# 阶段1完善基础功能 - 设计文档（修订版）

日期：2026-04-17

## 目标

完成阶段1四个任务，使处理器能够运行 RISC-V 官方测试：
1. 统一 Load-Use 冒险检测实现
2. 添加 LB/LH/LBU/LHU + SB/SH 字节/半字指令
3. 内存扩展到 16MB（含 Core 内嵌内存）
4. 运行 riscv-tests 官方测试

## 实现策略

采用分层实现 + 官方测试验证策略：

```
内存扩展 → 字节指令 → HazardUnit重构 → 官方测试验证全部
```

---

## 第一部分：内存扩展到 16MB

### 问题分析

**当前状态**：
- Core.bsv:61-62 内嵌了 imem/dmem（1024/512 entries）
- 外部 IMem.bsv/DMem.bsv 模块未被使用
- 这是重复实现，需要统一

**解决方案**：保留 Core 内嵌内存（测试方便），扩展容量

### 改动范围

| 文件 | 改动内容 |
|------|----------|
| `Core.bsv` | imem 1024→16384，dmem 512→262144，索引位宽扩展 |
| `Types.bsv` | 无需改动（Addr 已是 32 位） |

### 内存布局

```
IMem: 0x80000000 - 0x8000FFFF (64KB, 16384×32bit)
      索引: addr[15:2] (14 位)
DMem: 0x80000000 - 0x80FFFFFF (16MB, 262144×32bit)
      索引: addr[21:2] (18 位)
```

### 实现细节

**Core.bsv 改动**：
```bsv
// 原来：Vector#(1024, Reg#(Word)) imem <- replicateM(mkReg(0));
// 改为：
Vector#(16384, Reg#(Word)) imem <- replicateM(mkRegU);

// 原来：Vector#(512, Reg#(Word)) dmem <- replicateM(mkReg(0));
// 改为：
Vector#(262144, Reg#(Word)) dmem <- replicateM(mkRegU);

// IF 阶段索引改动
// 原来：Bit#(10) idx = fetchPC[11:2];
// 改为：
Bit#(14) idx = fetchPC[15:2];

// MEM 阶段索引改动
// 原来：dmem[pkt.alu_result[10:2]]
// 改为：
dmem[pkt.alu_result[21:2]]
```

### loadProgram 接口改动

```bsv
// 原来：method Action loadProgram(Vector#(1024, Word) prog);
// 改为：
method Action loadProgram(Vector#(16384, Word) prog);

// 循环范围改动
for (Integer i = 0; i < 16384; i = i + 1)
    imem[i] <= prog[i];
```

### 注意事项

- 使用 `mkRegU` 减少仿真初始化开销
- 仿真时内存占用约 16MB×4 = 64MB RAM
- 外部 IMem.bsv/DMem.bsv 保留但不使用（未来可改为 SOC 外设）

---

## 第二部分：添加 LB/LH/LBU/LHU + SB/SH

### 改动范围

| 文件 | 改动内容 |
|------|----------|
| `Types.bsv` | 添加 MemWidth 枚举，扩展数据包 |
| `Decoder.bsv` | 解码 funct3 区分字节/半字/字操作 |
| `Core.bsv` | MEM 阶段根据 width 调用对应处理逻辑 |

### MemWidth 枚举

```bsv
// Types.bsv 新增
typedef enum {
    MEM_BYTE,   // LB/LBU/SB
    MEM_HALF,   // LH/LHU/SH
    MEM_WORD    // LW/SW
} MemWidth deriving (Bits, Eq, FShow);
```

### 数据包改动

**DecodedInstr 新增字段**：
```bsv
// Decoder.bsv
MemWidth    mem_width;      // 内存访问宽度
Bool        mem_unsigned;   // 是否无符号扩展 (LBU/LHU)
```

**ID_EX_Packet 新增字段**：
```bsv
// Types.bsv
MemWidth    mem_width;
Bool        mem_unsigned;
```

**EX_MEM_Packet 新增字段**：
```bsv
// Types.bsv
MemWidth    mem_width;
Bool        mem_unsigned;
```

### Decoder funct3 完整处理

**Load 指令 (opcode 7'b0000011)**：
| funct3 | 指令 | mem_width | mem_unsigned |
|--------|------|-----------|--------------|
| 000 | LB | MEM_BYTE | False |
| 001 | LH | MEM_HALF | False |
| 010 | LW | MEM_WORD | False |
| 100 | LBU | MEM_BYTE | True |
| 101 | LHU | MEM_HALF | True |

**Store 指令 (opcode 7'b0100011)**：
| funct3 | 指令 | mem_width |
|--------|------|-----------|
| 000 | SB | MEM_BYTE |
| 001 | SH | MEM_HALF |
| 010 | SW | MEM_WORD |

**Decoder.bsv 实现改动**：
```bsv
// 7'b0000011: Load 指令
7'b0000011: begin
    write_reg = True;
    is_load = True;
    mem_op = MEM_READ;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = False;
    imm = signExtendI(instruction);
    alu_op = ALU_ADD;

    // 新增：根据 funct3 区分
    case (funct3)
        3'b000: begin  // LB
            mem_width = MEM_BYTE;
            mem_unsigned = False;
        end
        3'b001: begin  // LH
            mem_width = MEM_HALF;
            mem_unsigned = False;
        end
        3'b010: begin  // LW
            mem_width = MEM_WORD;
            mem_unsigned = False;
        end
        3'b100: begin  // LBU
            mem_width = MEM_BYTE;
            mem_unsigned = True;
        end
        3'b101: begin  // LHU
            mem_width = MEM_HALF;
            mem_unsigned = True;
        end
        default: begin
            mem_width = MEM_WORD;
            mem_unsigned = False;
        end
    endcase
end

// 7'b0100011: Store 指令
7'b0100011: begin
    mem_op = MEM_WRITE;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = True;
    imm = signExtendS(instruction);
    alu_op = ALU_ADD;

    // 新增：根据 funct3 区分
    case (funct3)
        3'b000: mem_width = MEM_BYTE;  // SB
        3'b001: mem_width = MEM_HALF;  // SH
        3'b010: mem_width = MEM_WORD;  // SW
        default: mem_width = MEM_WORD;
    endcase
end
```

### Core MEM 阶段改动

**字节/半字读取实现**：
```bsv
// MEM 阶段改动
Word mem_data = 0;

if (pkt.mem_op == MEM_READ) begin
    Bit#(18) word_idx = pkt.alu_result[21:2];
    Word word_val = dmem[word_idx];

    case (pkt.mem_width)
        MEM_WORD: mem_data = word_val;

        MEM_HALF: begin
            Bit#(1) half_offset = pkt.alu_result[1];
            Bit#(16) half_val = half_offset == 0
                ? word_val[15:0]
                : word_val[31:16];
            mem_data = pkt.mem_unsigned
                ? zeroExtend(half_val)
                : signExtend(half_val);
        end

        MEM_BYTE: begin
            Bit#(2) byte_offset = pkt.alu_result[1:0];
            Bit#(8) byte_val = case (byte_offset)
                0: word_val[7:0];
                1: word_val[15:8];
                2: word_val[23:16];
                3: word_val[31:24];
            endcase;
            mem_data = pkt.mem_unsigned
                ? zeroExtend(byte_val)
                : signExtend(byte_val);
        end
    endcase
end
```

**字节/半字写入实现**：
```bsv
if (pkt.mem_op == MEM_WRITE) begin
    Bit#(18) word_idx = pkt.alu_result[21:2];
    Word old_word = dmem[word_idx];
    Word new_word = old_word;

    case (pkt.mem_width)
        MEM_WORD: new_word = pkt.rs2_val;

        MEM_HALF: begin
            Bit#(16) half_val = pkt.rs2_val[15:0];
            Bit#(1) half_offset = pkt.alu_result[1];
            new_word = half_offset == 0
                ? {old_word[31:16], half_val}
                : {half_val, old_word[15:0]};
        end

        MEM_BYTE: begin
            Bit#(8) byte_val = pkt.rs2_val[7:0];
            Bit#(2) byte_offset = pkt.alu_result[1:0];
            case (byte_offset)
                0: new_word = {old_word[31:8], byte_val};
                1: new_word = {old_word[31:16], byte_val, old_word[7:0]};
                2: new_word = {old_word[31:24], byte_val, old_word[15:0]};
                3: new_word = {byte_val, old_word[23:0]};
            endcase
        end
    endcase;

    dmem[word_idx] <= new_word;
end
```

### 非对齐访问处理

RISC-V 允许非字对齐访问：
- LB/LBU/SB：任意字节地址，addr[1:0] 选择字节位置
- LH/LHU/SH：任意半字地址，addr[1] 选择高低半字（addr[0] 忽略）

**实现说明**：
- `addr[1:0]` 用于字节选择（LB/SB）
- `addr[1]` 用于半字选择（LH/SH）
- 索引 `addr[21:2]` 用于字地址

---

## 第三部分：统一 Load-Use 冒险检测

### 问题分析

**当前状态**：
- Core.bsv:107-123 自己实现了 Load-Use 检测
- HazardUnit.bsv 的 detectLoadUseHazard 方法未被调用
- 这是重复实现，代码不一致

**解决方案**：使用 HazardUnit 模块，删除 Core 中的重复逻辑

### 改动范围

| 文件 | 改动内容 |
|------|----------|
| `HazardUnit.bsv` | 扩展检测方法支持 MEM 阶段检测 |
| `Core.bsv` | 删除 107-123 行重复逻辑，调用 hazardUnit |

### HazardUnit 扩展

```bsv
interface HazardUnit;
    method Bool detectLoadUseHazard(
        Bool ex_is_load,        // EX 阶段是否是 Load
        Bit#(5) ex_rd,          // EX 阶段目标寄存器
        Bool mem_is_load,       // MEM 阶段是否是 Load（新增）
        Bit#(5) mem_rd,         // MEM 阶段目标寄存器（新增）
        Bool id_use_rs1,
        Bit#(5) id_rs1,
        Bool id_use_rs2,
        Bit#(5) id_rs2
    );
endinterface
```

**实现改动**：
```bsv
method Bool detectLoadUseHazard(...);
    Bool hazard = False;

    // 检查 EX 阶段 Load
    if (ex_is_load && ex_rd != 0) begin
        if (id_use_rs1 && id_rs1 == ex_rd) hazard = True;
        if (id_use_rs2 && id_rs2 == ex_rd) hazard = True;
    end

    // 新增：检查 MEM 阶段 Load
    if (mem_is_load && mem_rd != 0 && !hazard) begin
        if (id_use_rs1 && id_rs1 == mem_rd) hazard = True;
        if (id_use_rs2 && id_rs2 == mem_rd) hazard = True;
    end

    return hazard;
endmethod
```

### Core.bsv 改动

**删除 107-123 行重复逻辑，改为调用 hazardUnit**：
```bsv
// 原来 107-123 行的重复实现删除
// 改为：
Bool load_use_hazard = hazardUnit.detectLoadUseHazard(
    id2ex.notEmpty && id2ex.first.mem_op == MEM_READ,
    id2ex.notEmpty ? id2ex.first.rd : 0,
    ex2mem.notEmpty && ex2mem.first.is_load,
    ex2mem.notEmpty ? ex2mem.first.rd : 0,
    dec.use_rs1,
    dec.rs1,
    dec.use_rs2,
    dec.rs2
);
```

---

## 第四部分：运行 riscv-tests 官方测试

### 测试套件

使用 `riscv-tests` 项目的 `rv32ui-p-*` 测试：
- 基础指令：simple, add, sub, and, or, xor, sll, srl, sra
- Load 指令：lw, lh, lb, lhu, lbu（含 Load-Use 验证）
- Store 指令：sw, sh, sb
- 分支：branch, beq, bne, blt, bge, bltu, bgeu
- 跳转：jal, jalr
- 立即数：addi, andi, ori, xori, slti, sltiu
- 比较：slt, sltu

### 集成步骤

1. **克隆 riscv-tests**：
   ```bash
   git clone https://github.com/riscv-software-src/riscv-tests
   cd riscv-tests
   ```

2. **编译测试**：
   ```bash
   make rv32ui
   ```

3. **转换格式**：
   ```bash
   riscv64-unknown-elf-objcopy -O verilog rv32ui-p-simple.elf rv32ui-p-simple.hex
   ```

4. **修改 TestBench.bsv**：
   - 添加 hex 文件加载函数
   - 添加 tohost 地址检测

### tohost 地址确认

riscv-tests 的 tohost 地址在 `tests/env/link.ld` 中定义：
```ld
tohost = 0x80001000;
```

需要在编译前确认，或查看生成的 hex 文件。

### hex 文件加载函数

```bsv
function Action loadHexFile(String filename, Vector#(N, Reg#(Word)) mem);
    // 解析 verilog hex 格式
    // 格式：@地址 数据...
endfunction
```

### TestBench 检测逻辑

```bsv
// MEM 阶段检测 tohost 写入
Bit#(32) tohost_addr = 32'h80001000;

// 在 MEM 写入时检测
if (pkt.mem_op == MEM_WRITE && pkt.alu_result == tohost_addr) begin
    if (pkt.rs2_val == 1) $display("PASS");
    else $display("FAIL: %0d", pkt.rs2_val);
    $finish;
end
```

---

## Load-Use 专项测试矩阵

riscv-tests 基本覆盖，但建议额外验证：

| 测试 | Load 指令 | Use 指令 | 期望停顿 |
|------|-----------|----------|----------|
| 1 | LW x1, 0(x0) | ADD x2, x1, x3 | 1 周期 |
| 2 | LB x1, 0(x0) | SB x1, 1(x0) | 1 周期 |
| 3 | LH x1, 0(x0) | SH x1, 2(x0) | 1 周期 |
| 4 | LBU x1, 0(x0) | AND x2, x1, x3 | 1 周期 |
| 5 | LHU x1, 0(x0) | OR x2, x1, x3 | 1 周期 |
| 6 | LW (MEM 阶段) | SUB (ID 阃段) | 0 周期 |

---

## 实现顺序

| 步骤 | 任务 | 验证方式 |
|------|------|----------|
| 1 | Types.bsv 添加 MemWidth | 编译通过 |
| 2 | Types.bsv 扩展数据包字段 | 编译通过 |
| 3 | Decoder.bsv 添加 funct3 处理 | 编译通过 |
| 4 | HazardUnit.bsv 扩展 MEM 阶段检测 | 编译通过 |
| 5 | Core.bsv 内存扩展 | LW/SW 程序 |
| 6 | Core.bsv MEM 阶段字节处理 | LB/LH/SB/SH 程序 |
| 7 | Core.bsv 使用 HazardUnit | 编译通过 + Load-Use 测试 |
| 8 | TestBench.bsv hex 加载 | 加载测试 hex |
| 9 | 运行 riscv-tests | 全部 PASS |

---

## 风险与注意事项

1. **内存容量**：16MB 仿真内存占用约 64MB RAM
2. **字节对齐**：SB/SH 写入需要正确处理字内字节位置
3. **tohost 地址**：需确认 riscv-tests 配置中的实际地址
4. **HazardUnit 参数**：MEM 阶段检测需要额外参数
5. **NOP 包字段**：nopPacket() 需要添加 mem_width/mem_unsigned 字段

## 验证目标

通过所有 `rv32ui-p-*` 测试（约 40 个），验证：
- Load-Use 冒险正确处理（统一 HazardUnit 实现）
- 字节/半字指令正确（LB/LH/LBU/LHU/SB/SH）
- 分支预测正确（branch 测试）
- 五级流水线稳定工作