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

# 编译汇编文件
make asm-loop_test
make asm-all

# 查看帮助
make help
```

## 测试流程

```
汇编测试 (tests/assembly/*.s)
    ↓ make asm-<name>
Hex 文件 (firmware/*.hex)
    ↓ make test-<name>
Verilator 仿真
    ↓ 
测试结果（检查 tohost 写入）
```

## 添加新测试

```bash
# 1. 编写汇编（必须包含 tohost 写入）
vim tests/assembly/new_test.s

# 2. 编译并运行
make asm-new_test
make test-new_test
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

### 基线测试（10个）

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

### 定时器中断测试（2个）

| 测试 | 状态 | 说明 |
|------|------|------|
| mtime_increment_verify.s | ✓ PASSED | mtime 每周期递增验证 |
| mtimecmp_mtip_test.s | ✓ PASSED | MTIP 定时器中断触发 |

**总计**: 12 个测试，全部通过 ✓

## 阶段状态

| 阶段 | 内容 | 状态 |
|------|------|------|
| 阶段 1-2 | 流水线 + RV32I | ✓ 完成 |
| 阶段 3 | CSR + 陷阱处理 | ✓ 完成 |
| 阶段 4 | 分支预测修复 | ✓ 完成 |
| 阶段 5 | SOC + 外设框架 | ✓ 完成 |
| 阶段 6 | FreeRTOS 基础运行 | ✓ 完成 |
| 阶段 7 | 控制流协议重构 | ✓ 完成 |
| 阶段 8 | **定时器中断支持** | ✓ 完成 |

**最新突破**: 定时器中断机制完整实现，mtime 递增 + MTIP 触发测试通过。

## Trace 调试

处理器内置以下 trace 输出：

| Trace | 说明 |
|-------|------|
| `FETCH_PC: old=X new=Y predicted=N` | IF 阶段 PC 更新 |
| `WB_COMMIT: pc=X rd=N data=Y` | WB 阶段指令提交 |
| `MEM_REQ: pc=X addr=Y` | MEM 阶段内存请求 |
| `MEM_RESP: data=Y valid=1` | Load 响应数据 |
| `STORE_COMMIT: addr=X wdata=Y` | Store 指令提交 |
| `REDIRECT_REQ: pc=X target=Y reason=N` | 控制流重定向请求 |
| `PIPE_FLUSH: stages` | 流水线冲刷 |

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

### Load 响应为 0

**原因**: Store 响应污染 Load 响应 FIFO

**解决**: SOC 只为 Load 请求发送响应，使用 mkBypassFIFOF

### MTIP 不触发

**原因**: CSR mip 依赖规则更新，存在隐式条件

**解决**: CSR mip 直接从 Wire 读取（组合逻辑）

### BSV G0021 警告"规则永不能执行"

**原因**: 方法调用成为规则隐式条件，导致规则死锁

**解决**: 
1. 分离依赖不同条件的规则（Load/非Load）
2. 使用 FIFOF 消息通道替代跨模块方法调用
3. 使用 mkBypassFIFOF 支持同周期读写

详见 `docs/debugging-lessons.md`