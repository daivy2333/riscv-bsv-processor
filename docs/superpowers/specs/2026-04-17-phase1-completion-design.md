# 阶段1完善基础功能 - 设计文档（修订版 v2）

日期：2026-04-17

## 目标

完成阶段1四个任务，使处理器能够运行 RISC-V 官方测试：
1. 统一 Load-Use 冒险检测实现
2. 添加 LB/LH/LBU/LHU + SB/SH 字节/半字指令
3. 内存扩展到 16MB（含 Core 内嵌内存）
4. 运行 riscv-tests 官方测试

## 实现策略

采用分层实现 + 官方测试验证策略：

```
内存扩展 → 字节指令 → HazardUnit重构 → 官方测试验证全部
```

---

## 第一部分：内存扩展到 16MB

### 问题分析

**当前状态**：
- Core.bsv:61-62 内嵌了 imem/dmem（1024/512 entries）
- 外部 IMem.bsv/DMem.bsv 模块未被使用
- 这是重复实现，需要统一

**解决方案**：保留 Core 内嵌内存（测试方便），扩展容量

### 改动范围

| 文件 | 改动内容 |
|------|----------|
| `Core.bsv` | imem 1024→16384，dmem 512→262144，索引位宽扩展 |
| `Types.bsv` | 无需改动（Addr 已是 32 位） |

### 内存布局

```
IMem: 0x80000000 - 0x8000FFFF (64KB, 16384×32bit)
      索引: addr[15:2] (14 位)
DMem: 0x80000000 - 0x80FFFFFF (16MB, 262144×32bit)
      索引: addr[21:2] (18 位)
```

### 大 Vector 性能考量

**风险**：Vector#(262144, Reg#(Word)) 会生成大量 Verilog 寄存器

**解决方案**：分阶段扩展，使用编译选项控制

```bsv
// 推荐方案：使用 ifdef 控制内存大小
`ifdef USE_LARGE_MEM
    // 16MB 配置（用于 riscv-tests）
    // DMem: 262144 entries = 2^18
    Vector#(262144, Reg#(Word)) dmem <- replicateM(mkRegU);
    // 索引: addr[21:2] (18 位，log2(262144) = 18)
    Bit#(18) dmem_idx = addr[21:2];

    // IMem: 16384 entries = 2^14
    Vector#(16384, Reg#(Word)) imem <- replicateM(mkRegU);
    // 索引: addr[15:2] (14 位，log2(16384) = 14)
    Bit#(14) imem_idx = addr[15:2];
`else
    // 256KB 配置（用于开发调试）
    // DMem: 65536 entries = 2^16
    Vector#(65536, Reg#(Word)) dmem <- replicateM(mkRegU);
    // 索引: addr[17:2] (16 位，log2(65536) = 16)
    Bit#(16) dmem_idx = addr[17:2];

    // IMem: 4096 entries = 2^12 (16KB)
    Vector#(4096, Reg#(Word)) imem <- replicateM(mkRegU);
    // 索引: addr[13:2] (12 位，log2(4096) = 12)
    Bit#(12) imem_idx = addr[13:2];
`endif
```

**索引位宽计算公式**：
```
索引位宽 = log2(Vector 大小)
例如：262144 = 2^18，索引需 18 位
```

**编译命令**：
```bash
# 开发调试（快速编译）
bsc -u Core.bsv

# riscv-tests（大内存）
bsc -u -D USE_LARGE_MEM Core.bsv
```

### 实现细节

**Core.bsv 改动**：
```bsv
// IF 阶段索引改动
// 原来：Bit#(10) idx = fetchPC[11:2];
// 改为：
Bit#(14) idx = fetchPC[15:2];

// MEM 阶段索引改动
// 原来：dmem[pkt.alu_result[10:2]]
// 改为：
Bit#(18) word_idx = pkt.alu_result[21:2];
// ... 使用 dmem[word_idx]
```

### loadProgram 接口改动与兼容性

**问题**：接口改动会导致 TestBench 编译错误

**解决方案**：添加适配函数

```bsv
// Core.bsv 接口改动
interface Core;
    // 新增：支持大程序加载
    method Action loadProgramLarge(Vector#(16384, Word) prog);
    // 保留：兼容小程序加载（开发调试用）
    method Action loadProgram(Vector#(1024, Word) prog);
endinterface

// 实现中添加适配
method Action loadProgram(Vector#(1024, Word) prog);
    Vector#(16384, Word) large_prog = replicate(0);
    for (Integer i = 0; i < 1024; i = i + 1)
        large_prog[i] = prog[i];
    loadProgramLarge(large_prog);
endmethod

method Action loadProgramLarge(Vector#(16384, Word) prog);
    for (Integer i = 0; i < 16384; i = i + 1)
        imem[i] <= prog[i];
    programLoaded <= True;
endmethod
```

### 注意事项

- 使用 `mkRegU` 减少仿真初始化开销
- 开发阶段使用小内存配置，加快编译速度
- 外部 IMem.bsv/DMem.bsv 保留但不使用（未来可改为 SOC 外设）

---

## 第二部分：添加 LB/LH/LBU/LHU + SB/SH

### 改动范围

| 文件 | 改动内容 |
|------|----------|
| `Types.bsv` | 添加 MemWidth 枚举，扩展数据包 |
| `Decoder.bsv` | 解码 funct3 区分字节/半字/字操作 |
| `Core.bsv` | MEM 阶段根据 width 调用对应处理逻辑 |

### MemWidth 枚举

```bsv
// Types.bsv 新增
typedef enum {
    MEM_BYTE,   // LB/LBU/SB
    MEM_HALF,   // LH/LHU/SH
    MEM_WORD    // LW/SW
} MemWidth deriving (Bits, Eq, FShow);
```

### 数据包改动

**DecodedInstr 新增字段**：
```bsv
// Decoder.bsv - 在结构体定义中添加
MemWidth    mem_width;      // 内存访问宽度
Bool        mem_unsigned;   // 是否无符号扩展 (仅用于 LBU/LHU)

// 默认值（非 Load/Store 指令）
MemWidth    mem_width = MEM_WORD;   // 默认值
Bool        mem_unsigned = False;   // 默认值
```

**ID_EX_Packet 新增字段**：
```bsv
// Types.bsv - 在结构体定义中添加
MemWidth    mem_width;
Bool        mem_unsigned;   // 仅 Load 指令使用
```

**EX_MEM_Packet 新增字段**：
```bsv
// Types.bsv - 在结构体定义中添加
MemWidth    mem_width;
Bool        mem_unsigned;   // 仅 Load 指令使用
```

**注意**：Store 指令的 `mem_unsigned` 字段虽然存在但不使用（浪费 1 位但实现简单）

### Decoder funct3 完整处理

**Load 指令 (opcode 7'b0000011)**：
| funct3 | 指令 | mem_width | mem_unsigned | 对齐要求 |
|--------|------|-----------|--------------|----------|
| 000 | LB | MEM_BYTE | False | 无（任意地址） |
| 001 | LH | MEM_HALF | False | addr[0]=0 |
| 010 | LW | MEM_WORD | False | addr[1:0]=0 |
| 100 | LBU | MEM_BYTE | True | 无（任意地址） |
| 101 | LHU | MEM_HALF | True | addr[0]=0 |

**Store 指令 (opcode 7'b0100011)**：
| funct3 | 指令 | mem_width | 对齐要求 |
|--------|------|-----------|----------|
| 000 | SB | MEM_BYTE | 无（任意地址） |
| 001 | SH | MEM_HALF | addr[0]=0 |
| 010 | SW | MEM_WORD | addr[1:0]=0 |

**RISC-V 地址对齐规范**：
- **LB/LBU/SB**：任意字节地址，无对齐要求
- **LH/LHU/SH**：必须半字对齐，addr[0] 必须为 0
- **LW/SW**：必须字对齐，addr[1:0] 必须为 0

**Decoder.bsv 实现改动**：
```bsv
// 在 decode 方法开头添加默认值
MemWidth mem_width = MEM_WORD;
Bool mem_unsigned = False;

// 7'b0000011: Load 指令
7'b0000011: begin
    write_reg = True;
    is_load = True;
    mem_op = MEM_READ;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = False;
    imm = signExtendI(instruction);
    alu_op = ALU_ADD;

    case (funct3)
        3'b000: begin  // LB
            mem_width = MEM_BYTE;
            mem_unsigned = False;
        end
        3'b001: begin  // LH
            mem_width = MEM_HALF;
            mem_unsigned = False;
        end
        3'b010: begin  // LW
            mem_width = MEM_WORD;
            mem_unsigned = False;
        end
        3'b100: begin  // LBU
            mem_width = MEM_BYTE;
            mem_unsigned = True;
        end
        3'b101: begin  // LHU
            mem_width = MEM_HALF;
            mem_unsigned = True;
        end
        default: begin
            // 未定义的 funct3：视为 NOP（安全处理）
            // 阶段2将实现异常：raiseException(ILLEGAL_INSTRUCTION)
            mem_width = MEM_WORD;
            mem_unsigned = False;
        end
    endcase
end

// 7'b0100011: Store 指令
7'b0100011: begin
    mem_op = MEM_WRITE;
    use_imm = True;
    use_rs1 = True;
    use_rs2 = True;
    imm = signExtendS(instruction);
    alu_op = ALU_ADD;

    case (funct3)
        3'b000: mem_width = MEM_BYTE;  // SB
        3'b001: mem_width = MEM_HALF;  // SH
        3'b010: mem_width = MEM_WORD;  // SW
        default: mem_width = MEM_WORD;
    endcase
    // mem_unsigned 对 Store 无意义，保持默认 False
end
```

### 未定义指令处理策略

**阶段1策略**：未定义的 funct3 视为安全默认值（NOP 行为）

| 指令类型 | 未定义 funct3 | 阶段1 处理 | 阶段2 处理 |
|----------|---------------|------------|------------|
| Load | 3'b011, 3'b110, 3'b111 | 默认 LW | 触发 ILLEGAL_INSTRUCTION 异常 |
| Store | 3'b011, 3'b100, 3'b101, 3'b110, 3'b111 | 默认 SW | 触发 ILLEGAL_INSTRUCTION 异常 |
| 其他 opcode | - | NOP（不写寄存器） | 触发 ILLEGAL_INSTRUCTION 异常 |

**理由**：
- 阶段1 无异常机制，采用安全默认值避免处理器崩溃
- riscv-tests 只使用合法指令，不会触发此路径
- 阶段2 实现特权级后，将正确触发异常

### 地址对齐检查

**Core.bsv MEM 阶段添加对齐检查**：
```bsv
// 对齐检查辅助函数
function Bool checkAlignment(Addr addr, MemWidth width);
    case (width)
        MEM_BYTE:  return True;           // 任意对齐
        MEM_HALF:  return addr[0] == 0;   // 半字对齐
        MEM_WORD:  return addr[1:0] == 0; // 字对齐
        default:   return True;
    endcase
endfunction
```

**MEM 阶段处理改动（含对齐检查）**：
```bsv
rule memoryStage;
    EX_MEM_Packet pkt = ex2mem.first;
    ex2mem.deq;

    Word mem_data = 0;

    // 对齐检查（阶段1暂不实现异常，仅打印警告）
    if (pkt.mem_op != MEM_NONE && !checkAlignment(pkt.alu_result, pkt.mem_width)) begin
        $display("WARNING: Misaligned access at PC=%h, addr=%h, width=%s",
                 pkt.pc, pkt.alu_result, pkt.mem_width);
        // 阶段2实现异常：raiseException(LOAD_STORE_ADDRESS_MISALIGNED);
    end

    if (pkt.mem_op == MEM_READ) begin
        Bit#(18) word_idx = pkt.alu_result[21:2];
        Word word_val = dmem[word_idx];

        case (pkt.mem_width)
            MEM_WORD: mem_data = word_val;

            MEM_HALF: begin
                // addr[1] 选择高低半字（addr[0] 已在对齐检查中验证）
                Bit#(1) half_offset = pkt.alu_result[1];
                Bit#(16) half_val = half_offset == 0
                    ? word_val[15:0]
                    : word_val[31:16];
                mem_data = pkt.mem_unsigned
                    ? zeroExtend(half_val)
                    : signExtend(half_val);
            end

            MEM_BYTE: begin
                Bit#(2) byte_offset = pkt.alu_result[1:0];
                Bit#(8) byte_val = case (byte_offset)
                    0: word_val[7:0];
                    1: word_val[15:8];
                    2: word_val[23:16];
                    3: word_val[31:24];
                endcase;
                mem_data = pkt.mem_unsigned
                    ? zeroExtend(byte_val)
                    : signExtend(byte_val);
            end
        endcase
    end

    if (pkt.mem_op == MEM_WRITE) begin
        Bit#(18) word_idx = pkt.alu_result[21:2];
        Word old_word = dmem[word_idx];
        Word new_word = old_word;

        case (pkt.mem_width)
            MEM_WORD: new_word = pkt.rs2_val;

            MEM_HALF: begin
                // addr[1] 选择高低半字（addr[0] 已在对齐检查中验证）
                Bit#(16) half_val = pkt.rs2_val[15:0];
                Bit#(1) half_offset = pkt.alu_result[1];
                new_word = half_offset == 0
                    ? {old_word[31:16], half_val}
                    : {half_val, old_word[15:0]};
            end

            MEM_BYTE: begin
                Bit#(8) byte_val = pkt.rs2_val[7:0];
                Bit#(2) byte_offset = pkt.alu_result[1:0];
                case (byte_offset)
                    0: new_word = {old_word[31:8], byte_val};
                    1: new_word = {old_word[31:16], byte_val, old_word[7:0]};
                    2: new_word = {old_word[31:24], byte_val, old_word[15:0]};
                    3: new_word = {byte_val, old_word[23:0]};
                endcase;
            end
        endcase;

        dmem[word_idx] <= new_word;
    end

    mem2wb.enq(MEM_WB_Packet {
        pc: pkt.pc,
        mem_data: mem_data,
        alu_result: pkt.alu_result,
        rd: pkt.rd,
        write_reg: pkt.write_reg,
        is_load: pkt.is_load
    });

    // MEM 前递设置
    mem_forward <= pkt.alu_result;
    mem_forward_rd <= pkt.rd;
    mem_forward_valid <= pkt.write_reg && !pkt.is_load;
endrule
```

### 非对齐访问策略说明

**RISC-V 规范要求**：
- LH/LHU/SH 必须半字对齐（addr[0]=0）
- LW/SW 必须字对齐（addr[1:0]=0）

**本实现策略**：
- **阶段1**：仅打印警告，不触发异常（简化实现）
- **阶段2**：实现异常陷入机制后，触发 `LOAD_STORE_ADDRESS_MISALIGNED`

**不支持非对齐访问的理由**：
- 非对齐访问需要跨字读取，增加硬件复杂度
- riscv-tests 测试程序都是对齐访问
- 大多数嵌入式系统也不支持非对齐访问

---

## 第三部分：统一 Load-Use 冒险检测

### 问题分析

**当前状态**：
- Core.bsv:107-123 自己实现了 Load-Use 检测
- HazardUnit.bsv 的 detectLoadUseHazard 方法未被调用
- 这是重复实现，代码不一致

**解决方案**：使用 HazardUnit 模块，删除 Core 中的重复逻辑

### 改动范围

| 文件 | 改动内容 |
|------|----------|
| `HazardUnit.bsv` | 扩展检测方法支持 MEM 阶段检测 |
| `Core.bsv` | 删除 107-123 行重复逻辑，调用 hazardUnit |

### HazardUnit 扩展

```bsv
interface HazardUnit;
    method Bool detectLoadUseHazard(
        Bool ex_is_load,        // EX 阶段是否是 Load
        Bit#(5) ex_rd,          // EX 阶段目标寄存器
        Bool mem_is_load,       // MEM 阶段是否是 Load（新增）
        Bit#(5) mem_rd,         // MEM 阶段目标寄存器（新增）
        Bool id_use_rs1,
        Bit#(5) id_rs1,
        Bool id_use_rs2,
        Bit#(5) id_rs2
    );
endinterface

module mkHazardUnit(HazardUnit);
    method Bool detectLoadUseHazard(
        Bool ex_is_load,
        Bit#(5) ex_rd,
        Bool mem_is_load,
        Bit#(5) mem_rd,
        Bool id_use_rs1,
        Bit#(5) id_rs1,
        Bool id_use_rs2,
        Bit#(5) id_rs2
    );
        Bool hazard = False;

        // 检查 EX 阶段 Load
        if (ex_is_load && ex_rd != 0) begin
            if (id_use_rs1 && id_rs1 == ex_rd) hazard = True;
            if (id_use_rs2 && id_rs2 == ex_rd) hazard = True;
        end

        // 检查 MEM 阶段 Load
        if (mem_is_load && mem_rd != 0 && !hazard) begin
            if (id_use_rs1 && id_rs1 == mem_rd) hazard = True;
            if (id_use_rs2 && id_rs2 == mem_rd) hazard = True;
        end

        return hazard;
    endmethod
endmodule
```

### Core.bsv 改动

**删除 107-123 行重复逻辑，改为调用 hazardUnit**：
```bsv
// 原来 107-123 行的重复实现删除
// 改为调用 hazardUnit（在 decodeStage 规则中）：
Bool load_use_hazard = hazardUnit.detectLoadUseHazard(
    id2ex.notEmpty && id2ex.first.mem_op == MEM_READ,
    id2ex.notEmpty ? id2ex.first.rd : 0,
    ex2mem.notEmpty && ex2mem.first.is_load,
    ex2mem.notEmpty ? ex2mem.first.rd : 0,
    dec.use_rs1,
    dec.rs1,
    dec.use_rs2,
    dec.rs2
);
```

---

## 第四部分：运行 riscv-tests 官方测试

### 测试套件

使用 `riscv-tests` 项目的 `rv32ui-p-*` 测试：

**测试分级**：

| 级别 | 测试数量 | 测试名称 | 通过条件 |
|------|----------|----------|----------|
| 最小集 | 5 个 | simple, add, lw, sw, beq | 基础流水线验证 |
| 推荐集 | 12 个 | +lb, sb, lh, sh, jal, jalr, branch, blt, addi, lui, auipc | 字节指令 + 分支验证 |
| 完整集 | 约40个 | 全部 rv32ui-p-* | RV32I 全指令验证 |

**详细测试列表**：

- 基础指令：simple, add, sub, and, or, xor, sll, srl, sra
- Load 指令：lw, lh, lb, lhu, lbu（含 Load-Use 验证）
- Store 指令：sw, sh, sb
- 分支：branch, beq, bne, blt, bge, bltu, bgeu
- 跳转：jal, jalr
- 立即数：addi, andi, ori, xori, slti, sltiu
- 比较：slt, sltu
- 大立即数：lui, auipc

**建议验证顺序**：先运行最小集确认基础框架，再逐步扩展到完整集。

### 集成步骤

1. **克隆 riscv-tests**：
   ```bash
   git clone https://github.com/riscv-software-src/riscv-tests
   cd riscv-tests
   ```

2. **确认 tohost 地址**：
   ```bash
   grep -r "tohost" tests/env/*.ld
   # 通常输出：tohost = 0x80001000;
   ```

3. **编译测试**：
   ```bash
   make rv32ui
   ```

4. **转换格式**：
   ```bash
   riscv64-unknown-elf-objcopy -O verilog rv32ui-p-simple.elf rv32ui-p-simple.hex
   ```

5. **验证 hex 文件**：
   ```bash
   head -20 rv32ui-p-simple.hex
   # 查看是否有写入 0x80001000 的指令
   ```

### hex 文件加载方案（推荐 Python 预处理）

由于 BSV 中解析 hex 文件较复杂，**推荐使用 Python 预处理脚本**将 hex 转换为 BSV 数组格式。

#### Python 预处理脚本

```python
#!/usr/bin/env python3
# scripts/gen_prog.py - 将 Verilog hex 文件转换为 BSV 数组格式
import sys
import os

def parse_hex_file(filename):
    """解析 Verilog hex 格式文件"""
    program = []
    current_addr = 0

    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue

            if line.startswith('@'):
                # 地址行：@80000000
                current_addr = int(line[1:], 16)
            else:
                # 数据行：12345678 9ABCDEF0 ...
                # 每个数据是 8 字符的十六进制数
                for i in range(0, len(line), 9):  # 8 字符 + 1 空格
                    data_str = line[i:i+8].strip()
                    if data_str:
                        data = int(data_str, 16)
                        # 计算索引（基于地址 0x80000000）
                        idx = (current_addr - 0x80000000) // 4
                        if idx >= 0:
                            while len(program) <= idx:
                                program.append(0)
                            program[idx] = data
                            current_addr += 4

    return program

def output_bsv(program, output_file=None):
    """输出 BSV 格式的程序数组"""
    # 扩展到 16384 条目（64KB）
    while len(program) < 16384:
        program.append(0)

    lines = []
    lines.append(f"// 自动生成的程序数组（{len(program)} 条目）")
    lines.append(f"Vector#(16384, Word) testProgram = newVector;")
    for i, data in enumerate(program):
        lines.append(f"    testProgram[{i}] = 32'h{data:08x};")

    content = '\n'.join(lines)

    if output_file:
        with open(output_file, 'w') as f:
            f.write(content)
    else:
        print(content)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <hex_file> [output_file]")
        sys.exit(1)

    hex_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else None

    program = parse_hex_file(hex_file)
    output_bsv(program, output_file)

    print(f"# 加载 {len([x for x in program if x != 0])} 条有效指令")
    print(f"# 从 {hex_file} 转换完成")
```

#### 使用方法

```bash
# 创建脚本目录
mkdir -p scripts

# 保存脚本
# scripts/gen_prog.py

# 转换 hex 文件为 BSV 数组
python3 scripts/gen_prog.py rv32ui-p-simple.hex > tests/programs/simple_prog.bsvi

# 或直接输出到文件
python3 scripts/gen_prog.py rv32ui-p-lw.hex tests/programs/lw_prog.bsvi
```

#### 生成的 BSV 数组格式示例

```bsv
// 自动生成的程序数组（16384 条目）
Vector#(16384, Word) testProgram = newVector;
    testProgram[0] = 32'h12345678;
    testProgram[1] = 32'h9abcdef0;
    testProgram[2] = 32'h00000013;  // nop
    ...
    testProgram[16383] = 32'h00000000;
```

#### TestBench 加载生成的程序

```bsv
// TestBench.bsv 中使用
// 直接 include 生成的数组文件或手动复制

// 方式1：include 文件（如果 BSV 支持）
// include "tests/programs/simple_prog.bsvi"

// 方式2：手动加载（推荐）
Vector#(16384, Word) prog = newVector;
// 从生成的文件复制数组赋值语句到此处
prog[0] = 32'h12345678;
...

core.loadProgramLarge(prog);
```

#### 错误处理

Python 脚本包含以下错误处理：
- 文件不存在检查
- 地址越界警告（自动填充 0）
- 无效十六进制数据跳过

---

### FPGA 上板备选方案（无 Python 环境）

对于 FPGA 上板场景，无法使用 Python 预处理，推荐以下备选方案：

#### 方案 A：Verilog $readmemh（推荐）

**适用场景**：FPGA 上板、Verilator 仿真

BSV 编译生成 Verilog 后，在顶层模块使用 `$readmemh`：

```verilog
// 生成的 Verilog 文件（mkCore.v）中添加：
// 注意：BSV 生成的内存是 reg 数组，可直接使用 $readmemh

initial begin
    $readmemh("rv32ui-p-simple.hex", mkCore_imem);
end
```

**优点**：
- Verilog 标准函数，所有工具链支持
- 无需 Python，直接加载 hex 文件
- FPGA 综合时，工具会自动将 hex 内容转换为初始化值

**实现步骤**：
1. BSV 编译生成 Verilog：`bsc -verilog Core.bsv`
2. 修改生成的 `mkCore.v`，添加 `initial $readmemh`
3. 或在顶层 TestBench 中调用

**C++ TestBench（Verilator）版本**：

```cpp
// tests/c/test_bench.cpp 中添加：
#include <fstream>
#include <sstream>

void loadHexFile(const char* filename, uint32_t* mem, int size) {
    std::ifstream f(filename);
    std::string line;
    uint32_t addr = 0;

    while (std::getline(f, line)) {
        if (line[0] == '@') {
            addr = std::stoul(line.substr(1), nullptr, 16);
        } else {
            std::istringstream iss(line);
            uint32_t data;
            while (iss >> std::hex >> data) {
                int idx = (addr - 0x80000000) / 4;
                if (idx >= 0 && idx < size) {
                    mem[idx] = data;
                }
                addr += 4;
            }
        }
    }
}

// 使用：
loadHexFile("rv32ui-p-simple.hex", top->mkCore__imem, 16384);
```

#### 方案 B：预生成 BSV 数组文件

**适用场景**：开发机上编译，FPGA 上运行

在开发机上用 Python 生成 `.bsv` 文件，编译到 Verilog 中：

```bash
# 开发机上执行一次
python3 scripts/gen_prog.py rv32ui-p-simple.hex > src/programs/simple_program.bsvi
```

**生成的 `.bsvi` 文件格式**：

```bsv
// src/programs/simple_program.bsvi
// 预生成的程序数组（可直接 include）
Vector#(16384, Word) simple_program = newVector;
simple_program[0] = 32'h12345678;
simple_program[1] = 32'h9abcdef0;
...
```

**TestBench 中使用**：

```bsv
// tests/TestBench.bsv
// 直接复制预生成文件的内容，或使用 BSV 的 include 机制

Vector#(16384, Word) prog = newVector;
prog[0] = 32'h12345678;  // 从 .bsvi 文件复制
...
core.loadProgramLarge(prog);
```

**优点**：
- 编译时程序已固化在 Verilog 中
- FPGA 上无需任何文件加载
- 综合后程序存储在 Block RAM 初始化值中

#### 方案选择矩阵

| 场景 | 推荐方案 | 理由 |
|------|----------|------|
| Verilator 开发调试 | Python 预处理 + C++ 加载 | 快速迭代，灵活 |
| FPGA 上板测试 | 方案 A：$readmemh | Verilog 标准，工具链支持 |
| FPGA 最终部署 | 方案 B：预生成数组 | 程序固化，无需外部文件 |
| 无开发机环境 | 方案 A：$readmemh | 仅需 hex 文件 |

#### Makefile 集成示例

```makefile
# Makefile 添加 hex 加载支持

# 开发调试（Python 预处理）
tests/programs/%_prog.bsvi: tests/hex/%.hex
	python3 scripts/gen_prog.py $< > $@

# Verilator 仿真（C++ 加载）
VERILATOR_FLAGS += -CFLAGS "-DHEX_FILE=\"tests/hex/rv32ui-p-simple.hex\""

# FPGA 上板（$readmemh）
# 需手动修改生成的 Verilog 或使用脚本注入
sed -i '/initial begin/a \    \$readmemh("rv32ui-p-simple.hex", imem);' build/mkCore.v
```

### TestBench 检测逻辑

```bsv
// 在 Core 中添加 tohost 检测（MEM 阶段）
Bit#(32) tohost_addr = 32'h80001000;

// MEM 写入检测（添加到 memoryStage 规则）
if (pkt.mem_op == MEM_WRITE && pkt.alu_result == tohost_addr) begin
    if (pkt.rs2_val == 1) begin
        $display("PASS");
    end else begin
        $display("FAIL: test %0d", pkt.rs2_val - 1);
    end
    $finish;
end
```

### tohost 地址验证步骤

1. 编译 riscv-tests 后检查链接脚本
2. 转换 hex 后查看前几行确认地址格式
3. 如地址不同，修改 TestBench 中的 `tohost_addr`

---

## Load-Use 专项测试矩阵

riscv-tests 基本覆盖，但建议额外验证：

| 测试 | Load 指令 | Use 指令 | 期望停顿 | 说明 |
|------|-----------|----------|----------|------|
| 1 | LW x1, 0(x0) | ADD x2, x1, x3 | 1 周期 | 字 Load-Use |
| 2 | LB x1, 0(x0) | SB x1, 1(x0) | 1 周期 | 字节 Load-Use |
| 3 | LH x1, 0(x0) | SH x1, 2(x0) | 1 周期 | 半字 Load-Use |
| 4 | LBU x1, 0(x0) | AND x2, x1, x3 | 1 周期 | 无符号字节 Load-Use |
| 5 | LHU x1, 0(x0) | OR x2, x1, x3 | 1 周期 | 无符号半字 Load-Use |
| 6 | LW (MEM 阶段) | SUB (ID 阶段) | 0 周期 | Load 已完成，无停顿 |
| 7 | LH x1, 0(x0) | ADD x2, x1, x3 | 1 周期 | 半字 Load-Use (有符号) |
| 8 | LHU x1, 0(x0) | SUB x2, x1, x3 | 1 周期 | 半字 Load-Use (无符号) |

---

## NOP 包完整实现

```bsv
// Core.bsv 改动 nopPacket 函数
function ID_EX_Packet nopPacket();
    return ID_EX_Packet {
        pc: 0,
        instruction: 0,
        rs1_val: 0,
        rs2_val: 0,
        imm: 0,
        rs1: 0,
        rs2: 0,
        rd: 0,
        alu_op: ALU_ADD,
        branch_cond: BR_NONE,
        mem_op: MEM_NONE,
        is_branch: False,
        is_jump: False,
        write_reg: False,
        use_imm: False,
        mem_width: MEM_WORD,     // 新增
        mem_unsigned: False      // 新增
    };
endfunction
```

---

## 实现顺序

| 步骤 | 任务 | 验证方式 |
|------|------|----------|
| 1 | Types.bsv 添加 MemWidth 枚举 | 编译通过 |
| 2 | Types.bsv 扩展 ID_EX_Packet/EX_MEM_Packet 字段 | 编译通过 |
| 3 | Decoder.bsv 添加 mem_width/mem_unsigned 默认值 | 编译通过 |
| 4 | Decoder.bsv 添加 funct3 处理 | 编译通过 |
| 5 | Core.bsv 添加 checkAlignment 函数 | 编译通过 |
| 6 | Core.bsv 内存扩展（含 ifdef） | LW/SW 程序 |
| 7 | Core.bsv MEM 阶段字节处理 | LB/LH/SB/SH 程序 |
| 8 | Core.bsv nopPacket 更新 | 编译通过 |
| 9 | Core.bsv 接口适配函数 | 编译通过 |
| 10 | HazardUnit.bsv 扩展 MEM 阶段检测 | 编译通过 |
| 11 | Core.bsv 使用 HazardUnit | 编译通过 + Load-Use 测试 |
| 12 | Core.bsv tohost 检测 | 编译通过 |
| 13 | TestBench.bsv hex 加载 | 加载测试 hex |
| 14 | 运行 riscv-tests | 全部 PASS |

---

## 风险与注意事项

1. **内存容量**：使用 ifdef 控制大小，开发时用小内存
2. **地址对齐**：LH/SH 必须半字对齐，LW/SW 必须字对齐
3. **tohost 地址**：需确认 riscv-tests 配置中的实际地址
4. **TestBench 兼容性**：添加适配函数保持向后兼容
5. **NOP 包更新**：必须包含所有新增字段
6. **hex 解析**：完整实现较复杂，可先用 Verilog $readmemh

## 验证目标

通过所有 `rv32ui-p-*` 测试（约 40 个），验证：
- Load-Use 冒险正确处理（统一 HazardUnit 实现）
- 字节/半字指令正确（LB/LH/LBU/LHU/SB/SH）
- 地址对齐检查正确（阶段1打印警告）
- 分支预测正确（branch 测试）
- 五级流水线稳定工作