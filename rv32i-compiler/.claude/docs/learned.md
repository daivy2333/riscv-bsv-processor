# 学习记忆

> 最后更新：2026-05-13
> 记录探索发现、API 路径、技巧、踩坑经验

---

## 编译器实现记录

### Micro-C 编译器架构（阶段3）

| 文件 | 职责 | 关键函数 |
|------|------|----------|
| `lexer.c` | 字符→Token流（含控制流关键字） | `tokenize()` 新增 `if/else/while/for` 关键字 + `++`/`<` 标记 |
| `parser.c` | Token→AST（三级优先级 + 控制流） | `parse_term(*/)` / `parse_addsub(+-)` / `parse_expr(<)` / `parse_if/while/for_stmt()` |
| `ast.c/h` | AST节点定义 | 新增 `AST_IF`(left=cond,body=then,right=else) / `AST_WHILE`(left=cond,body=body) / `AST_NOOP`(空语句) |
| `codegen.c` | AST→汇编（标签生成 + 分支 + 多级溢出槽） | `fresh_label()` / `gen_stmt(AST_IF/WHILE)` / `spill_depth` 深度溢出 |
| `asm.c` | 二遍汇编器，全RV32I指令集 | `beqz`/`bnez`/`j` 伪指令 + `slt` R-type |
| `linker.c` | 拼接 crt0+lib+用户→hex | `read_file()` 拼接 + 一次 `asm_assemble()` |

### 阶段3新增架构模式

#### 表达式优先级三级层次
```
parse_expr()       → <          (loops on TOK_LT, calls parse_addsub)
parse_addsub()     → + -        (loops on TOK_PLUS/MINUS, calls parse_term)
parse_term()       → * /        (loops on TOK_STAR/SLASH, calls parse_primary)
parse_primary()    → int-lit, id, (expr)
```

#### 控制流语法糖展开
```
for(init; cond; inc) body  →   { init; while(cond) { body; inc; } }
i++                        →   i = i + 1
```

#### 代码生成—分支模式
```
// if-then-else
gen_expr(cond) → t0
beqz t0, .L_else
gen_stmt(then_body)
j .L_end
.L_else:
gen_stmt(else_body)
.L_end:

// while loop
.L_loop:
gen_expr(cond) → t0
beqz t0, .L_end
gen_stmt(body)
j .L_loop
.L_end:
```

#### 多级溢出槽系统
- 旧：单个 sp+0 临时槽（嵌套表达式溢出冲突）
- 新：4 个槽位 sp+0~sp+12，`spill_depth` 计数器跟踪嵌套级别
- 局部变量起始偏移改为 sp+16（为溢出槽腾空间）

```c
case AST_BIN_OP: {
    gen_expr(n->left);                          // left → t0
    int my_off = spill_depth * 4;
    spill_depth++;
    emit("    sw t0, %d(sp)\n", my_off);        // spill left
    gen_expr(n->right);                         // right → t0
    spill_depth--;
    emit("    mv t1, t0\n");                    // t1 = right
    emit("    lw t0, %d(sp)\n", my_off);        // restore left
    // emit operation (add/sub/mul/div/slt)
}
```



### 汇编器编码函数

```c
// R-type: [funct7][rs2][rs1][funct3][rd][opcode]
uint32_t encode_rtype(int funct7, int rs2, int rs1, int funct3, int rd, int opcode);

// I-type: [imm12][rs1][funct3][rd][opcode]
uint32_t encode_itype(int32_t imm12, int rs1, int funct3, int rd, int opcode);

// S-type: [imm11:5][rs2][rs1][funct3][imm4:0][opcode]
uint32_t encode_stype(int32_t imm12, int rs2, int rs1, int funct3);

// B-type: [imm12|imm10:5][rs2][rs1][funct3][imm4:1|imm11][opcode=0x63]
uint32_t encode_btype(int32_t offset, int rs2, int rs1, int funct3);

// U-type: [imm20][rd][opcode]
uint32_t encode_utype(int32_t imm20, int rd, int opcode);

// J-type: [imm20|imm10:1|imm11|imm19:12][rd][opcode=0x6F]
uint32_t encode_jtype(int32_t offset, int rd);
```

### Stack Frame Layout (阶段3)

```
高地址
  ┌──────────────┐ ← 调用前 sp
  │ ra           │ ← sp + frame_size - 4
  ├──────────────┤
  │ local[N-1]   │ ← sp + 16 + 4*(N-1)
  │ ...          │
  │ local[0]     │ ← sp + 16
  ├──────────────┤
  │ spill[3]     │ ← sp + 12 (多级溢出槽)
  │ spill[2]     │ ← sp + 8
  │ spill[1]     │ ← sp + 4
  │ spill[0]     │ ← sp + 0
  └──────────────┘ ← sp
低地址

frame_size = (16 + 4 * num_locals) 16-byte对齐
4 个溢出槽用于嵌套表达式求值的临时值存储
变量递归扫描：count_vars() 递归进入 AST_IF/AST_WHILE 体
```

### 算术指令

| 指令 | 功能 | 编码格式 |
|------|------|----------|
| `add rd, rs1, rs2` | rd = rs1 + rs2 | R-type |
| `addi rd, rs1, imm` | rd = rs1 + imm | I-type |
| `sub rd, rs1, rs2` | rd = rs1 - rs2 | R-type |
| `sll rd, rs1, rs2` | rd = rs1 << rs2 | R-type |
| `srl rd, rs1, rs2` | rd = rs1 >> rs2 (逻辑) | R-type |
| `sra rd, rs1, rs2` | rd = rs1 >> rs2 (算术) | R-type |
| `slt rd, rs1, rs2` | rd = (rs1 < rs2) ? 1 : 0 | R-type |

### 分支指令

| 指令 | 功能 | 编码格式 |
|------|------|----------|
| `beq rs1, rs2, offset` | if (rs1 == rs2) PC += offset | B-type |
| `bne rs1, rs2, offset` | if (rs1 != rs2) PC += offset | B-type |
| `blt rs1, rs2, offset` | if (rs1 < rs2) PC += offset | B-type |
| `bge rs1, rs2, offset` | if (rs1 >= rs2) PC += offset | B-type |

### 内存指令

| 指令 | 功能 | 编码格式 |
|------|------|----------|
| `lw rd, offset(rs1)` | rd = mem[rs1 + offset] | I-type |
| `sw rs2, offset(rs1)` | mem[rs1 + offset] = rs2 | S-type |
| `lb/lh/lbu/lhu` | 字节/半字加载 | I-type |
| `sb/sh` | 字节/半字存储 | S-type |

### 跳转指令

| 指令 | 功能 | 编码格式 |
|------|------|----------|
| `jal rd, offset` | rd = PC; PC += offset | J-type |
| `jalr rd, rs1, offset` | rd = PC; PC = rs1 + offset | I-type |
| `ret` | jalr x0, ra, 0 (伪指令) | — |

---

## 调用约定速查

| 寄存器 | ABI 名 | 用途 | 保存责任 |
|--------|--------|------|----------|
| x0 | zero | 常量 0 | — |
| x1 | ra | 返回地址 | Caller |
| x2 | sp | 栈指针 | Callee |
| x8 | s0/fp | 帧指针 | Callee |
| x5-7 | t0-2 | 临时 | Caller |
| x10-17 | a0-7 | 参数/返回值 | Caller |
| x18-27 | s2-11 | 保存寄存器 | Callee |
| x28-31 | t3-6 | 临时 | Caller |

---

## CPU TestBench 路径

| 类型 | 路径 | 说明 |
|------|------|------|
| CPU 源码 | `../src/` | BSV 流水线实现 |
| 测试程序 | `../tests/assembly/` | 汇编测试用例 |
| Hex 转换工具 | `../tools/hex_to_bsv.py` | hex → BSV 程序 |
| TestBench | `../src/soc/TestBench.bsv` | CPU 仿真入口 |

---

## 常用命令

| 场景 | 命令 | 输出含义 |
|------|------|----------|
| 编译微CC | `make` | 产出 build/microcc |
| 编译测试 | `make build/test.hex` | 编译 tests/test.c |
| 运行CPU测试 | `make test` | Verilator仿真，验证tohost |
| 清理 | `make clean` | 删除build/ |

---

## 阶段3踩坑记录

| 问题 | 原因 | 解决方案 | 发现时间 |
|------|------|----------|----------|
| 空复合语句 `{ }` 段错误 | parse_stmt 调用 parse_compound 时未消费 `{` 导致无限递归 | parse_stmt 先 `cur=cur->next` 消费 `{`，再调 parse_compound，最后 expect(RBRACE) | 2026-05-13 |
| 嵌套表达式溢出值被覆盖 | 单级 sp+0 临时槽被内外层 BIN_OP 同时使用 | 4 级深度溢出槽 + spill_depth 计数器，每层使用独立偏移 | 2026-05-13 |
| AST_IF/AST_WHILE 体内变量未识别 | count_frame 只扫描顶层语句，不递归进入控制流节点 | count_vars() 递归函数，对 AST_IF/AST_WHILE 进入 .body/.right | 2026-05-13 |
| for 语法糖展开链被覆盖 | parse_compound 只设置 tail=s，不走到链尾，导致下一语句覆盖 .next | parse_compound 增加 `while (tail->next) tail=tail->next` 走完整条链 | 2026-05-13 |
| for 增量 `i++` 后缺少 `;` | parse_stmt 的 ++ 处理期望后续有 `;`，但 for 循环增量后为 `)` | 在 parse_for_stmt 中直接处理 TOK_ID+TOK_INC，不委托给 parse_stmt | 2026-05-13 |
| Verilator 并行测试缓存冲突 | make test-phase2 并行运行多个仿真共享 obj_dir | 单个运行测试，每次 clean obj_dir | 2026-05-13 |

## 阶段3已完成

- [x] 表达式优先级三级层次（`*/` > `+-` > `<`）
- [x] if/else 语句 + AST_IF 节点
- [x] while 循环 + AST_WHILE 节点
- [x] for 循环（语法糖展开为 while + 赋值）
- [x] ++ 后自增（语法糖展开为 `i = i + 1`）
- [x] 空语句 `;` → AST_NOOP
- [x] 复合语句体 `{ ... }` 支持
- [x] 嵌套控制流（if 内含 while，for 内含 if）
- [x] 标签生成系统（单调递增计数器 `.L0`, `.L1`, ...）
- [x] 多级表达式溢出槽系统（4 槽位 + 深度跟踪）
- [x] 6 个 Phase 3 CPU 测试全部通过

## 阶段4完成

- [x] 多参数函数定义 (`int fib(int n)`)
- [x] 函数调用表达式 (`fib(n-1)` 在 return/赋值/表达式中)
- [x] RISC-V ABI 调用约定 (a0-a7 传参, a0 返回值, jal ra)
- [x] 传出参数溢出区（32 字节, 8 槽位, frame-36 偏移）
- [x] 递归调用（独立栈帧, ra 保存/恢复正确）
- [x] 多函数支持（main 调用 fib/add/get42/sum3）
- [x] crt0.s 栈空间扩大 (256 → 4096 字节)
- [x] 4 个 Phase 4 CPU 测试全部通过

### 阶段4新增架构模式

#### 函数调用代码生成
```
// 评估所有参数，存入溢出区
for each arg: gen_expr(arg) → sw t0, arg_base(sp)
// 加载参数到寄存器
for i in 0..N-1: lw ai, arg_base + i*4(sp)
// 调用并获取结果
jal ra, func_name
mv t0, a0
```

#### 函数序言-参数溢出
```
func_name:
    addi sp, sp, -frame
    sw ra, frame-4(sp)
    sw a0, param0_offset(sp)   // 参数 N=0
    sw a1, param1_offset(sp)   // 参数 N=1
    ...
```

#### 栈帧布局 (阶段4)
```
sp + 0..15:       4 溢出槽
sp + 16..:        params → body 局部变量
sp + frame-36:    arg[0..7] 传出参数区 (32字节)
sp + frame-4:     saved ra
```

### 递归调用追踪 — fib(3) 示例
```
main() sp=0x7FF0
  jal fib, ra=main+4
  fib(3) sp=0x7FB0: sw a0→sp+16, ra→sp+60
    jal fib, ra=fib+4
    fib(2) sp=0x7F70: n=3, n<2? no, fib(2)+fib(1)
      fib(1) sp=0x7F30: sw ra, ra→sp+60
        fib(0) sp=0x7EF0: sw a0=0, ra→sp+60
        return 0→sp→fib(0)
      return 1
    return 1+1=2
  return 2+1=3
```

## 待探索（阶段5+）

- [ ] 指针与数组（load/store 地址计算）
- [ ] 全局变量与多文件编译
- [ ] 结构体与高级类型
- [ ] 寄存器分配（线性扫描）
- [ ] 指针与数组（load/store 地址计算）