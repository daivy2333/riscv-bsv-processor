# RISC-V BSV 五级流水线处理器

基于 Bluespec SystemVerilog 实现的 RISC-V RV32I 五级流水线处理器。

## 特性

- ✅ 五级流水线 (IF → ID → EX → MEM → WB)
- ✅ 数据前递 (EX→EX, MEM→EX, WB→EX)
- ✅ Load-Use 冒险检测 + Stall
- ✅ 动态分支预测 (BHT + BTB)
- ✅ 基本指令集 (ADD, ADDI, LUI, LW, SW, BEQ, JAL 等)
- ✅ 字节/半字访问 (LB/LH/SB/SH)
- ✅ Verilator 仿真验证

## 项目结构

```
riscv-bsv-processor/
├── Makefile                  # 构建脚本
├── CLAUDE.md                 # 项目指南
├── docs/                     # 设计文档
│   ├── cpu-pipeline-architecture.md
│   ├── data-forwarding.md
│   ├── load-use-hazard.md
│   └── branch-prediction.md
├── firmware/                 # 编译后的固件
│   └── pipeline_test.hex     # 测试程序
├── scripts/
│   └── link.ld               # 链接脚本
├── src/
│   ├── common/
│   │   └── Types.bsv         # 类型定义
│   ├── core/
│   │   ├── Core.bsv          # 流水线核心
│   │   ├── ALU.bsv           # 算术逻辑单元
│   │   ├── Decoder.bsv       # 指令解码
│   │   ├── RegFile.bsv       # 寄存器文件
│   │   └── HazardUnit.bsv    # 冒险检测
│   ├── branch/
│   │   ├── BHT.bsv           # 分支历史表
│   │   └── BTB.bsv           # 分支目标缓冲
│   └── soc/
│       ├── TestBench.bsv     # 测试平台
│       └── TestProgram.bsv   # 测试程序
├── tests/
│   ├── assembly/             # 汇编测试
│   │   └ pipeline_test.s
│   └ c/                      # C++仿真驱动
│   │   └ test_bench.cpp
│   └ verification/           # 验证脚本
└── tools/
    └── hex_to_bsv.py         # Hex转BSV工具
```

## 快速开始

### 环境要求

- BSC (Bluespec Compiler)
- riscv64-unknown-elf-gcc
- Verilator 4.x

### 编译运行

```bash
# 编译 BSV
make compile

# 运行测试
make test

# 输出示例
# ====================================
#   Pipeline Test Results
# ====================================
# Cycles: 52
# Register dump:
#   x1  (ra)  = 10 (expected 10)
#   x2  (sp)  = 20 (expected 20)
#   x3  (gp)  = 30 (expected 30)
#   x4  (tp)  = 40 (expected 40)
#   x5  (t0)  = 70 (expected 70)
#   x31 (t6)  = 57005 (expected 0xDEAD)
```

### 添加新测试

```bash
# 1. 编写汇编
vim tests/assembly/my_test.s

# 2. 编译
make firmware/my_test.hex

# 3. 生成 BSV
python3 tools/hex_to_bsv.py firmware/my_test.hex > src/soc/TestProgram.bsv

# 4. 修改结束条件
vim src/soc/TestBench.bsv

# 5. 运行
make test
```

## 架构概览

### 流水线阶段

| 阶段 | 功能 |
|------|------|
| IF | 取指 + 分支预测 (BHT/BTB) |
| ID | 解码 + 冒险检测 + 寄存器读取 |
| EX | ALU执行 + 前递选择 + 分支判断 |
| MEM | 内存访问 + tohost检测 |
| WB | 寄存器写回 |

### 冒险处理

- **数据冒险**: 三级前递 (EX→EX, MEM→EX, WB→EX)
- **Load-Use**: ID检测 → stall + 气泡插入
- **控制冒险**: BHT动态预测 + BTB目标缓存

## 内存布局

| 区域 | 基址 | 大小 |
|------|------|------|
| IMem | 0x80000000 | 4KB |
| DMem | - | 2KB |
| tohost | 0x80001000 | 1 word |

## 已验证测试

| 测试 | 内容 | 结果 |
|------|------|------|
| pipeline_test | 前递+Load-Use+分支+循环 | ✓ |
| rtype_test | SUB/SLL/SRL/SRA/SLT/AND/OR/XOR | ✓ |

## 开发路线

### 阶段 2 (计划)

- 更多指令 (SUB, SLL, SRL, AND, OR, XOR)
- riscv-tests 官方测试
- 性能计数器

### 阶段 3-4

- 特权级架构 (M/S/U)
- CSR 寄存器
- 异常/中断

### 阶段 5+

- FreeRTOS/uClinux 支持

## 文档

详细设计文档见 `docs/` 目录。

## 许可证

MIT License