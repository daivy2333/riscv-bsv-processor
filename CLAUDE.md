# CLAUDE.md

Claude Code 项目指南。

## 项目概述

RISC-V RV32I 五级流水线处理器，使用 BSV 实现，Verilator 仿真。目标是支持 FreeRTOS/uClinux。

**当前状态**: 阶段 1-8 全部完成，架构稳定，12 个测试全部通过。

## 快速开始

```bash
# 查看帮助
make help

# 运行单个测试
make test-loop_test

# 运行所有基线测试
make test-baseline

# 运行所有测试（含定时器中断）
make test-all

# 编译并运行
make all && make run

# 清理
make clean
```

## 构建命令

```bash
# BSV 编译
/opt/bsc/bin/bsc -verilog -p src:src/common:src/core:src/memory:src/soc:src/branch:src/peripheral:%/Libraries -no-warn-action-shadowing -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS

# Verilator 构建+运行
rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench --top-module mkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench

# 清理
rm -rf build obj_dir
```

## 工具链

| 工具 | 用途 | 安装检查 |
|------|------|----------|
| **BSC** | BSV → Verilog | `/opt/bsc/bin/bsc --version` |
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
    ↓ bsc -verilog ...
Verilator 仿真
    ↓ ./obj_dir/VmkTestBench
测试结果
```

### 添加新测试

```bash
# 1. 编写汇编测试（必须包含 tohost 写入）
vim tests/assembly/new_test.s

# 2. 编译为 hex
make asm-new_test

# 3. 运行测试
make test-new_test
```

### 测试结果

#### 基线测试（10个）

| 测试文件 | 验证内容 | 结果 |
|----------|----------|------|
| `loop_test.s` | 循环 + 分支预测 | ✓ PASSED |
| `simple_arith_test.s` | 基本算术 + li 指令 | ✓ PASSED |
| `load_test.s` | Load-Use 冒险 | ✓ PASSED |
| `csr_basic_test.s` | CSR 读写 | ✓ PASSED |
| `privilege_m_mode_test.s` | M-mode CSR 操作 | ✓ PASSED |
| `csr_immediate_test.s` | CSRRWI/CSRRSI/CSRRCI | ✓ PASSED |
| `rtype_complete_test.s` | R-Type 全指令集 | ✓ PASSED |
| `itype_alu_test.s` | 立即数 ALU 指令 | ✓ PASSED |
| `simple_branch_test.s` | 分支预测和执行 | ✓ PASSED |
| `simple_loop.s` | 循环计数 | ✓ PASSED |

#### 定时器中断测试（2个）

| 测试文件 | 验证内容 | 结果 |
|----------|----------|------|
| `mtime_increment_verify.s` | mtime 每周期递增 | ✓ PASSED |
| `mtimecmp_mtip_test.s` | MTIP 定时器中断触发 | ✓ PASSED |

**总计**: 12 个测试，全部通过 ✓

## 架构要点

### 五级流水线

```
IF → ID → EX → MEM → WB
```

| 阶段 | 功能 | 关键模块 |
|------|------|----------|
| IF | 取指 + 分支预测 | BHT(64)/BTB(64) |
| ID | 解码 + 冒险检测 | Decoder/HazardUnit |
| EX | ALU 执行 + 前递 + CSR + 陷阱处理 | ALU + CSR |
| MEM | 内存访问 + tohost 检测 | DMem |
| WB | 寄存器写回 | RegFile |

### 控制流重定向协议（统一）

| 状态寄存器 | 说明 |
|------------|------|
| `redirect_pending` | 重定向请求挂起 |
| `redirect_target` | 重定向目标地址 |
| `redirect_reason` | 重定向原因编码 |

**redirect_reason 编码**：

| 编码 | 原因 | 触发场景 |
|------|------|----------|
| 0 | NONE | 无重定向 |
| 1 | BRANCH | 条件分支 taken/mispredict |
| 2 | JAL | 无条件跳转 (JAL/JALR) |
| 3 | TRAP | 陷阱 (ECALL/EBREAK) |
| 4 | MRET | 从陷阱返回 |
| 5 | INTERRUPT | WB 阶段中断 |

### Core-SOC 消息通道架构

**关键设计原则**：
1. **分离规则**: Load 和非Load 包由独立规则处理
2. **FIFOF 通道**: 跨模块通信使用 FIFOF，避免方法调用循环
3. **BypassFIFOF**: 响应 FIFO 使用 mkBypassFIFOF 支持同周期读写
4. **Load-only 响应**: 只为 Load 请求发送响应，隔离 Store 响应

### 定时器中断架构

**关键修复**：
1. CSR mip 直接从 Wire 读取（组合逻辑），不依赖规则更新
2. Core 添加 drive_interrupts 规则每周期驱动中断信号
3. CLINT mtime 每周期自动递增

### 关键文件

| 文件 | 作用 |
|------|------|
| `src/core/Core.bsv` | 流水线核心，规则调度，控制流重定向 |
| `src/soc/SOC.bsv` | SOC 集成，FIFOF 消息通道，外设连接 |
| `src/core/CSR.bsv` | CSR 寄存器，中断 Wire 直连 |
| `src/peripheral/CLINT.bsv` | 定时器，mtime 自动递增 |

## 已实现指令

### RV32I 指令集

| 类型 | 指令 | 状态 |
|------|------|------|
| **R-Type** | ADD, SUB, SLL, SRL, SRA, SLT, SLTU, AND, OR, XOR | ✓ |
| **I-Type ALU** | ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI | ✓ |
| **I-Type Load** | LB, LH, LW, LBU, LHU | ✓ |
| **S-Type** | SB, SH, SW | ✓ |
| **B-Type** | BEQ, BNE, BLT, BGE, BLTU, BGEU | ✓ |
| **U-Type** | LUI, AUIPC | ✓ |
| **J-Type** | JAL, JALR | ✓ |

### 特权指令 (Zicsr)

| 指令 | 状态 |
|------|------|
| CSRRW, CSRRS, CSRRC | ✓ |
| CSRRWI, CSRRSI, CSRRCI | ✓ |
| ECALL, EBREAK | ✓ |
| MRET | ✓ |

## 已实现 CSR

| 地址 | 名称 | 说明 |
|------|------|------|
| 0x300 | mstatus | 机器状态 |
| 0x301 | misa | 机器 ISA |
| 0x304 | mie | 中断使能 |
| 0x305 | mtvec | 陷阱向量 |
| 0x341 | mepc | 异常 PC |
| 0x342 | mcause | 异常原因 |
| 0x343 | mtval | 陷阱值 |
| 0x344 | mip | 中断挂起（Wire 直连） |
| 0xB00 | mcycle | 周期计数 |
| 0xB03 | minstret | 指令计数 |

## 已验证功能

- [x] 五级流水线
- [x] 数据前递
- [x] Load-Use 冒险处理
- [x] 控制流重定向协议
- [x] 动态分支预测 (BHT + BTB)
- [x] RV32I 全指令集
- [x] CSR 寄存器和特权指令
- [x] 陷阱处理
- [x] SOC 架构 (Core ↔ SOC ↔ 外设)
- [x] CLINT/PLIC/UART 外设
- [x] **定时器中断（mtime 递增 + MTIP 触发）**
- [x] **12 个测试全部通过**

## 内存配置

| 内存 | 大小 | 基址 |
|------|------|------|
| IMem | 4KB | 0x80000000 |
| DMem | 8KB | 0x80000000+ |
| tohost | 1 word | 0x80001000 |

**外设地址映射**：

| 外设 | 地址范围 |
|------|----------|
| CLINT | 0x02000000-0x0200FFFF |
| PLIC | 0x0C000000-0x0C0FFFFF |
| UART | 0x10000000-0x10000FFF |

## 注意事项

- x0 寄存器硬连线为 0，不参与前递
- 编译汇编必须禁用压缩指令: `-march=rv32i_zicsr`
- 测试程序必须包含 `sw xN, 0(xM)` 写入 0x80001000 (tohost)
- **BSV 规则调度**: 方法调用会创建隐式条件，使用 FIFOF 通道避免跨模块死锁
- **定时器中断**: mip 从 Wire 直接读取（组合逻辑），不依赖规则

## 开发阶段

### 阶段 1-8（全部完成）

1. ✓ 五级流水线 + 数据前递
2. ✓ Load-Use 冒险处理
3. ✓ 分支预测 + 预测失败处理
4. ✓ RV32I 全指令集
5. ✓ CSR + 特权指令 + 陷阱处理
6. ✓ SOC 架构 + 外设框架
7. ✓ 控制流重定向协议重构
8. ✓ **定时器中断支持**

## 相关文档

- `docs/architecture.md` - 流水线架构、分支预测、内存布局
- `docs/debugging-lessons.md` - 调试经验
- `docs/testing-guide.md` - 测试指南

---

请用"架构/协议审查"的方式分析 CPU/SoC 问题，而不是补丁式调 bug。

要求：
1. 先判断这是实现 bug 还是协议/架构 bug
2. 优先从协议缺失、状态机不完备、职责边界不清的角度分析
3. 不要优先建议"多 stall 一拍""增加特判"等补丁式修复
4. 优先给出"最小正确架构"