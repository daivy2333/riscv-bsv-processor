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

### ADDI
```
li t0, 100
addi t1, t0, -50    # t1 = 50
addi t2, t1, -60    # t2 = -10
```

### SLTI / SLTIU
```
li t0, -1           # 0xFFFFFFFF
slti t1, t0, 0      # t1 = 1 (有符号: -1 < 0)
sltiu t2, t0, 0     # t2 = 0 (无符号: MAX_UINT > 0)
```

### ANDI / ORI / XORI
```
li t0, 0xFF
andi t1, t0, 0x0F   # t1 = 0x0F
ori t2, t0, 0xF0    # t2 = 0xFF
xori t3, t0, 0xFF   # t3 = 0
```

### SLLI / SRLI / SRAI
```
li t0, 1
slli t1, t0, 4      # t1 = 16

li t0, 0x80000000
srli t2, t0, 4      # t2 = 0x08000000 (逻辑右移，填0)
srai t3, t0, 4      # t3 = 0xF8000000 (算术右移，填符号位)
```

## 预期结果

仿真输出：
```
Cycle X: tohost write detected! Value = 0x1
Test passed!
```

## 风险点

1. **立即数符号扩展**：I-Type 立即数为 12 位有符号，需确认 Decoder 正确扩展
2. **移位量截取**：SLLI/SRLI/SRAI 的移位量应取 `shamt[4:0]`（5 位，最大 31）
3. **SRAI 符号扩展**：算术右移必须保持符号位

## 后续

验证通过后：
- 更新 CLAUDE.md 已验证列表
- 继续阶段 2 任务 3：运行 riscv-tests