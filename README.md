# RISC-V BSV 五级流水线处理器

基于 Bluespec SystemVerilog 实现的 RISC-V RV32I 五级流水线处理器，目标支持 FreeRTOS/uClinux。

## 特性

- ✅ 五级流水线 (IF → ID → EX → MEM → WB)
- ✅ 数据前递 (MEM→EX, WB→EX, WB→ID)
- ✅ Load-Use 冒险检测 + Stall
- ✅ 动态分支预测 (BHT + BTB) + 预测失败处理
- ✅ RV32I 全指令集 (R/I/S/B/U/J-Type)
- ✅ 字节/半字访问 (LB/LH/SB/SH)
- ✅ 特权级架构 (M-mode)
- ✅ CSR 寄存器 (mstatus, mie, mip, mtvec, mepc, mcause, mtval, mcycle, mtime, mtimecmp, minstret)
- ✅ CSR 指令 (CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI)
- ✅ 陷阱处理 (ECALL, EBREAK, MRET)
- ✅ CLINT 定时器 (mtime, mtimecmp)
- ✅ Verilator 仿真验证 (11 tests passing)

## 项目结构

```
riscv-bsv-processor/
├── Makefile                  # 构建脚本
├── CLAUDE.md                 # 项目指南（详细）
├── docs/                     # 设计文档
│   ├── cpu-pipeline-architecture.md  # 流水线架构
│   ├── branch-prediction.md           # 分支预测机制
│   ├── load-use-hazard.md             # 冒险检测
│   ├── debugging-lessons.md           # 调试经验
│   └ roadmap-embedded-os.md           # 开发路线图
├── firmware/                 # 编译后的固件
│   └ *.hex                   # 测试程序
├── src/
│   ├── common/
│   │   └ Types.bsv           # 类型定义 + 数据包
│   ├── core/
│   │   ├── Core.bsv          # 流水线核心
│   │   ├── ALU.bsv           # 算术逻辑单元
│   │   ├── Decoder.bsv       # 指令解码
│   │   ├── RegFile.bsv       # 寄存器文件
│   │   ├── CSR.bsv           # CSR 寄存器
│   │   ├── HazardUnit.bsv    # 冒险检测
│   │   └── PrivilegedTypes.bsv # 特权级类型
│   ├── branch/
│   │   ├── BHT.bsv           # 分支历史表
│   │   └ BTB.bsv             # 分支目标缓冲
│   └── soc/
│       ├── TestBench.bsv     # 测试平台
│       └ TestProgram.bsv     # 测试程序
├── tests/
│   ├── assembly/             # 汇编测试 (*.s)
│   └ c/                      # C++仿真驱动
│   │   └ test_bench.cpp
└── tools/
    └ hex_to_bsv.py           # Hex转BSV工具
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
#   Test Results: PASSED
# ====================================
# Cycles: 70
# Final PC: 0x80000024
```

### 添加新测试

```bash
# 1. 编写汇编
vim tests/assembly/my_test.s

# 2. 编译（禁用压缩指令）
riscv64-unknown-elf-gcc -march=rv32i_zicsr -mabi=ilp32 \
    -nostdlib -static -T scripts/link.ld \
    tests/assembly/my_test.s -o firmware/my_test.elf

# 3. 生成 hex
riscv64-unknown-elf-objcopy -O verilog firmware/my_test.elf firmware/my_test.hex

# 4. 生成 BSV
python3 tools/hex_to_bsv.py firmware/my_test.hex > src/soc/TestProgram.bsv

# 5. 运行
make test
```

## 架构概览

### 流水线阶段

| 阶段 | 功能 |
|------|------|
| IF | 取指 + 分支预测 (BHT/BTB) |
| ID | 解码 + 冒险检测 + 寄存器读取 |
| EX | ALU执行 + 前递选择 + 分支判断 + CSR操作 |
| MEM | 内存访问 + tohost检测 |
| WB | 寄存器写回 + wb_history更新 |

### 冒险处理

- **数据冒险**: MEM→EX, WB→EX, WB→ID 前递
- **Load-Use**: ID检测 → stall + 气泡插入
- **控制冒险**: BHT动态预测 + BTB目标缓存 + 预测失败冲刷

## 内存布局

| 区域 | 基址 | 大小 |
|------|------|------|
| IMem | 0x80000000 | 4KB |
| DMem | - | 2KB |
| tohost | 0x80001000 | 1 word |

## 已验证测试

| 测试 | 内容 | 结果 |
|------|------|------|
| loop_test | 循环分支 | ✓ PASSED (70 cycles) |
| pipeline_test | 完整流水线 | ✓ PASSED (65 cycles) |
| simple_arith_test | 基本算术 | ✓ PASSED (50 cycles) |
| load_test | Load-Use 冒险 | ✓ PASSED (57 cycles) |
| csr_basic_test | CSR 读写 | ✓ PASSED (58 cycles) |
| privilege_m_mode_test | M-mode CSR | ✓ PASSED (64 cycles) |
| csr_immediate_test | CSR 立即数 | ✓ PASSED (46 cycles) |
| rtype_complete_test | R-Type 全指令集 | ✓ PASSED |
| itype_alu_test | I-Type ALU | ✓ PASSED |
| simple_branch_test | 分支预测 | ✓ PASSED |
| simple_loop | 循环计数 | ✓ PASSED |

**总计**: 11 个测试，全部通过

## 开发路线

### 阶段 1-3 (已完成)

- 五级流水线
- 数据前递 + Load-Use 冒险处理
- 动态分支预测
- RV32I 全指令集验证
- 特权级架构 (M-mode)
- CSR 寄存器模块
- CSR 指令 (Zicsr 扩展)
- 陷阱处理 (ECALL/EBREAK/MRET)

### 阶段 4 (已完成)

- CLINT 定时器 (mtime, mtimecmp 内存映射)
- 分支预测失败处理修复
- 全部测试通过

### 阶段 5+ (待开始)

- PLIC 中断控制器
- UART 控制台
- FreeRTOS/uClinux 支持

## 文档

详细设计文档见 `docs/` 目录：

- `cpu-pipeline-architecture.md` - 流水线架构详解
- `branch-prediction.md` - 分支预测机制
- `debugging-lessons.md` - 棘手问题调试经验
- `roadmap-embedded-os.md` - 开发路线图

## 许可证

MIT License