# RISC-V BSV处理器项目

## 项目简介

本项目是基于Bluespec SystemVerilog (BSV)实现的RISC-V处理器，采用模块化设计，支持基本的RISC-V指令集。项目使用BSV进行硬件描述，并提供了完整的测试环境。

## 项目架构

```
riscv-bsv-processor/
├── Makefile                # 构建脚本，集成BSV和RISC-V工具链
├── firmware/               # 存放编译后的固件文件
├── scripts/                # 辅助脚本，如链接脚本
│   └── link.ld            # RISC-V链接脚本
├── src/                    # 源代码目录
│   ├── common/            # 公共类型和定义
│   │   └── Types.bsv      # 基本数据类型和指令格式定义
│   ├── core/              # 处理器核心模块
│   │   ├── ALU.bsv        # 算术逻辑单元
│   │   ├── Core.bsv       # 处理器核心主模块
│   │   └── RegFile.bsv    # 寄存器文件
│   ├── memory/            # 内存子系统（待实现）
│   └── soc/               # 系统级模块
│       └── TestBench.bsv  # 测试平台，用于仿真和验证
└── tests/                 # 测试用例
    ├── assembly/          # 汇编测试程序
    │   └── simple_test.s  # 简单的汇编测试
    ├── c/                 # C语言测试程序（待实现）
    └── verification/      # 验证脚本（待实现）
```

## 模块关系图

```mermaid
graph TD
    A[TestBench] --> B[Core]
    B --> C[ALU]
    B --> D[RegFile]
    B --> E[Types]
    C --> E
    D --> E
    A --> E
```

## 模块说明

### 1. Types模块 (src/common/Types.bsv)
- 定义了基本数据类型，如Word、Addr等
- 定义了RISC-V指令格式结构
- 定义了处理器状态枚举

### 2. Core模块 (src/core/Core.bsv)
- 处理器核心主模块
- 实现基本的指令获取和执行流程
- 包含程序计数器和处理器状态管理

### 3. ALU模块 (src/core/ALU.bsv)
- 算术逻辑单元实现
- 支持基本的算术、逻辑和移位操作

### 4. RegFile模块 (src/core/RegFile.bsv)
- 寄存器文件实现
- 支持RISC-V的32个通用寄存器
- 处理x0寄存器特殊行为（硬连线为0）

### 5. TestBench模块 (src/soc/TestBench.bsv)
- 测试平台，用于仿真和验证
- 实例化处理器核心
- 提供仿真控制和输出

## 构建和仿真

### 编译项目
```bash
make compile
```

### 运行仿真
```bash
make simulate
```

### 清理构建文件
```bash
make clean
```

## 开发计划

1. 完成内存子系统实现
2. 扩展指令集支持
3. 添加更多测试用例
4. 优化处理器性能
