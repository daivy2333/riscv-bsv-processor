# CLAUDE.md

Claude Code 项目指南。

## 项目概述

RISC-V RV32I 五级流水线处理器，使用 BSV 实现，Verilator 仿真。目标是支持 FreeRTOS/uClinux。

**当前状态**: 阶段 1-7 全部完成，G0021 核心问题已彻底解决，架构稳定。

## 构建命令

```bash
# BSV 编译
/opt/bsc/bin/bsc -verilog -p src:src/common:src/core:src/memory:src/soc:src/branch:src/peripheral:%/Libraries -no-warn-action-shadowing -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS

# Verilator 构建+运行
rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench --top-module mkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH && ./obj_dir/VmkTestBench

# 快速测试（单个测试）
python3 tools/hex_to_bsv.py firmware/loop_test.hex > src/soc/TestProgram.bsv
# 然后编译和运行

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

# 2. 编译为 hex（禁用压缩指令，启用 zicsr）
riscv64-unknown-elf-gcc -march=rv32i_zicsr -mabi=ilp32 -nostdlib -T scripts/link.ld tests/assembly/new_test.s -o firmware/new_test.elf
riscv64-unknown-elf-objcopy -O verilog firmware/new_test.elf firmware/new_test.hex

# 3. 生成 BSV 测试程序
python3 tools/hex_to_bsv.py firmware/new_test.hex > src/soc/TestProgram.bsv

# 4. 编译和运行
/opt/bsc/bin/bsc -verilog -p src:... -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv
rm -rf obj_dir && verilator --cc --exe --build ... && ./obj_dir/VmkTestBench
```

### 现有测试

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

**总计**: 10 个测试，全部通过 ✓

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

**协议流程**：

```
EX/WB 阶段检测重定向需求
    ↓ 设置 redirect_pending + redirect_target + redirect_reason
    ↓ 清空被污染的流水段 (if2id, id2ex)
fetchStage 看到 redirect_pending
    ↓ 等待（不取指）
consumeRedirect 规则触发
    ↓ 清除 redirect_pending
    ↓ 下一周期恢复正常取指
```

### Core-SOC 消息通道架构（G0021 解决方案）

**问题根因**: BSV 方法调用会自动成为规则的隐式条件，导致跨模块规则死锁。

**解决方案**: FIFOF 消息通道架构

```
Core                    SOC
  │                       │
  │──── sendMemReq() ───→ │ 请求 FIFOF
  │                       │ handle_mem_req (内部规则)
  │                       │
  │←── hasMemResp() ─────│ 响应 FIFOF
  │←── peekMemResp() ────│
  │                       │
  │  writebackStage       │
  │  ├─ nonLoad 规则      │ 不依赖响应 FIFOF
  │  └─ Load 规则         │ 显式依赖 hasMemResp()
```

**关键设计原则**：
1. **分离规则**: Load 和非Load 包由独立规则处理
2. **FIFOF 通道**: 跨模块通信使用 FIFOF，避免方法调用循环
3. **显式条件**: 在规则显式条件中检查 FIFOF 状态，而非规则内部 if 分支

### 关键文件

| 文件 | 作用 |
|------|------|
| `src/core/Core.bsv` | 流水线核心，规则调度，控制流重定向 |
| `src/soc/SOC.bsv` | SOC 集成，FIFOF 消息通道，外设连接 |
| `src/soc/TestBench.bsv` | 仿真测试台 |
| `src/common/Types.bsv` | 数据包定义 |
| `src/core/Decoder.bsv` | 指令解码 |
| `src/core/CSR.bsv` | CSR 寄存器 |
| `src/branch/BHT.bsv` | 分支历史表 |
| `src/branch/BTB.bsv` | 分支目标缓冲 |

### 数据前递

| 前递路径 | 数据来源 | 优先级 |
|----------|----------|--------|
| MEM→EX | ex2mem.first (缓存) | 高 |
| WB→EX | mem2wb.first (缓存) | 中 |
| WB→EX (历史) | wb_forward_data0/1 | 低 |

### Load-Use 冒险处理

```
周期 N:   Load 进入 EX
周期 N:   ID 检测冒险 → stall=1, count=2
周期 N+1: decrementStall → count=1
周期 N+2: decrementStall → count=0 → stall=0
周期 N+3: Load 在 WB → 前递可用
```

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
| 0x344 | mip | 中断挂起 |
| 0xB00 | mcycle | 周期计数 |
| 0xB03 | minstret | 指令计数 |

## 已验证功能

- [x] 五级流水线
- [x] 数据前递
- [x] Load-Use 冒险处理
- [x] 控制流重定向协议（统一处理分支/JAL/trap/MRET/中断）
- [x] 动态分支预测 (BHT + BTB)
- [x] RV32I 全指令集
- [x] CSR 寄存器和特权指令
- [x] 陷阱处理
- [x] SOC 架构 (Core ↔ SOC ↔ 外设)
- [x] CLINT/PLIC/UART 外设框架
- [x] 10 个基线测试通过
- [x] 稳定性测试通过 (10⁵+ 周期)
- [x] **G0021 BSV 规则调度问题彻底解决**

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
- **控制流重定向**: 使用统一的 `redirect_pending/target/reason` 协议
- **BSV 规则调度**: 方法调用会创建隐式条件，使用 FIFOF 通道避免跨模块死锁
- **分离规则**: Load 和非Load 包由独立规则处理

## 开发阶段

### 阶段 1-7（全部完成）

1. ✓ 五级流水线 + 数据前递
2. ✓ Load-Use 冒险处理
3. ✓ 分支预测 + 预测失败处理
4. ✓ RV32I 全指令集
5. ✓ CSR + 特权指令 + 陷阱处理
6. ✓ SOC 架构 + 外设框架
7. ✓ 控制流重定向协议重构
8. ✓ **G0021 规则调度问题彻底解决**

### 阶段 6：FreeRTOS 支持（架构就绪）

| 任务 | 状态 |
|------|------|
| FreeRTOS demo 执行 | ✓ 基础运行（BSS清零、UART输出） |
| 中断连接修复 | ✓ 已解决（G0021 问题根因） |
| 定时器中断 | 架构就绪 |
| 任务调度验证 | 架构就绪 |

**当前状态**: 
- 处理器架构完整稳定
- 所有基线测试通过
- 无 BSV 编译警告
- FreeRTOS 基础运行验证
- 中断架构就绪

## 相关文档

- `docs/debugging-lessons.md` - 调试经验（含 G0021 解决方案）
- `docs/testing-guide.md` - 测试指南
- `docs/branch-prediction.md` - 分支预测机制
- `docs/cpu-pipeline-architecture.md` - 流水线架构

---

请用"架构/协议审查"的方式分析 CPU/SoC 问题，而不是补丁式调 bug。

要求：
1. 先判断这是实现 bug 还是协议/架构 bug
2. 优先从协议缺失、状态机不完备、职责边界不清的角度分析
3. 不要优先建议"多 stall 一拍""增加特判"等补丁式修复
4. 优先给出"最小正确架构"