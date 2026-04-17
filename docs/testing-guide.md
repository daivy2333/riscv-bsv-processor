# 测试指南

本文档说明如何为 RISC-V BSV 处理器编写和运行测试。

## 测试流程

```
┌─────────────────────────────────┐
│  1. 编写汇编测试                 │
│     tests/assembly/xxx.s        │
└─────────────────────────────────┘
              ↓
┌─────────────────────────────────┐
│  2. 编译为 Hex                   │
│     make firmware/xxx.hex       │
│     (-march=rv32i 禁用压缩)      │
└─────────────────────────────────┘
              ↓
┌─────────────────────────────────┐
│  3. 生成 BSV 测试程序            │
│     python3 tools/hex_to_bsv.py │
└─────────────────────────────────┘
              ↓
┌─────────────────────────────────┐
│  4. 修改 TestBench 结束条件      │
│     src/soc/TestBench.bsv       │
└─────────────────────────────────┘
              ↓
┌─────────────────────────────────┐
│  5. 运行仿真                     │
│     make test                   │
└─────────────────────────────────┘
```

## 汇编测试格式

### 基本模板

```asm
# tests/assembly/my_test.s
.section .text
.global _start

_start:
    # 测试代码
    li x1, 10
    li x2, 20
    add x3, x1, x2    # x3 = 30

    # 结束标记
    li x31, 0xDEAD    # 结束信号
end:
    j end             # 止循环
```

### 注意事项

1. **禁用压缩指令**: 使用 `make firmware/xxx.hex` 时自动添加 `-march=rv32i`
2. **地址对齐**: 字访问 addr[1:0]=0, 半字访问 addr[0]=0
3. **内存边界**: DMem 地址 < 2048 (addr[10:2] < 512)
4. **tohost**: 写入 0x80001000 表示测试完成

## 现有测试说明

### pipeline_test.s

验证内容：
- 数据前递 (EX→EX, MEM→EX, WB→EX)
- Load-Use 冒险
- 分支预测 (BNE 循环)
- 条件分支 (BLT)
- JAL 跳转

预期结果：
| 寄存器 | 预期值 | 说明 |
|--------|--------|------|
| x1 | 10 | li x1, 10 |
| x2 | 20 | li x2, 20 |
| x3 | 30 | add x3, x1, x2 |
| x4 | 40 | add x4, x3, x1 (前递) |
| x5 | 70 | add x5, x4, x3 (前递) |
| x31 | 0xDEAD | 结束标记 |

## Hex 转 BSV

### 工具用法

```bash
python3 tools/hex_to_bsv.py firmware/pipeline_test.hex > src/soc/TestProgram.bsv
```

### 输出格式

```bsv
// Auto-generated test program from hex file
package TestProgram;
import Types::*;
import Vector::*;

function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    prog[0] = 32'h00a00093;  // @ 0x80000000
    prog[1] = 32'h01400113;  // @ 0x80000004
    // ...

    return prog;
endfunction
endpackage
```

## TestBench 配置

### 结束条件

修改 `checkDone` 规则中的 PC 阈值：

```bsv
rule checkDone (programLoaded && !programDone && core.pc >= 32'h80000058);
    programDone <= True;
endrule
```

### 预期结果

修改 `report` 规则中的预期值：

```bsv
rule report (dumpDone);
    $display("Register dump:");
    $display("  x1  = %0d (expected 10)", core.readReg(1));
    $display("  x31 = %0d (expected 0xDEAD)", core.readReg(31));
endrule
```

## 调试技巧

### 添加调试输出

在 Core.bsv 添加 $display：

```bsv
rule executeStage;
    ID_EX_Packet pkt = id2ex.first;
    if (pkt.write_reg) begin
        $display("EX: rd=%d result=%h", pkt.rd, alu_result);
    end
endrule
```

### 检查流水线状态

```bsv
rule debugCycle (programLoaded);
    $display("CYCLE: PC=%h IF=%h ID=%h EX=%h",
             pcReg, if2id.first.instruction, id2ex.first.instruction);
endrule
```

### 追踪 Stall

```bsv
rule decrementStall (stall_load_use && stall_count > 0);
    $display("STALL: count=%d", stall_count);
    // ...
endrule
```

## 测试最佳实践

1. **单一功能测试**: 每个测试验证一个特定功能
2. **明确预期值**: 在注释中标注每个寄存器的预期值
3. **结束标记**: 使用固定寄存器 (如 x31) 作为结束信号
4. **地址规划**: 确保内存访问地址在有效范围内
5. **文档同步**: 测试完成后更新 TestBench 预期值

## riscv-tests 集成 (计划)

官方测试套件使用 tohost 机制：

- 写入 1 = 测试通过
- 写入 >1 = 测试失败 (test_id = value >> 1)

需要在 Core 中检测 `0x80001000` 地址写入，并传递到 TestBench。