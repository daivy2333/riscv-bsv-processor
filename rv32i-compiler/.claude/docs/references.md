# 外部参考资料

> 收录依赖文档链接、重要概念、常见解决方案

---

## 核心参考资料

| 资料 | 链接 | 关键内容 |
|------|------|----------|
| **RISC-V Spec** | https://riscv.org/technical/specifications/ | RV32I 指令集定义、ABI 规范 |
| **RISC-V Reader** | https://riscv.org/technical/specifications/ | 指令详解、示例代码 |
| **Compiler Design** | 《Engineering a Compiler》 | 编译器架构、寄存器分配 |
| **Self-hosting CC** | https://github.com/rui314/chibicc | 小型 C 编译器参考实现 |

---

## 父项目参考

| 资料 | 路径 | 内容 |
|------|------|------|
| CPU 架构文档 | `../docs/architecture.md` | 流水线设计、分支预测 |
| CPU 测试指南 | `../docs/testing-guide.md` | 测试框架、验证流程 |
| CLAUDE.md | `../CLAUDE.md` | CPU 项目指南 |

---

## 关键概念笔记

### RV32I 指令编码

```
R-type: [funct7][rs2][rs1][funct3][rd][opcode]
I-type: [imm12][rs1][funct3][rd][opcode]
S-type: [imm7][rs2][rs1][funct3][imm5][opcode]
B-type: [imm7][rs2][rs1][funct3][imm5][opcode]
U-type: [imm20][rd][opcode]
J-type: [imm20][rd][opcode]
```

### Opcode 表

| Opcode | 指令类型 |
|--------|----------|
| 0x33 | R-type (ADD, SUB, SLL, etc.) |
| 0x13 | I-type ALU (ADDI, SLTI, etc.) |
| 0x03 | Load (LB, LH, LW, etc.) |
| 0x23 | Store (SB, SH, SW) |
| 0x63 | Branch (BEQ, BNE, etc.) |
| 0x67 | JALR |
| 0x6F | JAL |
| 0x37 | LUI |
| 0x17 | AUIPC |

---

## 实现参考

### 递归下降解析器模式

```c
// 每个产生式对应一个函数
ASTNode* parse_expr() {
    ASTNode* left = parse_term();
    while (current_token == '+' || current_token == '-') {
        Token op = current_token;
        advance();
        ASTNode* right = parse_term();
        left = new_binary_node(op, left, right);
    }
    return left;
}
```

### 代码生成模式

```c
// 表达式求值，结果放入指定寄存器
void gen_expr(ASTNode* node, Reg result_reg) {
    if (node->type == INT_LIT) {
        emit("li %s, %d", reg_name(result_reg), node->val);
    } else if (node->type == BINARY_OP) {
        gen_expr(node->left, t0);
        gen_expr(node->right, t1);
        emit("add %s, t0, t1", reg_name(result_reg));
    }
}
```

---

## 待补充

- BSV 语言参考（用于理解 CPU 实现）
- Verilator 仿真调试技巧
- mini-os 内核架构概述