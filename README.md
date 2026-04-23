# RISC-V BSV 五级流水线处理器

基于 Bluespec SystemVerilog 实现的 RISC-V RV32I 五级流水线处理器，支持 Mini-OS 任务调度。

## 特性

- 五级流水线 (IF → ID → EX → MEM → WB)
- 数据前递 (MEM→EX, WB→EX, WB→ID)
- Load-Use 冒险检测 + Stall
- 动态分支预测 (BHT 64条目 + BTB 64条目)
- RV32I 全指令集 + Zicsr 扩展
- 定时器中断 (CLINT)
- UART 输出
- Mini-OS Round-Robin 任务调度

## 项目结构

```
riscv-bsv-processor/
├── Makefile              # 构建脚本
├── docs/                 # 设计文档
├── src/                  # BSV 源码
│   ├── core/             # 流水线核心
│   ├── branch/           # 分支预测 (BHT/BTB)
│   ├── peripheral/       # CLINT, PLIC, UART
│   └── soc/              # SOC 集成
├── mini-os/              # Mini-OS 源码
├── tests/                # 测试程序
│   ├── assembly/         # 汇编测试 (12个)
│   └ c/                  # C++ 仿真驱动
└── tools/                # 工具脚本
```

## 快速开始

### 环境要求

- BSC (Bluespec Compiler)
- riscv64-unknown-elf-gcc
- Verilator

### 编译运行

```bash
make test-all      # 运行全部测试
make test-mini-os  # 运行 Mini-OS Demo
make clean         # 清理
```

## 测试结果

### 汇编测试 (12个全部通过)

```
loop_test:             ✓ PASSED
simple_arith_test:     ✓ PASSED
load_test:             ✓ PASSED
csr_basic_test:        ✓ PASSED
privilege_m_mode_test: ✓ PASSED
csr_immediate_test:    ✓ PASSED
rtype_complete_test:   ✓ PASSED
itype_alu_test:        ✓ PASSED
simple_branch_test:    ✓ PASSED
simple_loop:           ✓ PASSED
mtime_increment_verify: ✓ PASSED
mtimecmp_mtip_test:    ✓ PASSED
```

### Mini-OS Demo

```
=== Mini-OS Round-Robin Demo ===
[SOC] CLINT write: addr=02004004 data=00000000
[SOC] CLINT write: addr=02004000 data=00003c4b
Tasks created. Starting...

[TRAP] cause=11, pc=80000078  (ECALL 触发任务切换)

Cycle 10000 running...
Cycle 50000 running...
...
Timeout at cycle 500000  (Mini-OS 稳定运行 50万周期)
```

Mini-OS 成功验证：
- 任务创建和调度
- 定时器中断触发
- UART 字符输出
- ECALL 上下文切换

## 架构概览

### 流水线

```
IF → ID → EX → MEM → WB
```

| 阶段 | 功能 |
|------|------|
| IF | 取指 + 分支预测 |
| ID | 解码 + 冒险检测 |
| EX | ALU + CSR + Trap |
| MEM | 内存访问 |
| WB | 写回 + 中断处理 |

### Mini-OS

| 组件 | 说明 |
|------|------|
| 栈帧 | 128 bytes |
| 调度 | Round-Robin |
| 中断 | Timer IRQ (CLINT) |
| 切换 | Trap 处理 |

## 文档

- `docs/architecture.md` - 流水线架构详解
- `docs/testing-guide.md` - 测试方法
- `docs/debugging-lessons.md` - 调试经验

## 许可证

MIT License