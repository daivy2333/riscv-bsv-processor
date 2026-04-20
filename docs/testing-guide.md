# 测试指南

## 测试流程

```
汇编测试 (tests/assembly/*.s)
    ↓ riscv64-unknown-elf-gcc -march=rv32i_zicsr
Hex 文件 (firmware/*.hex)
    ↓ python3 tools/hex_to_bsv.py
BSV 程序 (src/soc/TestProgram.bsv)
    ↓ bsc -verilog ...
Verilator 仿真
    ↓ ./obj_dir/VmkTestBench
测试结果（检查 tohost 写入）
```

## 添加新测试

```bash
# 1. 编写汇编（必须包含 tohost 写入）
vim tests/assembly/new_test.s

# 2. 编译为 hex
riscv64-unknown-elf-gcc -march=rv32i_zicsr -mabi=ilp32 -nostdlib -T scripts/link.ld tests/assembly/new_test.s -o firmware/new_test.elf
riscv64-unknown-elf-objcopy -O verilog firmware/new_test.elf firmware/new_test.hex

# 3. 生成 BSV
python3 tools/hex_to_bsv.py firmware/new_test.hex > src/soc/TestProgram.bsv

# 4. 编译
/opt/bsc/bin/bsc -verilog -p src:src/common:src/core:src/memory:src/soc:src/branch:src/peripheral:%/Libraries -no-warn-action-shadowing -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS

# 5. 运行
rm -rf obj_dir && verilator --cc --exe --build -o VmkTestBench --top-module mkTestBench build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp -Wno-STMTDLY -Wno-WIDTH
./obj_dir/VmkTestBench
```

## 注意事项

| 项目 | 要求 |
|------|------|
| 编译选项 | `-march=rv32i_zicsr`（禁用压缩指令） |
| 地址对齐 | 字: addr[1:0]=0, 半字: addr[0]=0 |
| 内存边界 | DMem 地址 < 2048 words |
| 结束标记 | **必须**写入 tohost (0x80001000) |

## 汇编模板

```asm
.section .text
.global _start

_start:
    # 测试代码
    li x1, 10
    li x2, 20
    add x3, x1, x2    # x3 = 30

    # 结束标记（必须）
    li x6, 0x80001000   # tohost 地址
    li x7, 1            # 成功值
    sw x7, 0(x6)        # 写入 tohost

end:
    j end               # 无限循环
```

## 测试状态

| 测试 | 状态 | 说明 |
|------|------|------|
| loop_test.s | ✓ PASSED | 循环 + 分支预测 |
| simple_arith_test.s | ✓ PASSED | 基本算术 |
| load_test.s | ✓ PASSED | Load-Use 冒险 |
| csr_basic_test.s | ✓ PASSED | CSR 读写 |
| privilege_m_mode_test.s | ✓ PASSED | M-mode CSR |
| csr_immediate_test.s | ✓ PASSED | CSR 立即数指令 |
| rtype_complete_test.s | ✓ PASSED | R-Type 全指令 |
| itype_alu_test.s | ✓ PASSED | I-Type ALU |
| simple_branch_test.s | ✓ PASSED | 分支预测执行 |
| simple_loop.s | ✓ PASSED | 循环计数 |

**总计**: 10 个测试，全部通过 ✓

## 阶段状态

| 阶段 | 内容 | 状态 |
|------|------|------|
| 阶段 1-2 | 流水线 + RV32I | ✓ 完成 |
| 阶段 3 | CSR + 陷阱处理 | ✓ 完成 |
| 阶段 4 | 分支预测修复 | ✓ 完成 |
| 阶段 5 | SOC + 外设框架 | ✓ 完成 |
| 阶段 6 | FreeRTOS 基础运行 | ✓ 完成 |
| 阶段 7 | 控制流协议重构 | ✓ 完成 |
| 阶段 8 | G0021 规则调度解决 | ✓ 完成 |

**最新突破**: G0021 BSV 规则调度问题彻底解决，通过分离 Load/非Load 处理规则和 FIFOF 消息通道架构。

## Trace 调试

处理器内置以下 trace 输出：

| Trace | 说明 |
|-------|------|
| `FETCH_PC: old=X new=Y predicted=N` | IF 阶段 PC 更新 |
| `WB_COMMIT: pc=X rd=N data=Y` | WB 阶段指令提交 |
| `MEM_REQ: pc=X addr=Y` | MEM 阶段内存请求 |
| `STORE_COMMIT: addr=X wdata=Y` | Store 指令提交 |
| `REDIRECT_REQ: pc=X target=Y reason=N` | 控制流重定向请求 |
| `PIPE_FLUSH: stages` | 流水线冲刷 |
| `REDIRECT_CONSUMED: target=X reason=N` | 重定向消费 |

### redirect_reason 编码

| 编码 | 原因 |
|------|------|
| 1 | BRANCH（条件分支） |
| 2 | JAL（无条件跳转） |
| 3 | TRAP（陷阱） |
| 4 | MRET（返回） |
| 5 | INTERRUPT（中断） |

## 常见问题

### 测试超时/失败

**原因**: 缺少 tohost 写入

**解决**: 确保测试程序包含 `sw xN, 0(0x80001000)` 写入

### BSV 编译错误

**原因**: 路径配置问题

**解决**: 使用完整的 `-p src:src/common:...` 路径列表

### Verilator 找不到模块

**原因**: build 目录缺少 .v 文件

**解决**: 先运行 bsc 编译生成 Verilog

### BSV G0021 警告"规则永不能执行"

**原因**: 方法调用成为规则隐式条件，导致规则死锁

**解决**: 
1. 分离依赖不同条件的规则（Load/非Load）
2. 使用 FIFOF 消息通道替代跨模块方法调用
3. 在规则显式条件中检查状态，而非规则内部 if 分支

详见 `docs/debugging-lessons.md` 问题 7