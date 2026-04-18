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
    ↓ riscv64-unknown-elf-gcc -march=rv32i
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

# 2. 编译为 hex（禁用压缩指令）
make firmware/new_test.hex

# 3. 生成 BSV 测试程序
python3 tools/hex_to_bsv.py firmware/new_test.hex > src/soc/TestProgram.bsv

# 4. 修改 TestBench.bsv 的结束条件和预期值
vim src/soc/TestBench.bsv

# 5. 运行测试
make test
```

### 现有测试

| 测试文件 | 验证内容 | 结果 |
|----------|----------|------|
| `tests/assembly/pipeline_test.s` | 数据前递 + Load-Use + 分支 + 循环 | ✓ 通过 |
| `tests/assembly/rtype_test.s` | SUB/SLL/SRL/SRA/SLT/AND/OR/XOR | ✓ 通过 |

## 架构要点

### 五级流水线

```
IF → ID → EX → MEM → WB
```

| 阶段 | 功能 | 关键模块 |
|------|------|----------|
| IF | 取指 + 分支预测 | BHT(64)/BTB(64) |
| ID | 解码 + 冒险检测 | Decoder/HazardUnit |
| EX | ALU + 前递选择 | ALU + Forward |
| MEM | 内存访问 + tohost 检测 | DMem |
| WB | 寄存器写回 | RegFile |

### 关键文件

| 文件 | 作用 |
|------|------|
| `src/core/Core.bsv` | 流水线核心，规则调度 |
| `src/common/Types.bsv` | 数据包定义 |
| `src/core/Decoder.bsv` | 指令解码 + use_rs1/rs2 |
| `src/core/ALU.bsv` | ALU 操作实现 |
| `src/branch/BHT.bsv` | 2位饱和计数器预测 |
| `src/soc/TestProgram.bsv` | 自动生成的测试程序 |

### 数据前递

| 前递路径 | 数据来源 | 优先级 | 说明 |
|----------|----------|--------|------|
| MEM→EX | ex2mem.first | 高 | 直接读取 FIFO，同周期可用 |
| WB→EX | mem2wb.first | 中 | 直接读取 FIFO，同周期可用 |
| WB→ID | wb_forward_data | 低 | Reg 存储，解决分支读寄存器延迟 |

**注**: 前递直接从 FIFO 读取，绕过 BSV 规则顺序限制

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
| **R-Type** | ADD, SUB, SLL, SRL, SRA, SLT, SLTU, AND, OR, XOR | ✓ 已实现 |
| **I-Type ALU** | ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI | 部分 ✓ |
| **I-Type Load** | LB, LH, LW, LBU, LHU | ✓ 已实现 |
| **S-Type** | SB, SH, SW | ✓ 已实现 |
| **B-Type** | BEQ, BNE, BLT, BGE, BLTU, BGEU | ✓ 已实现 |
| **U-Type** | LUI, AUIPC | ✓ 已实现 |
| **J-Type** | JAL, JALR | ✓ 已实现 |

### 待实现 I-Type ALU 指令

- SLTI, SLTIU (有符号/无符号比较立即数)
- ANDI, ORI, XORI (逻辑立即数操作)
- SLLI, SRLI, SRAI (移位立即数)

**注**: Decoder 已有解析逻辑，ALU 已有操作支持，仅需确认 I-Type 解码正确。

## 已验证功能

- [x] 五级流水线 (IF, ID, EX, MEM, WB)
- [x] 数据前递 (MEM→EX, WB→EX, WB→ID)
- [x] Load-Use 冒险检测 + stall + 气泡插入
- [x] 动态分支预测 (BHT + BTB)
- [x] 分支/跳转 PC 更新 (MEM 阶段执行)
- [x] 所有 R-Type 指令 (10条)
- [x] Load/Store 字节/半字/字 (8条)
- [x] 所有分支指令 (6条)
- [x] LUI, AUIPC, JAL, JALR
- [x] ADDI
- [x] 地址对齐检查
- [x] tohost 写入检测 (0x80001000)
- [x] 汇编测试框架 (hex → BSV)

## 内存配置

| 内存 | 大小 | 索引方式 | 基址 |
|------|------|----------|------|
| IMem | 1024×32bit (4KB) | PC[11:2] | 0x80000000 |
| DMem | 512×32bit (2KB) | addr[10:2] | - |
| tohost | 1 word | - | 0x80001000 |

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
- 编译汇编时必须禁用压缩指令: `-march=rv32i`
- Verilator 4.038 不支持 VerilatedVar API
- DMem 地址必须 < 2048 (512 words)

## 已知问题

### 分支冲刷时序问题

**现象**: 跳转到自身的指令（如 `j end`）会导致 PC 循环增加，形成无限循环

**原因**:
- MEM 阶段执行分支，设置 pcReg
- IF 阶段在同一周期已执行，使用旧 PC fetch 并增加 pcReg
- BSV 规则执行顺序导致 IF 阶段先于 MEM 阶段

**影响**: 测试无法正常结束（依赖死循环检测或 tohost 写入）

**解决方案**:
- 研究 BSV 规则调度机制
- 可能需要使用 Wire 或调整规则结构

## 后续任务

### 阶段 2（当前）

1. ✓ R-Type 指令 (已完成)
2. ⏳ 验证 I-Type ALU 指令 (SLTI/ANDI/SLLI 等) - 阻塞于分支冲刷问题
3. ⏳ 运行 riscv-tests 官方测试 - 阻塞于分支冲刷问题
4. 添加性能计数器 (CPI, 分支预测率)

### 阶段 3-4

- 特权级架构 (M/S/U mode)
- CSR 寄存器
- 异常/中断机制

### 阶段 5+

- CLINT/PLIC
- UART 控制台
- 内存扩展
- FreeRTOS/uClinux

## 相关文档

- `docs/cpu-pipeline-architecture.md` - 流水线结构图解
- `docs/data-forwarding.md` - 前递机制详解
- `docs/load-use-hazard.md` - 冒险检测流程
- `docs/branch-prediction.md` - 分支预测原理
- `docs/testing-guide.md` - 测试方法指南
- `docs/roadmap-embedded-os.md` - OS 支持路线图