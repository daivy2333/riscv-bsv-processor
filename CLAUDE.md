# CLAUDE.md

Claude Code 项目指南。

## 项目概述

RISC-V RV32I 五级流水线处理器，使用 BSV 实现，Verilator 仿真。目标是支持 FreeRTOS/uClinux。

## 构建命令

```bash
# BSV 编译
make compile

# Verilator 构建+运行
rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench --top-module mkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench

# 快速测试
make test

# 清理
make clean
```

## 工具链

| 工具 | 用途 | 安装检查 |
|------|------|----------|
| **BSC** | BSV → Verilog | `bsc --version` |
| **riscv64-unknown-elf-gcc** | 汇编编译 | `which riscv64-unknown-elf-gcc` |
| **Verilator** | Verilog C++ 仿真 | `verilator --version` |

## 测试方法

### 流程

```
汇编测试 (tests/assembly/*.s)
    ↓ riscv64-unknown-elf-gcc -march=rv32i_zicsr
Hex 文件 (firmware/*.hex)
    ↓ python3 tools/hex_to_bsv.py
BSV 程序 (src/soc/TestProgram.bsv)
    ↓ make compile
Verilator 仿真
    ↓ ./obj_dir/VmkTestBench
测试结果
```

### 添加新测试

```bash
# 1. 编写汇编测试
vim tests/assembly/new_test.s

# 2. 编译为 hex（禁用压缩指令，启用 zicsr）
make firmware/new_test.hex

# 3. 生成 BSV 测试程序
python3 tools/hex_to_bsv.py firmware/new_test.hex > src/soc/TestProgram.bsv

# 4. 运行测试
make test
```

### 现有测试

| 测试文件 | 验证内容 | 结果 |
|----------|----------|------|
| `tests/assembly/loop_test.s` | 循环 + 分支预测 | ✓ PASSED (71 cycles) |
| `tests/assembly/pipeline_test.s` | 完整流水线测试 | ✓ PASSED (65 cycles) |
| `tests/assembly/simple_arith_test.s` | 基本算术 + li 指令 | ✓ PASSED (50 cycles) |
| `tests/assembly/load_test.s` | Load-Use 冒险 + li | ✓ PASSED (57 cycles) |
| `tests/assembly/csr_basic_test.s` | CSR 读写和 mcycle/mtvec | ✓ PASSED (58 cycles) |
| `tests/assembly/privilege_m_mode_test.s` | M-mode CSR 基本操作 | ✓ PASSED (64 cycles) |
| `tests/assembly/csr_immediate_test.s` | CSRRWI/CSRRSI/CSRRCI | ✓ PASSED (46 cycles) |
| `tests/assembly/rtype_complete_test.s` | R-Type 全指令集验证 | ✓ PASSED |
| `tests/assembly/itype_alu_test.s` | SLTI/ADDI 等立即数指令 | ✓ PASSED |
| `tests/assembly/simple_branch_test.s` | 分支预测和执行 | ✓ PASSED |
| `tests/assembly/simple_loop.s` | 循环计数 | ✓ PASSED |

**总计**: 11 个测试，全部通过

## 架构要点

### 五级流水线

```
IF → ID → EX → MEM → WB
```

| 阶段 | 功能 | 关键模块 |
|------|------|----------|
| IF | 取指 + 分支预测 | BHT(64)/BTB(64) |
| ID | 解码 + 冒险检测 + CSR 指令检测 | Decoder/HazardUnit |
| EX | ALU 执行 + 前递选择 + CSR 操作 + 陷阱处理 | ALU + CSR |
| MEM | 内存访问 + tohost 检测 | DMem |
| WB | 寄存器写回 | RegFile |

### 关键文件

| 文件 | 作用 |
|------|------|
| `src/core/Core.bsv` | 流水线核心，规则调度，陷阱处理 |
| `src/soc/SOC.bsv` | SOC 集成，外设连接，内存路由 |
| `src/soc/TestBench.bsv` | 仿真测试台，完成检测 |
| `src/common/Types.bsv` | 数据包定义，MemReq/MemResp |
| `src/core/Decoder.bsv` | 指令解码 + CSR 指令解码 |
| `src/core/CSR.bsv` | CSR 寄存器文件 |
| `src/core/PrivilegedTypes.bsv` | 特权级类型定义 |
| `src/core/ALU.bsv` | ALU 操作实现 |
| `src/branch/BHT.bsv` | 2位饱和计数器预测 |
| `src/branch/BTB.bsv` | 分支目标缓冲 |
| `src/memory/DMem.bsv` | 数据内存 + tohost 监控 |
| `src/peripheral/CLINT.bsv` | 定时器外设 |
| `src/peripheral/PLIC.bsv` | 中断控制器 |
| `src/peripheral/UART.bsv` | 控制台外设 |
| `src/soc/TestProgram.bsv` | 自动生成的测试程序 |

### 数据前递

| 前递路径 | 数据来源 | 优先级 | 说明 |
|----------|----------|--------|------|
| MEM→EX | ex2mem.first | 高 | 直接读取 FIFO，同周期可用 |
| WB→EX | mem2wb.first | 中 | 直接读取 FIFO，同周期可用 |
| WB→EX (历史) | wb_forward_data0/1 | 低 | 双缓冲 Reg，保存最近两周期 WB 写入 |
| WB→ID | wb_forward_data0/1 | 低 | 解决分支读寄存器延迟 |

**注**: 前递直接从 FIFO 读取，绕过 BSV 规则顺序限制；WB 前递使用双缓冲解决 mkReg 写入延迟

### Load-Use 冒险处理

```
周期 N:   Load 进入 EX
周期 N:   ID 检测冒险 → stall=1, count=2 → 插入 NOP 气泡
周期 N+1: decrementStall → count=1 → 插入 NOP
周期 N+2: decrementStall → count=0 → stall=0
周期 N+3: Load 在 WB → WB→EX 前递可用
```

## 已实现指令

### RV32I 指令集覆盖

| 类型 | 指令 | 状态 |
|------|------|------|
| **R-Type** | ADD, SUB, SLL, SRL, SRA, SLT, SLTU, AND, OR, XOR | ✓ 已验证 |
| **I-Type ALU** | ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI | ✓ 已验证 |
| **I-Type Load** | LB, LH, LW, LBU, LHU | ✓ 已实现 |
| **S-Type** | SB, SH, SW | ✓ 已实现 |
| **B-Type** | BEQ, BNE, BLT, BGE, BLTU, BGEU | ✓ 已验证 |
| **U-Type** | LUI, AUIPC | ✓ 已实现 |
| **J-Type** | JAL, JALR | ✓ 已验证 |

### 特权指令 (Zicsr 扩展)

| 指令 | 说明 | 状态 |
|------|------|------|
| CSRRW | 读后写 CSR | ✓ 已实现 |
| CSRRS | 读后置位 CSR | ✓ 已实现 |
| CSRRC | 读后清除 CSR | ✓ 已实现 |
| CSRRWI | 立即数写 CSR | ✓ 已实现 |
| CSRRSI | 立即数置位 CSR | ✓ 已实现 |
| CSRRCI | 立即数清除 CSR | ✓ 已实现 |
| ECALL | 环境调用 | ✓ 已实现 |
| EBREAK | 断点 | ✓ 已实现 |
| MRET | 从 M-mode 陷阱返回 | ✓ 已实现 |

## 已实现 CSR

| 地址 | 名称 | 说明 |
|------|------|------|
| 0xF11 | mvendorid | 供应商 ID |
| 0xF12 | marchid | 架构 ID |
| 0xF13 | mimpid | 实现 ID |
| 0xF14 | mhartid | 硬件线程 ID |
| 0x300 | mstatus | 机器状态 |
| 0x301 | misa | 机器 ISA |
| 0x304 | mie | 机器中断使能 |
| 0x305 | mtvec | 机器陷阱向量 |
| 0x341 | mepc | 机器异常 PC |
| 0x342 | mcause | 机器异常原因 |
| 0x343 | mtval | 机器陷阱值 |
| 0x344 | mip | 机器中断挂起 |
| 0xB00 | mcycle | 周期计数器 |
| 0xB01 | mtime | 时间计数器 |
| 0xB02 | mtimecmp | 时间比较 |
| 0xB03 | minstret | 指令 retired 计数 |

## 已验证功能

- [x] 五级流水线 (IF, ID, EX, MEM, WB)
- [x] 数据前递 (MEM→EX, WB→EX, WB→ID)
- [x] WB 前递双缓冲 (wb_forward_data0/1)
- [x] wb_forward_valid0 fix (rd!=0 检查)
- [x] Load-Use 冒险检测 + stall + 气泡插入
- [x] 动态分支预测 (BHT + BTB)
- [x] 分支冲刷控制 (branch_flush/no_pc_update)
- [x] 所有 R-Type 指令 (10条)
- [x] 所有 I-Type ALU 指令 (9条)
- [x] Load/Store 字节/半字/字 (8条)
- [x] 所有分支指令 (6条)
- [x] LUI, AUIPC, JAL, JALR
- [x] 地址对齐检查
- [x] tohost 写入检测 (0x80001000)
- [x] 汇编测试框架 (hex → BSV)
- [x] 特权级架构 (M-mode)
- [x] CSR 寄存器 (mstatus, mie, mip, mtvec, mepc, mcause, mtval)
- [x] CSR 指令 (CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI)
- [x] 陷阱处理 (ECALL, EBREAK, MRET)
- [x] CLINT 内存映射访问 (mtime, mtimecmp)
- [x] 中断检查框架 (getPendingInterruptCause)
- [x] 分支预测失败处理 (misprediction detection + flush)
- [x] SOC 架构 (Core ↔ SOC ↔ 外设)
- [x] PLIC 中断控制器框架 (8 IRQ)
- [x] UART 控制台框架
- [x] BSV 规则调度修复 (descending_urgency)
- [x] 所有测试通过 (11 tests)

## 内存配置

| 内存 | 大小 | 索引方式 | 基址 |
|------|------|----------|------|
| IMem | 1024×32bit (4KB) | PC[11:2] | 0x80000000 |
| DMem | 2048×32bit (8KB) | addr[12:2] | - |
| tohost | 1 word | - | 0x80001000 |

**外设地址映射**：

| 外设 | 地址范围 | 说明 |
|------|----------|------|
| CLINT | 0x02000000-0x0200FFFF | mtime, mtimecmp |
| PLIC | 0x0C000000-0x0C0FFFFF | 中断控制器 |
| UART | 0x10000000-0x10000FFF | 控制台 |

## BSV 模式

```bsv
// FIFO 流水线寄存器（深度2，允许 stall 时操作）
FIFOF#(Packet) fifo <- mkFIFOF;

// 规则条件互斥
rule decodeStage (!stall_load_use);
rule decrementStall (stall_load_use && stall_count > 0);

// 结构体
typedef struct {
    Addr pc;
    Word data;
} Packet deriving (Bits, Eq, FShow);
```

## 注意事项

- x0 寄存器硬连线为0，不参与前递
- Load 不在 MEM→EX 前递（数据尚未可用）
- 编译汇编时必须禁用压缩指令: `-march=rv32i_zicsr`
- Verilator 4.038 不支持 VerilatedVar API
- DMem 地址必须 < 8192 (2048 words)
- 分支跳转后 IF 阶段暂停一周期（branch_flush 控制）
- CSR 指令需要 Zicsr 扩展
- **BSV 规则调度**: Wire 信号会引发跨规则冲突，优先使用 Reg
- **BSV 规则调度**: 使用 `descending_urgency` 属性解决死锁
- **BSV 规则调度**: 检查 Verilog 输出中的 enable 信号（如 `1'b0 &&`）

## 开发阶段

### 阶段 1-2（已完成）

1. ✓ 五级流水线
2. ✓ 数据前递 + Load-Use 冒险
3. ✓ 分支预测
4. ✓ RV32I 全指令支持

### 阶段 3（已完成）

1. ✓ 特权级类型定义 (PrivilegedTypes.bsv)
2. ✓ CSR 寄存器模块 (CSR.bsv)
3. ✓ CSR 指令解码 (Decoder.bsv)
4. ✓ 陷阱处理 (ECALL, EBREAK, MRET)
5. ✓ 特权模式测试

### 阶段 4（已完成）

1. ✓ CLINT 定时器基础设施 (mtime, mtimecmp 内存映射)
2. ✓ 中断检查框架 (getPendingInterruptCause)
3. ✓ 分支预测失败处理修复
4. ✓ 所有测试通过 (11 tests)

关键修复：分支预测只影响下一周期 PC，不跳过当前指令；ID_EX_Packet 携带预测信息；executeStage 检测 misprediction 并正确冲刷。详见 `docs/debugging-lessons.md`。

### 阶段 5（已完成）

1. ✓ SOC 架构重构 (Core ↔ SOC ↔ 外设)
2. ✓ CLINT 定时器模块 (CLINT.bsv)
3. ✓ PLIC 中断控制器 (PLIC.bsv, 8 IRQ)
4. ✓ UART 控制台框架 (UART.bsv)
5. ✓ 内存请求/响应接口 (MemReq/MemResp)
6. ✓ BSV 规则调度修复 (descending_urgency)

关键修复：Wire 信号引发规则冲突 → 改用 Reg；TestBench 规则死锁 → 使用 descending_urgency 属性。详见 `docs/debugging-lessons.md`。

---

### 阶段 6：FreeRTOS 支持（待开始）

| 任务 | 内容 | 优先级 |
|------|------|--------|
| 内存扩展 | 16MB RAM，支持操作系统加载 | 高 |
| 中断向量 | mtvec MODE=1，中断跳转实现 | 高 |
| 栈初始化 | MSP 设置，启动代码 | 高 |
| Timer中断 | CLINT mtimecmp 中断触发 | 中 |
| FreeRTOS移植 | 首次启动测试 | 低 |

**里程碑目标**: 首次启动 FreeRTOS，执行简单任务调度

## 相关文档

- `docs/cpu-pipeline-architecture.md` - 流水线结构图解
- `docs/branch-prediction.md` - 分支预测机制
- `docs/load-use-hazard.md` - 冒险检测流程
- `docs/debugging-lessons.md` - 棘手问题调试经验
- `docs/testing-guide.md` - 测试方法指南
- `docs/roadmap-embedded-os.md` - OS 支持路线图

## 分支预测机制

- BHT（64-entry 2-bit 饱和计数器）用于预测分支是否 taken
- BTB（64-entry）用于存储分支目标地址
- 预测只影响下一周期的 PC，当前指令仍正常取指
- ID_EX_Packet 携带 `predicted_taken` 和 `predicted_target` 字段
- executeStage 检测 misprediction 并正确冲刷流水线
- 冲刷恢复期间禁用预测以避免二次错误
