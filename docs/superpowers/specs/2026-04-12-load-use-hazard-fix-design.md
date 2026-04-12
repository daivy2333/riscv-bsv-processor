# Load-Use 冒险检测修复设计

日期：2026-04-12

## 问题概述

当前 RISC-V 五级流水线处理器中的 Load-Use 冒险检测存在缺陷，导致 `lw` 指令后紧跟使用其结果的指令时可能产生错误数据。

## 根因分析

### 当前实现问题

1. **检测时机错误**
   - 当前在 MEM 阶段检测（`Core.bsv:259-262`）
   - 应在 EX 阶段检测，因为此时 Load 指令刚进入 MEM，而下一条指令在 ID 阶段准备进入 EX

2. **检测对象错误**
   - 当前检查 `id2ex.first.rs1/rs2`（已在 EX 阶段的指令）
   - 应检查 `if2id.first` 中解码后的 rs1/rs2 信息

3. **前递时机错误**
   - MEM→EX 前递的是 `alu_result`（Load 地址），而非 `mem_data`（Load 数据）
   - Load 数据在 WB 阶段才可用（从 dmem 读出）

4. **停顿处理不完整**
   - 仅设置 `stall` 标志，但未正确暂停 IF/ID 阶段
   - 未插入气泡到 EX 阶段

5. **已有模块未集成**
   - `HazardUnit.bsv` 已实现冒险检测逻辑但未被 Core 使用
   - `ForwardUnit.bsv` 已实现前递逻辑但未被 Core 使用

### Load-Use 冒险时序分析

```
周期1: lw x1, 0(x2)    → IF
周期2: lw x1, 0(x2)    → ID    | add x3, x1, x4 → IF
周期3: lw x1, 0(x2)    → EX    | add x3, x1, x4 → ID    | xxx → IF (暂停)
周期4: lw x1, 0(x2)    → MEM   | [气泡]          → EX    | add x3, x1, x4 → ID (暂停)
周期5: lw x1, 0(x2)    → WB    | xxx             → MEM   | add x3, x1, x4 → EX (前递可用)
```

关键点：
- Load 数据在 MEM 阶段从 dmem 读取，在 WB 阶段写入 RegFile
- 使用 Load 结果的指令需要等待数据在 WB 阶段可用后才能前递
- 需要停顿 1 个周期 + 插入 1 个气泡

## 设计目标

1. 正确检测 Load-Use 冒险（EX 阶段 Load 指令，ID 阶段依赖指令）
2. 停顿 IF/ID 阶段，阻止新指令进入
3. 插入气泡到 EX 阶段，保持流水线流动
4. 在 WB 阶段前递 Load 数据到 EX 阶段
5. 测试覆盖所有场景：基本 Load-Use、多指令依赖、Load-Use 与分支

## 解决方案设计

### 架构修改

#### 1. 集成 HazardUnit

在 Core 模块中实例化 HazardUnit，在 ID 阶段调用检测方法：

```bsv
// 冒险检测在 ID 阶段进行
Bool load_use_hazard = hazardUnit.detectLoadUseHazard(
    ex2mem.first.is_load,    // EX→MEM: Load 指令刚进入 MEM
    ex2mem.first.rd,          // Load 的目标寄存器
    decoded.use_rs1,          // ID 阶段是否使用 rs1
    decoded.rs1,              // ID 阶段 rs1 编号
    decoded.use_rs2,          // ID 阶段是否使用 rs2
    decoded.rs2               // ID 阶段 rs2 编号
);
```

**检测时机说明**：
- Load 指令从 EX 进入 MEM 时（`ex2mem.first`）
- 依赖指令在 ID 阶段准备进入 EX（`if2id.first`）
- 此时检测冒险，停顿 ID 阶段，阻止依赖指令进入 EX
- 同时插入气泡到 EX 阶段，保持流水线流动

#### 2. 停顿控制信号

新增/修改控制信号：

```bsv
Reg#(Bool) stall_id <- mkReg(False);    // ID 阶段停顿
Reg#(Bool) stall_if <- mkReg(False);    // IF 阶段停顿（跟随 stall_id）
Reg#(Bool) insert_bubble <- mkReg(False); // 需要插入气泡到 EX
```

停顿逻辑：
- 检测到 Load-Use 冒险：`stall_id = True`, `insert_bubble = True`
- IF 阶段自动跟随 ID 停顿（无新指令进入）
- 下个周期：ID 阶段释放，EX 阶段插入 NOP 气泡

#### 3. 流水线阶段修改

**IF 阶段**：
```bsv
rule fetchStage (programLoaded && state == RUNNING && !stall_if);
    // 正常取指
endrule
```

**ID 阶段**：
```bsv
rule decodeStage (!stall_id && !insert_bubble);
    // 检测 Load-Use 冒险
    if (load_use_hazard) begin
        stall_id <= True;
        insert_bubble <= True;
        // 不发送包到 EX，保持 if2id 数据
    end else begin
        // 正常解码并发送到 EX
        if2id.deq;
        id2ex.enq(packet);
    end
endrule
```

**气泡插入规则**：
```bsv
rule insertBubble (insert_bubble && !stall_id);
    // 发送 NOP 到 EX
    id2ex.enq(nop_packet);
    insert_bubble <= False;
    stall_id <= False;
endrule
```

#### 4. 前递逻辑修改

Load 数据前递：
- Load 数据在 MEM 阶段从 dmem 读取得到 `mem_data`
- 在 WB 阶段，`mem_data` 可通过 WB→EX 前递传递给 EX 阶段

修改 WB→EX 前递：
```bsv
// WB 阶段前递
wb_forward <= wb_data;  // Load 指令用 mem_data，其他用 alu_result
wb_forward_rd <= pkt.rd;
wb_forward_valid <= pkt.write_reg;
```

### 数据流图

```
                    Load-Use 冒险检测
                          │
                          ▼
┌─────────┐    ┌─────────┐    ┌─────────┐    ┌─────────┐    ┌─────────┐
│   IF    │───▶│   ID    │───▶│   EX    │───▶│   MEM   │───▶│   WB    │
│ (暂停)  │    │ (检测)  │    │ (气泡)  │    │ (Load)  │    │ (前递)  │
└─────────┘    └─────────┘    └─────────┘    └─────────┘    └─────────┘
                    │                              │              │
                    │                              │              │
                    └────────── 冒险检测 ──────────┘              │
                    │                              │              │
                    └──────────────── WB→EX 前递 ─────────────────┘
```

### 气泡包定义

```bsv
function ID_EX_Packet nopPacket();
    return ID_EX_Packet {
        pc: 0,
        instruction: 0,
        rs1_val: 0, rs2_val: 0,
        imm: 0,
        rs1: 0, rs2: 0, rd: 0,
        alu_op: ALU_ADD,
        branch_cond: BR_NONE,
        mem_op: MEM_NONE,
        is_branch: False,
        is_jump: False,
        write_reg: False,
        use_imm: False
    };
endfunction
```

## 测试用例设计

### 测试1：基本 Load-Use

```asm
# lw 后紧跟 add 使用 Load 结果
li x1, 10          # x1 = 10
li x2, 4           # x2 = 4 (地址偏移)
sw x1, 0(x2)       # 存储 10 到 dmem[1]
lw x3, 0(x2)       # 从 dmem[1] 加载到 x3
add x4, x3, x1     # x4 = x3 + x1 = 10 + 10 = 20 (Load-Use 冒险)
# 验证：x3 = 10, x4 = 20
```

### 测试2：多指令依赖 Load

```asm
# lw 后多条指令都使用 Load 结果
li x1, 10
li x2, 4
sw x1, 0(x2)
lw x3, 0(x2)       # Load x3 = 10
add x4, x3, x1     # x4 = 20 (Load-Use)
sub x5, x3, x1     # x5 = 0 (前递可用，无冒险)
# 验证：x3 = 10, x4 = 20, x5 = 0
```

### 测试3：Load-Use 与分支

```asm
# lw 后分支指令判断 Load 结果
li x1, 10
li x2, 4
sw x1, 0(x2)
lw x3, 0(x2)       # Load x3 = 10
beq x3, x1, target # Load-Use 冒险，比较 x3 和 x1
li x4, 0           # 不跳转时执行
j end
target:
li x4, 1           # 跳转时执行
end:
# 验证：x3 = 10, x4 = 1 (因为 x3 == x1，分支命中)
```

## 实现要点

1. **修改 Types.bsv**：在 DecodedInstr 结构中添加 `use_rs1` 和 `use_rs2` 字段
2. **修改 Decoder.bsv**：解码时设置 `use_rs1` 和 `use_rs2`
3. **修改 Core.bsv**：
   - 实例化 HazardUnit
   - ID 阶段检测 Load-Use 冒险
   - 实现停顿和气泡插入逻辑
   - 确保 WB→EX 前递正确传递 Load 数据
4. **修改 TestBench.bsv**：添加 Load-Use 测试用例

## 影响范围

- `src/common/Types.bsv` - 添加字段
- `src/core/Decoder.bsv` - 解码逻辑修改
- `src/core/Core.bsv` - 冒险检测和停顿逻辑
- `src/soc/TestBench.bsv` - 测试用例

## 验证方法

1. 编译 BSV：`make compile`
2. 运行仿真：`./obj_dir/VmkTestBench`
3. 检查输出：验证寄存器值符合预期
4. 添加更多测试用例验证边界情况