# 嵌入式操作系统支持路线图

日期：2026-04-18

## 目标

支持 uClinux/FreeRTOS（无 MMU），可运行简单嵌入式操作系统

## 阶段性开发计划

### 阶段 1：完善基础功能（已完成）

| 任务 | 文件 | 状态 |
|------|------|------|
| 五级流水线 | Core.bsv | ✅ 完成 |
| 数据前递 | Core.bsv | ✅ 完成 |
| 分支预测 | Core.bsv, BHT.bsv, BTB.bsv | ✅ 完成 |
| Load-Use 冒险处理 | Core.bsv | ✅ 完成 |
| R-Type 指令验证 | Core.bsv | ✅ 完成 |
| I-Type ALU 验证 | Core.bsv, Decoder.bsv | ✅ 完成 |
| 所有分支指令 | Core.bsv | ✅ 完成 |
| LUI, AUIPC, JAL, JALR | Core.bsv | ✅ 完成 |

### 阶段 2：RV32I 全指令支持（已完成）

| 任务 | 文件 | 状态 |
|------|------|------|
| Load-Use 冒险修复 | Core.bsv | ✅ 完成 |
| WB 前递双缓冲 | Core.bsv | ✅ 完成 |
| 分支冲刷控制 | Core.bsv | ✅ 完成 |
| I-Type ALU 完整验证 | Decoder.bsv | ✅ 完成 |
| RISC-V 汇编测试 | tests/assembly/*.s | ✅ 完成 |

### 阶段 3：特权级架构（已完成）

| 任务 | 文件 | 状态 |
|------|------|------|
| PrivilegeMode 类型 | PrivilegedTypes.bsv | ✅ 完成 |
| CSR 寄存器模块 | CSR.bsv | ✅ 完成 |
| CSR 指令解码 | Decoder.bsv | ✅ 完成 |
| 特权级切换逻辑 | Core.bsv | ✅ 完成 |
| 陷阱处理 (ECALL/EBREAK/MRET) | Core.bsv | ✅ 完成 |
| CSR 测试汇编 | tests/assembly/*.s | ✅ 完成 |

### 阶段 4：CLINT 定时器（待开始）

**新增文件**：`src/peripheral/CLINT.bsv`

- mtime：64 位实时计数器
- mtimecmp：定时器比较值
- 定时器中断触发

### 阶段 5：PLIC 中断控制器（待开始）

**新增文件**：`src/peripheral/PLIC.bsv`

- 中断源注册
- 优先级仲裁
- enable/pending 寄存器

### 阶段 6：UART 控制台（待开始）

**新增文件**：`src/peripheral/UART.bsv`

- TX 发送、RX 接收
- 状态寄存器

### 阶段 7：内存扩展（待开始）

**内存布局**：
```
0x00000000 - 0x00000FFF: Boot ROM (4KB)
0x00010000 - 0x0001FFFF: CLINT (64KB)
0x00020000 - 0x0002FFFF: PLIC (64KB)
0x10000000 - 0x10000FFF: UART (4KB)
0x80000000 - 0x80FFFFFF: RAM (16MB)
```

## 关键里程碑

| 里程碑 | 状态 | 目标 |
|--------|------|------|
| M1 | ✅ 完成 | RV32I 全指令支持，流水线验证通过 |
| M2 | ✅ 完成 | 特权级架构完成 |
| M3 | ⏳ 待开始 | CLINT/PLIC/外设完成 |
| M4 | ⏳ 待开始 | 内存扩展完成 |
| M5 | ⏳ 待开始 | 首次启动 FreeRTOS/uClinux |

## 已实现 CSR 寄存器

| 地址 | 名称 | 说明 |
|------|------|------|
| 0xF11 | mvendorid | 供应商 ID |
| 0xF12 | marchid | 架构 ID |
| 0xF13 | mimpid | 实现 ID |
| 0xF14 | mhartid | 硬件线程 ID |
| 0x300 | mstatus | 机器状态 |
| 0x301 | misa | 机器 ISA |
| 0x304 | mie | 机器中断使能 |
| 0x305 | mtvec | 机器陷阱向量 |
| 0x341 | mepc | 机器异常 PC |
| 0x342 | mcause | 机器异常原因 |
| 0x343 | mtval | 机器陷阱值 |
| 0x344 | mip | 机器中断挂起 |
| 0xB00 | mcycle | 周期计数器 |
| 0xB01 | mtime | 时间计数器 |
| 0xB02 | mtimecmp | 时间比较 |
| 0xB03 | minstret | 指令 retired 计数 |

## 总时间估算

**约 3-4 个月**