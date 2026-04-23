# 测试指南

## 快速测试命令

```bash
# 运行单个测试
make test-loop_test

# 运行所有基线测试（10个）
make test-baseline

# 运行定时器中断测试（2个）
make test-timer

# 运行所有测试（12个）
make test-all

# 运行 Mini-OS Demo
make test-mini-os

# 查看帮助
make help
```

## 汇编测试流程

```
汇编测试 (tests/assembly/*.s)
    ↓ make asm-<name>
Hex 文件
    ↓ make test-<name>
Verilator 仿真
    ↓ 
测试结果（检查 tohost 写入）
```

## Mini-OS 测试

Mini-OS 用于验证 CPU 的任务调度和中断处理功能。

```bash
make test-mini-os
```

### 验证内容

| 功能 | 验证方法 |
|------|----------|
| 任务调度 | Round-Robin，3个任务轮流执行 |
| 定时器中断 | CLINT mtimecmp 触发 Timer IRQ |
| UART 输出 | 任务通过 UART 打印状态 |
| 上下文切换 | Trap 处理保存/恢复寄存器 |
| ECALL | 任务主动让出 CPU |

### Mini-OS 架构

- **栈帧**: 128 bytes (32 words)
- **调度**: Round-Robin，固定顺序轮流
- **中断**: Timer IRQ (mcause=0x80000007)
- **任务切换**: ECALL (mcause=11)

## 测试状态

### 基线测试（10个）

| 测试 | 说明 |
|------|------|
| loop_test | 循环 + 分支预测 |
| simple_arith_test | 基本算术 |
| load_test | Load-Use 冒险 |
| csr_basic_test | CSR 读写 |
| privilege_m_mode_test | M-mode CSR |
| csr_immediate_test | CSR 立即数指令 |
| rtype_complete_test | R-Type 全指令 |
| itype_alu_test | I-Type ALU |
| simple_branch_test | 分支预测执行 |
| simple_loop | 循环计数 |

### 定时器中断测试（2个）

| 测试 | 说明 |
|------|------|
| mtime_increment_verify | mtime 每周期递增 |
| mtimecmp_mtip_test | MTIP 定时器中断触发 |

### Mini-OS

| 功能 | 状态 |
|------|------|
| 任务创建 | ✓ |
| Round-Robin 调度 | ✓ |
| 定时器中断 | ✓ |
| UART 输出 | ✓ |
| 上下文切换 | ✓ |

## 注意事项

| 项目 | 要求 |
|------|------|
| 编译选项 | `-march=rv32i_zicsr`（禁用压缩指令） |
| 地址对齐 | 字: addr[1:0]=0, 半字: addr[0]=0 |
| 结束标记 | **必须**写入 tohost (0x80001000) |