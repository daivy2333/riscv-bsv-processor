# 调试经验

## Load 响应污染 FIFO

**问题**：SOC 为 Store 也生成响应，污染响应 FIFO。

**解决**：只为 Load 请求发送响应。

**教训**：FIFO 是消息队列，不是状态。

## CSR mip 读取依赖规则隐式条件

**问题**：CSR update_mip 规则与 SOC handle_mem_req 冲突。

**解决**：移除规则，在 readCSR 中组合逻辑读取 Wire。

**教训**：中断信号应从 Wire 直接读取（实时状态），不依赖规则更新。

## trap_entry 寄存器别名冲突

**问题**：使用 t0/t1/t2 作为临时寄存器，但 x5/x6/x7 正是它们。

**解决**：使用 x28-x31 (t3-t6) 作为临时寄存器。

**教训**：x5=t0, x6=t1, x7=t2，上下文保存必须原子性。

## SOC RAM 字节/半字读取

**问题**：SOC 直接返回完整 word，没有提取字节/半字。

**解决**：移到 Core WB 阶段处理。

**教训**：GCC 会使用 lbu/lb/lh/lhu/sb/sh。

## 方法论

### BSV 规则调度

| 问题 | 解决 |
|------|------|
| 方法调用隐式条件 | FIFOF 消息通道 |
| Wire 同周期读写冲突 | Reg 或组合逻辑直读 |
| FIFO 污染 | 只为需要响应的请求生成响应 |

### 定时器中断架构

- mtime: 自动递增
- MTIP: 组合逻辑 (mtime >= mtimecmp)
- mip: 直接读取 Wire
- 中断驱动: Core 独立规则