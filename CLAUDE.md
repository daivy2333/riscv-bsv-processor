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
| `tests/assembly/wb_forward_test.s` | WB 前递 + beq 分支跳转 | ✓ 通过 |
| `tests/assembly/rtype_complete_test.s` | R-Type 全指令集验证 | ✓ PASSED |
| `tests/assembly/itype_alu_test.s` | SLTI/ADDI 等立即数指令 | ✓ PASSED |
| `tests/assembly/simple_branch_test.s` | 分支预测和执行 | ✓ 通过 |
| `tests/assembly/simple_loop.s` | 循环计数 | ✓ 通过 |
| `tests/assembly/simple_pass.s` | 基本算术 + tohost | ✓ PASSED |

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

## 已验证功能

- [x] 五级流水线 (IF, ID, EX, MEM, WB)
- [x] 数据前递 (MEM→EX, WB→EX, WB→ID)
- [x] WB 前递双缓冲 (wb_forward_data0/1)
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
- 分支跳转后 IF 阶段暂停一周期（branch_flush 控制）

## 后续任务

### 阶段 2（已完成）

1. ✓ R-Type 指令验证
2. ✓ I-Type ALU 指令验证 (SLTI/ANDI/SLLI 等)
3. ✓ 分支冲刷控制修复
4. 添加性能计数器 (CPI, 分支预测率) - 可选

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