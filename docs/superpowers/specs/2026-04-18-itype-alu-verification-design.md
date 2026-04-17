# I-Type ALU 指令验证设计

日期: 2026-04-18

## 目标

验证已实现的 9 条 I-Type ALU 指令：
- ADDI, SLTI, SLTIU (比较类)
- ANDI, ORI, XORI (逻辑类)
- SLLI, SRLI, SRAI (移位类)

## 现状分析

Decoder.bsv 和 ALU.bsv 已有完整实现：
- opcode `7'b0010011` 处理 I-Type ALU
- funct3 区分具体操作
- ALUOp 对应正确

需要验证硬件正确性。

## 测试策略

采用单文件覆盖所有指令，类似 `rtype_test.s` 模式。

### 测试文件

`tests/assembly/itype_alu_test.s`

每个指令 2-3 个测试场景：
- 正数、负数、边界值
- 有符号 vs 无符号行为差异（SLTI/SLTIU）
- 逻辑右移 vs 算术右移（SRLI/SRAI）

### 验证流程

1. 编写汇编测试
2. 编译为 hex (`-march=rv32i` 禁用压缩指令)
3. 转换为 BSV TestProgram
4. Verilator 仿真运行
5. 检查 tohost = 1 表示通过

## 测试用例设计

### ADDI - 立即数边界测试
```
# 基本加法
li t0, 100
addi t1, t0, -50    # t1 = 50
addi t2, t1, -60    # t2 = -10

# 立即数边界
li t0, 0
addi t1, t0, 0      # t1 = 0（零值）
addi t2, t0, 2047   # t2 = 2047（最大正立即数）
addi t3, t0, -2048  # t3 = -2048（最小负立即数）

# 溢出测试
li t0, 0x7FFFFFFF
addi t1, t0, 1      # t1 = 0x80000000（正+正=负，溢出）
```

### SLTI / SLTIU - 有符号/无符号比较完整测试
```
# SLTI 有符号比较
li t0, -1           # 0xFFFFFFFF
slti t1, t0, 0      # t1 = 1（-1 < 0）
slti t2, t0, 1      # t2 = 1（-1 < 1）

li t0, 0
slti t1, t0, 1      # t1 = 1（0 < 1）
slti t2, t0, 0      # t2 = 0（0 < 0 为假）
slti t3, t0, -1     # t3 = 0（0 < -1 为假）

# SLTIU 无符号比较
li t0, -1           # 0xFFFFFFFF = MAX_UINT
sltiu t1, t0, 0     # t1 = 0（MAX_UINT < 0 为假）
sltiu t2, t0, 1     # t2 = 0（MAX_UINT < 1 为假）

li t0, 0
sltiu t1, t0, 1     # t1 = 1（0 < 1）
sltiu t2, t0, 0     # t2 = 0（0 < 0 为假）

# 有符号 vs 无符号差异
li t0, 1            # rs1 = 1
slti t1, t0, -2     # t1 = 1（1 < -2，有符号）
sltiu t2, t0, -2    # t2 = 0（1 < MAX_UINT-1，无符号）
```

### ANDI / ORI / XORI - 逻辑操作含负立即数
```
# ANDI 立即数边界
li t0, 0xFF
andi t1, t0, 0x0F   # t1 = 0x0F（正常）
andi t2, t0, 0xFFF  # t2 = 0xFF（高 8 位被 mask）
andi t3, t0, 0      # t3 = 0（零立即数）

# ORI 负立即数测试
li t0, 0
ori t1, t0, 0xF0F   # t1 = 0xF0F
ori t2, t0, -1      # t2 = 0xFFFFFFFF（立即数符号扩展）

# XORI 负立即数测试
li t0, 0xFF
xori t1, t0, 0xFF   # t1 = 0（正常）
xori t2, t0, 0xFFF  # t2 = 0xF00（高 12 位翻转）
xori t3, t0, -1     # t3 = 0xFFFFFF00（全部位翻转）
```

### SLLI / SRLI / SRAI - 移位边界测试
```
# SLLI 边界
li t0, 1
slli t1, t0, 0      # t1 = 1（不移位）
slli t2, t0, 4      # t2 = 16（正常移位）
slli t3, t0, 31     # t3 = 0x80000000（最大移位）

# SRLI 边界
li t0, 0xFFFFFFFF
srli t1, t0, 0      # t1 = 0xFFFFFFFF（不移位）
srli t2, t0, 4      # t2 = 0x0FFFFFFF（逻辑右移，填 0）
srli t3, t0, 31     # t3 = 1（最大移位）

# SRAI 正数测试（符号位为 0，移位后填 0）
li t0, 0x7FFFFFFF
srai t1, t0, 0      # t1 = 0x7FFFFFFF（不移位）
srai t2, t0, 4      # t2 = 0x07FFFFFF（0 填充）

# SRAI 负数测试（符号位为 1，移位后填 1）
li t0, 0x80000000
srai t1, t0, 0      # t1 = 0x80000000（不移位）
srai t2, t0, 4      # t2 = 0xF8000000（1 填充）
srai t3, t0, 31     # t3 = 0xFFFFFFFF（最大移位，全 1）
```

## 预期结果

仿真输出：
```
Cycle X: tohost write detected! Value = 0x1
Test passed!
```

## 风险点

1. **立即数符号扩展**：I-Type 立即数为 12 位有符号，需确认 Decoder 正确扩展。测试用例已覆盖边界值。

2. **移位量截取**：
   - 指令编码中：shamt = instruction[25:20]（6 位，但 RV32I 只用低 5 位）
   - BSV 实现中：通过 `signExtendI` 扩展为 32 位，ALU 使用 `operand2[4:0]`
   - 测试用例已覆盖移位量 0 和 31 的边界

3. **SRAI 符号扩展**：算术右移必须保持符号位。测试用例已覆盖正数和负数的算术右移。

## 完整测试文件

```assembly
# tests/assembly/itype_alu_test.s
# I-Type ALU 指令验证测试 (9 条指令)

.globl _start
.section .text

.equ tohost, 0x80001000

_start:
    # ========== ADDI 测试 ==========
    # 基本加法
    li   t0, 100
    addi t1, t0, -50      # t1 = 50
    li   t2, 50
    bne  t1, t2, fail

    # 立即数边界
    li   t0, 0
    addi t1, t0, 0        # t1 = 0（零值）
    bnez t1, fail

    addi t1, t0, 2047     # t1 = 2047（最大正立即数）
    li   t2, 2047
    bne  t1, t2, fail

    addi t1, t0, -2048    # t1 = -2048（最小负立即数）
    li   t2, -2048
    bne  t1, t2, fail

    # 溢出测试
    li   t0, 0x7FFFFFFF
    addi t1, t0, 1        # t1 = 0x80000000
    li   t2, 0x80000000
    bne  t1, t2, fail

    # ========== SLTI/SLTIU 测试 ==========
    # 有符号比较
    li   t0, -1           # 0xFFFFFFFF
    slti t1, t0, 0        # t1 = 1（-1 < 0）
    li   t2, 1
    bne  t1, t2, fail

    slti t1, t0, 1        # t1 = 1（-1 < 1）
    bne  t1, t2, fail

    li   t0, 0
    slti t1, t0, 1        # t1 = 1（0 < 1）
    bne  t1, t2, fail

    slti t1, t0, 0        # t1 = 0（0 < 0 为假）
    bnez t1, fail

    slti t1, t0, -1       # t1 = 0（0 < -1 为假）
    bnez t1, fail

    # 无符号比较
    li   t0, -1           # 0xFFFFFFFF = MAX_UINT
    sltiu t1, t0, 0       # t1 = 0（MAX_UINT < 0 为假）
    bnez t1, fail

    sltiu t1, t0, 1       # t1 = 0（MAX_UINT < 1 为假）
    bnez t1, fail

    li   t0, 0
    sltiu t1, t0, 1       # t1 = 1（0 < 1）
    li   t2, 1
    bne  t1, t2, fail

    sltiu t1, t0, 0       # t1 = 0（0 < 0 为假）
    bnez t1, fail

    # 有符号 vs 无符号差异
    li   t0, 1
    slti t1, t0, -2       # t1 = 1（1 < -2，有符号）
    bne  t1, t2, fail

    sltiu t1, t0, -2      # t1 = 0（1 < MAX_UINT-1，无符号）
    bnez t1, fail

    # ========== 移位指令测试 ==========
    # SLLI 边界
    li   t0, 1
    slli t1, t0, 0        # t1 = 1（不移位）
    bne  t1, t0, fail

    slli t1, t0, 4        # t1 = 16
    li   t2, 16
    bne  t1, t2, fail

    slli t1, t0, 31       # t1 = 0x80000000
    li   t2, 0x80000000
    bne  t1, t2, fail

    # SRLI 边界
    li   t0, 0xFFFFFFFF
    srli t1, t0, 0        # t1 = 0xFFFFFFFF（不移位）
    bne  t1, t0, fail

    srli t1, t0, 4        # t1 = 0x0FFFFFFF
    li   t2, 0x0FFFFFFF
    bne  t1, t2, fail

    srli t1, t0, 31       # t1 = 1
    li   t2, 1
    bne  t1, t2, fail

    # SRAI 正数测试（符号位为 0）
    li   t0, 0x7FFFFFFF
    srai t1, t0, 0        # t1 = 0x7FFFFFFF（不移位）
    bne  t1, t0, fail

    srai t1, t0, 4        # t1 = 0x07FFFFFF（0 填充）
    li   t2, 0x07FFFFFF
    bne  t1, t2, fail

    # SRAI 负数测试（符号位为 1）
    li   t0, 0x80000000
    srai t1, t0, 0        # t1 = 0x80000000（不移位）
    bne  t1, t0, fail

    srai t1, t0, 4        # t1 = 0xF8000000（1 填充）
    li   t2, 0xF8000000
    bne  t1, t2, fail

    srai t1, t0, 31       # t1 = 0xFFFFFFFF（全 1）
    li   t2, 0xFFFFFFFF
    bne  t1, t2, fail

    # ========== 逻辑指令测试 ==========
    # ANDI
    li   t0, 0xFF
    andi t1, t0, 0x0F     # t1 = 0x0F
    li   t2, 0x0F
    bne  t1, t2, fail

    andi t1, t0, 0xFFF    # t1 = 0xFF（高 8 位被 mask）
    bne  t1, t0, fail

    andi t1, t0, 0        # t1 = 0
    bnez t1, fail

    # ORI
    li   t0, 0
    ori  t1, t0, 0xF0F    # t1 = 0xF0F
    li   t2, 0xF0F
    bne  t1, t2, fail

    ori  t1, t0, -1       # t1 = 0xFFFFFFFF
    li   t2, 0xFFFFFFFF
    bne  t1, t2, fail

    # XORI
    li   t0, 0xFF
    xori t1, t0, 0xFF     # t1 = 0
    bnez t1, fail

    xori t1, t0, 0xFFF    # t1 = 0xF00（高 12 位翻转）
    li   t2, 0xF00
    bne  t1, t2, fail

    xori t1, t0, -1       # t1 = 0xFFFFFF00
    li   t2, 0xFFFFFF00
    bne  t1, t2, fail

    # ========== 测试通过 ==========
    li   t0, 1
    li   t5, tohost
    sw   t0, 0(t5)        # tohost = 1

pass:
    jal  zero, pass

fail:
    li   t0, 0xFF
    li   t5, tohost
    sw   t0, 0(t5)        # tohost = 0xFF（失败）
    jal  zero, fail
```

## 后续

验证通过后：
- 更新 CLAUDE.md 已验证列表
- 继续阶段 2 任务 3：运行 riscv-tests