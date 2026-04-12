# 嵌入式操作系统支持路线图

日期：2026-04-12

## 目标

支持 uClinux/FreeRTOS（无 MMU），可运行简单嵌入式操作系统

## 阶段性开发计划

### 阶段 1：完善基础功能（1-2 周）

| 任务 | 文件 | 状态 |
|------|------|------|
| Load-Use 冒险修复验证 | Core.bsv | ⚠️ 待验证 |
| 添加 LB/LH/LBU/LHU | Decoder.bsv, ALU.bsv | ❌ 未开始 |
| 添加 SB/SH | Decoder.bsv, Core.bsv | ❌ 未开始 |
| 扩展内存到 64KB | Core.bsv, Types.bsv | ❌ 未开始 |
| 运行 RISC-V 官方测试 | TestBench.bsv | ❌ 未开始 |

### 阶段 2：特权级架构（2-4 周）

| 任务 | 新文件 | 状态 |
|------|------|------|
| 定义 PrivMode 类型 | Types.bsv | ❌ 未开始 |
| 添加特权级状态寄存器 | Core.bsv | ❌ 未开始 |
| 特权级切换逻辑 | Core.bsv | ❌ 未开始 |
| 特权指令检查 | Decoder.bsv | ❌ 未开始 |

### 阶段 3：CSR 寄存器组（2-3 周）

**新增文件**：`src/core/CSR.bsv`

关键 CSR 寄存器：
- mstatus (0x300), mie (0x304), mip (0x344)
- mtvec (0x305), mepc (0x341), mcause (0x342), mtval (0x343)
- sstatus (0x100), stvec (0x105), sepc (0x141), scause (0x142)

### 阶段 4：异常陷入机制（1-2 周）

- 异常检测（非法指令、断点、ecall）
- 异常陷入（保存 PC，跳转到 mtvec/stvec）
- 异常返回（mret/sret）
- 中断优先级处理

### 阶段 5：CLINT 定时器（1 周）

**新增文件**：`src/peripheral/CLINT.bsv`

- mtime：64 位实时计数器
- mtimecmp：定时器比较值
- 定时器中断触发

### 阶段 6：PLIC 中断控制器（1-2 周）

**新增文件**：`src/peripheral/PLIC.bsv`

- 中断源注册
- 优先级仲裁
- enable/pending 寄存器

### 阶段 7：UART 控制台（1 周）

**新增文件**：`src/peripheral/UART.bsv`

- TX 发送、RX 接收
- 状态寄存器

### 阶段 8：内存扩展（1-2 周）

**内存布局**：
```
0x00000000 - 0x00000FFF: Boot ROM (4KB)
0x00010000 - 0x0001FFFF: CLINT (64KB)
0x00020000 - 0x0002FFFF: PLIC (64KB)
0x10000000 - 0x10000FFF: UART (4KB)
0x80000000 - 0x80FFFFFF: RAM (16MB)
```

## 关键里程碑

| 里程碑 | 时间 | 目标 |
|--------|------|------|
| M1 | 第2周 | RV32I 全指令支持，通过官方测试 |
| M2 | 第6周 | 特权级架构完成 |
| M3 | 第11周 | 异常处理完成，可响应中断 |
| M4 | 第15周 | 外设完成，有控制台输出 |
| M5 | 第17周 | 首次启动 FreeRTOS/uClinux |

## 总时间估算

**约 3-4 个月**