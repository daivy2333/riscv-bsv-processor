# 内存布局

## 地址空间

| 区域 | 范围 | 大小 |
|------|------|------|
| Boot ROM | 0x00000000 - 0x00000FFF | 4KB |
| CLINT | 0x02000000 - 0x0200FFFF | 64KB |
| PLIC | 0x0C000000 - 0x0C0FFFFF | 64KB |
| UART | 0x10000000 - 0x10000FFF | 4KB |
| RAM | 0x80000000 - 0x80FFFFFF | 16MB |

## 当前实现

| 内存 | 基地址 | 大小 | 索引 |
|------|--------|------|------|
| IMem | 0x80000000 | 4KB (1024×4) | PC[11:2] |
| DMem | - | 2KB (512×4) | addr[10:2] |
| tohost | 0x80001000 | 1 word | - |

**限制**：
- IMem: PC < 0x80001000
- DMem: 地址 < 2048

## 寄存器 ABI

| 寄存器 | ABI 名称 | 用途 |
|--------|----------|------|
| x0 | zero | 常数 0（硬连线） |
| x1 | ra | 返回地址 |
| x2 | sp | 栈指针 |
| x5-x7 | t0-t2 | 临时 |
| x10-x17 | a0-a7 | 参数/返回值 |
| x28-x31 | t3-t6 | 临时 |

**x0 硬连线为 0，不参与前递/冒险检测。**

## 模块依赖

```
Types.bsv → ALU, RegFile, Decoder, CSR, Core
PrivilegedTypes.bsv → CSR, Core
Core → TestBench
```

## 目录结构

```
src/
├── common/Types.bsv          # 类型定义
├── core/
│   ├── Core.bsv              # 流水线核心
│   ├── ALU.bsv               # ALU
│   ├── RegFile.bsv           # 寄存器堆
│   ├── Decoder.bsv           # 解码器
│   ├── CSR.bsv               # CSR
│   └── PrivilegedTypes.bsv   # 特权类型
├── branch/
│   ├── BHT.bsv               # 分支历史表
│   └── BTB.bsv               # 分支目标缓冲
└── soc/TestBench.bsv         # 测试平台
```