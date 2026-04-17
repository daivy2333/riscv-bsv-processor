# I-Type ALU 指令验证实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 验证 9 条 I-Type ALU 指令 (ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI) 的硬件实现正确性

**Architecture:** 编写边界覆盖的汇编测试，编译为 hex，转换为 BSV 测试程序，运行 Verilator 仿真验证 tohost 输出

**Tech Stack:** RISC-V 汇编, riscv64-unknown-elf-gcc, Python hex 转换工具, Verilator 仿真

---

## 文件结构

| 文件 | 责任 |
|------|------|
| `tests/assembly/itype_alu_test.s` | 创建 - I-Type ALU 边界测试汇编源文件 |
| `firmware/itype_alu_test.hex` | 创建 - 编译生成的 hex 文件 |
| `src/soc/TestProgram.bsv` | 修改 - 自动生成的测试程序内存初始化 |
| `docs/superpowers/specs/2026-04-18-itype-alu-verification-design.md` | 参考 - 测试用例设计 |

---

### Task 1: 编写汇编测试文件

**Files:**
- Create: `tests/assembly/itype_alu_test.s`

- [ ] **Step 1: 创建测试文件**

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

- [ ] **Step 2: 提交测试文件**

```bash
git add tests/assembly/itype_alu_test.s
git commit -m "test: 添加 I-Type ALU 指令边界测试汇编文件"
```

---

### Task 2: 编译汇编为 hex 文件

**Files:**
- Create: `firmware/itype_alu_test.hex`

- [ ] **Step 1: 编译汇编文件**

检查 link.ld 是否存在：
```bash
ls tests/link.ld
```

如果不存在，使用默认链接脚本参数：
```bash
riscv64-unknown-elf-gcc -march=rv32i -nostdlib -nostartfiles -static \
  -Ttext=0x80000000 -o tests/assembly/itype_alu_test.o tests/assembly/itype_alu_test.s
```

Expected: 生成 itype_alu_test.o 文件

- [ ] **Step 2: 生成 hex 文件**

```bash
riscv64-unknown-elf-objcopy -O verilog tests/assembly/itype_alu_test.o firmware/itype_alu_test.hex
```

Expected: 生成 firmware/itype_alu_test.hex 文件

- [ ] **Step 3: 验证 hex 文件生成**

```bash
head -20 firmware/itype_alu_test.hex
```

Expected: 显示 hex 文件内容，格式为 `@地址 数据`

---

### Task 3: 生成 BSV 测试程序

**Files:**
- Modify: `src/soc/TestProgram.bsv`

- [ ] **Step 1: 运行 hex_to_bsv.py 转换**

```bash
python3 tools/hex_to_bsv.py firmware/itype_alu_test.hex > src/soc/TestProgram.bsv
```

Expected: TestProgram.bsv 文件更新，包含 I-Type ALU 测试指令的内存初始化数据

- [ ] **Step 2: 验证 BSV 文件生成**

```bash
head -30 src/soc/TestProgram.bsv
```

Expected: 显示生成的 BSV 代码，包含 `mkProgramMemory` 模块和内存初始化向量

---

### Task 4: BSV 编译和 Verilator 构建

**Files:**
- Generate: `build/mkTestBench.v`, `obj_dir/VmkTestBench`

- [ ] **Step 1: BSV 编译**

```bash
make compile
```

Expected: 编译成功，生成 build/mkTestBench.v 文件。无错误输出。

- [ ] **Step 2: Verilator 构建**

```bash
rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench --top-module mkTestBench \
  build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp \
  -Wno-STMTDLY -Wno-WIDTH
```

Expected: 编译成功，生成 obj_dir/VmkTestBench 可执行文件

---

### Task 5: 运行仿真验证

**Files:**
- 无新文件，验证输出

- [ ] **Step 1: 运行仿真**

```bash
./obj_dir/VmkTestBench
```

Expected: 输出包含 `Cycle X: tohost write detected! Value = 0x1`，表示测试通过

- [ ] **Step 2: 检查测试结果**

如果输出显示 `Value = 0x1`:
- 测试通过 ✓

如果输出显示 `Value = 0xFF`:
- 测试失败 ✗，需要检查失败的具体指令

Expected: 测试通过，tohost 输出 = 1

---

### Task 6: 更新文档和提交

**Files:**
- Modify: `CLAUDE.md`

- [ ] **Step 1: 更新 CLAUDE.md 已验证列表**

在 CLAUDE.md 的 "已验证功能" 部分，添加：
```markdown
- [x] 所有 I-Type ALU 指令 (ADDI, SLTI, SLTIU, ANDI, ORI, XORI, SLLI, SRLI, SRAI)
```

- [ ] **Step 2: 提交所有更改**

```bash
git add firmware/itype_alu_test.hex src/soc/TestProgram.bsv CLAUDE.md
git commit -m "feat: 验证 I-Type ALU 指令 (9 条)

验证指令:
- ADDI: 立即数边界 (0, 2047, -2048) + 溢出
- SLTI/SLTIU: 有符号/无符号比较完整场景
- ANDI/ORI/XORI: 负立即数符号扩展测试
- SLLI/SRLI/SRAI: 移位量 0/31 边界测试

测试结果: tohost = 0x1 (通过)"
```

---

## Spec 自查清单

**✓ Spec 覆盖检查:**
- ADDI 边界测试 (零值、最大/最小立即数、溢出) → Task 1, Step 1
- SLTI/SLTIU 完整场景 → Task 1, Step 1
- ANDI/ORI/XORI 负立即数 → Task 1, Step 1
- SLLI/SRLI/SRAI 移位边界 → Task 1, Step 1
- 立即数符号扩展验证 → Task 1, Step 1 (通过负立即数测试覆盖)
- 编译流程 → Task 2-4
- 运行仿真 → Task 5
- 更新文档 → Task 6

**✓ Placeholder 扫描:**
- 无 TBD、TODO 等占位符
- 所有代码块完整
- 所有命令有预期输出

**✓ 类型一致性:**
- 汇编语法正确 (RISC-V RV32I)
- hex 文件路径一致 (`firmware/itype_alu_test.hex`)
- BSV 输出路径一致 (`src/soc/TestProgram.bsv`)