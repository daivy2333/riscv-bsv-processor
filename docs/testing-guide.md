# 测试指南

## 测试流程

```
汇编测试 (tests/assembly/*.s)
    ↓ make firmware/xxx.hex (-march=rv32i_zicsr)
Hex 文件 (firmware/*.hex)
    ↓ python3 tools/hex_to_bsv.py
BSV 程序 (src/soc/TestProgram.bsv)
    ↓ make test
Verilator 仿真
```

## 添加新测试

```bash
# 1. 编写汇编
vim tests/assembly/new_test.s

# 2. 编译为 hex（禁用压缩指令）
make firmware/new_test.hex

# 3. 生成 BSV
python3 tools/hex_to_bsv.py firmware/new_test.hex > src/soc/TestProgram.bsv

# 4. 运行
make test
```

## 注意事项

| 项目 | 要求 |
|------|------|
| 编译选项 | `-march=rv32i_zicsr`（禁用压缩指令） |
| 地址对齐 | 字: addr[1:0]=0, 半字: addr[0]=0 |
| 内存边界 | DMem 地址 < 2048 |
| 结束标记 | tohost 写入 0x80001000 |

## 汇编模板

```asm
.section .text
.global _start

_start:
    # 测试代码
    li x1, 10
    li x2, 20
    add x3, x1, x2    # x3 = 30

    # 结束标记
    li x31, 0xDEAD
end:
    j end
```

## 测试状态

| 测试 | 状态 | 说明 |
|------|------|------|
| simple_arith_test.s | ✓ PASSED | 基本算术 + li (50 cycles) |
| load_test.s | ✓ PASSED | Load-Use 冒险 (57 cycles) |
| rtype_complete_test.s | ✓ PASSED | R-Type 全指令 |
| itype_alu_test.s | ✓ PASSED | I-Type ALU |
| simple_branch_test.s | ✓ PASSED | 分支预测 |
| simple_loop.s | ✓ PASSED | 循环计数 |
| csr_basic_test.s | ✓ PASSED | CSR 读写 (58 cycles) |
| privilege_m_mode_test.s | ✓ PASSED | M-mode CSR (64 cycles) |
| csr_immediate_test.s | ✓ PASSED | CSR 立即数 (46 cycles) |
| loop_test.s | ✓ PASSED | 循环分支 (71 cycles) |
| pipeline_test.s | ✓ PASSED | 完整流水线 (65 cycles) |
| uart_putchar_test.s | ✓ PASSED | UART TX 输出 (62 cycles) |
| mtime_test.s | ✓ PASSED | mtime 读取 (62 cycles) |
| mtime_increment_verify.s | ✓ PASSED | mtime 递增验证 (62 cycles) |
| mtimecmp_mtip_test.s | ✓ PASSED | MTIP 触发 (62 cycles) |
| trap_mret_test.s | ✓ PASSED | Trap + mret (62 cycles) |

**总计**: 16 个测试，全部通过

## 阶段状态

| 阶段 | 内容 | 状态 |
|------|------|------|
| 阶段 1-2 | 流水线 + RV32I | ✓ 完成 |
| 阶段 3 | CSR + 陷阱处理 | ✓ 完成 |
| 阶段 4 | 分支预测修复 | ✓ 完成 |
| 阶段 5 | SOC + 中断框架 | ✓ 完成 |
| 阶段 6 | FreeRTOS 基础 | ✓ 完成 |

## 调试技巧

### 流水线追踪

```bsv
rule debugCycle;
    $display("CYCLE: PC=%h ID=%h EX=%h",
             pcReg, if_id_reg.payload.instruction, id_ex_reg.payload.instruction);
endrule
```

### 前递追踪

```bsv
if (ex_mem_reg.valid && ex_mem_reg.payload.rd == pkt.rs1) begin
    $display("FWD: MEM→EX rs1=%d val=%h", pkt.rs1, ex_mem_reg.payload.alu_result);
end
```

### Stall 追踪

```bsv
if (stall_load_use) begin
    $display("STALL: count=%d", stall_count);
end
```