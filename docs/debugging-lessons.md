# 项目调试经验：棘手问题记录

本文档记录项目开发过程中遇到的特别难以调试和解决的问题，供后续参考和学习。

---

## 问题 1-7

详见上文（分支预测、前递时机、WB双缓冲、x0前递、规则调度死锁、控制流协议、G0021警告）。

---

## 问题 8：Load 响应污染导致 mtime 读取返回 0

**日期**：2026-04-21

**现象**：mtime 递增验证测试失败，两次读取 mtime 都返回 0，但调试显示 CLINT 的 mtime 值正确递增。

**调试时长**：约 3 小时

### 根因分析

**问题**：SOC 为所有内存请求（包括 Store）生成响应，导致响应 FIFO 中存在上一条 Store 的响应残留。

```
Store 写入 mtimecmp_hi → SOC 响应 (rdata=0, op=MEM_WRITE)
Load 读取 mtime → Core 读到 Store 响应 (错误！)
```

**时序分析**：

```
周期 N:   MEM_REQ (Store mtimecmp_hi, op=2)
周期 N:   handle_mem_req → enq 响应 (rdata=0)
周期 N+1: MEM_REQ (Load mtime, op=1)
周期 N+1: writebackStage_Load → deq 响应 → 读到 Store 响应 (错误)
周期 N+2: handle_mem_req → enq 正确响应 (rdata=21)
```

### 解决方案

**方案**：只为 Load 请求发送响应，Store 不生成响应。

```bsv
rule handle_mem_req (mem_req_fifo.notEmpty);
    MemReq req = mem_req_fifo.first;
    mem_req_fifo.deq;
    
    // 处理请求...
    
    // 只为 Load 发送响应
    if (req.op == MEM_READ)
        mem_resp_fifo.enq(MemResp {valid: True, rdata: rdata});
endrule
```

### 经验教训

1. **FIFO 是消息队列，不是状态**
   - Store 请求不需要响应数据
   - 为 Store 生成响应会污染 FIFO

2. **响应必须与请求匹配**
   - 同周期内规则调度顺序不确定
   - 需确保响应 FIFO 的数据对应正确的请求

---

## 问题 9：CSR mip 读取依赖规则隐式条件导致 MTIP 不触发

**日期**：2026-04-21

**现象**：MTIP 定时器中断测试失败，csrr mip 返回的 MTIP 位始终为 0，即使 mtime >= mtimecmp。

**调试时长**：约 4 小时

### 根因分析

**问题**：CSR 的 update_mip 规则存在隐式条件，当 SOC 的 handle_mem_req 执行时，规则无法同时执行。

```bsv
// CSR.bsv - 原实现
rule update_mip;
    Word new_mip = mip;
    new_mip[7] = timer_irq_wire ? 1 : 0;  // MTIP
    mip <= new_mip;
endrule
```

BSV 编译后，timer_irq_wire 的驱动成为隐式条件：

```verilog
// 生成的 Verilog
assign result = { 
    mip[31:12],
    !WILL_FIRE_RL_soc_handle_mem_req && timer_irq_wire,  // 隐式条件！
    ...
};
```

当 handle_mem_req 执行时，MTIP 变成 0。

### 解决方案

**方案 1**：移除 update_mip 规则，直接在 readCSR 中组合逻辑读取 Wire。

```bsv
// CSR.bsv - 新实现
method Word readCSR(Bit#(12) addr);
    case (addr)
        12'h344: begin  // mip
            value = mip;
            value[11] = external_irq_wire ? 1 : 0;  // 直接读取 Wire
            value[7] = timer_irq_wire ? 1 : 0;
            value[3] = software_irq_wire ? 1 : 0;
        end
    endcase
endmethod
```

**方案 2**：Core 添加 drive_interrupts 规则，每周期驱动 Wire。

```bsv
// Core.bsv
rule drive_interrupts;
    mem_if.timerIRQWire(mem_if.clintTimerIRQ());
    mem_if.softwareIRQWire(mem_if.clintSoftwareIRQ());
    mem_if.externalIRQWire(mem_if.plicExternalIRQ());
endrule
```

### 架构变更

```
旧架构（隐式条件问题）：
  SOC drive_interrupts 规则 → CSR timerIRQWire 方法
  ↑ CSR 方法调用成为 SOC 规则的隐式条件
  ↑ 与 handle_mem_req 规则冲突

新架构（Wire 直连）：
  Core drive_interrupts 规则 → CSR timerIRQWire 方法
  ↑ Core 独立驱动，不影响 SOC 规则
  CSR readCSR 直接读取 Wire（组合逻辑）
  ↑ 无规则依赖，实时读取当前值
```

### 经验教训

1. **CSR mip 应从 Wire 直接读取**
   - MTIP/MSIP/MEIP 是实时状态，不应存储在寄存器中
   - 使用组合逻辑读取 Wire，避免规则隐式条件

2. **中断信号驱动应由 Core 负责**
   - SOC 规则（handle_mem_req）不能被中断信号驱动阻塞
   - Core 规则与 SOC 规则分离，无隐式条件冲突

3. **Wire vs Reg 的使用场景**
   - Wire：实时状态传递，组合逻辑读取
   - Reg：状态存储，规则结束时更新

---

## 问题 10：mtimecmp 64 位值设置不完整

**日期**：2026-04-21

**现象**：MTIP 测试设置 mtimecmp_lo=50，但 MTIP 不触发。

### 根因分析

CLINT 的 mtimecmp 初始化为 64 位最大值（0xFFFFFFFFFFFFFFFF）。测试只设置低 32 位为 50，高位仍为最大值。

```
mtimecmp = {0xFFFFFFFF, 50} = 巨大值
mtime = 60 (递增中)
mtime < mtimecmp → MTIP = 0
```

### 解决方案

测试程序必须同时设置 mtimecmp_hi 和 mtimecmp_lo：

```asm
# 设置 mtimecmp = 50
li x5, 0x02004004        # mtimecmp_hi 地址
li x6, 0
sw x6, 0(x5)             # mtimecmp_hi = 0

li x7, 0x02004000        # mtimecmp_lo 地址
li x8, 50
sw x8, 0(x7)             # mtimecmp_lo = 50
```

### 经验教训

1. **64 位 CSR 必须完整设置**
   - 分两次写入时，高位和低位都要正确设置
   - 初始化值可能是最大值，需要显式清零

---

## 总结：调试方法论

### 1. 周期级 trace 是最强大的工具

```bsv
$display("CLINT_READ: addr=%h rdata=%h", addr, rdata);
$display("SOC_RESP: rdata=%h op=%h", rdata, pack(op));
$display("MEM_RESP: data=%h valid=1", data);
```

### 2. 架构审查优于补丁式修复

- 先判断是"实现 bug"还是"协议/架构 bug"
- 优先从职责边界不清角度分析
- 给出最小正确架构，再讨论优化

### 3. BSV 规则调度的关键原则

| 问题 | 解决方案 |
|------|----------|
| 方法调用隐式条件 | 使用 FIFOF 消息通道 |
| Wire 同周期读写冲突 | 使用 Reg 或组合逻辑直读 |
| 规则死锁 | 分离依赖不同的规则 |
| FIFO 污染 | 只为需要响应的请求生成响应 |

### 4. 定时器中断架构要点

- **mtime**: 自动递增（每周期 +1）
- **MTIP**: 组合逻辑（mtime >= mtimecmp）
- **mip**: 直接读取 Wire（不依赖规则）
- **中断驱动**: Core 独立规则，不影响 SOC

---

*更新日期: 2026-04-21*

*最后问题: 定时器中断机制完整实现，12 个测试全部通过*