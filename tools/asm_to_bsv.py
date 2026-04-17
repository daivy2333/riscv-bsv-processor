#!/usr/bin/env python3
"""
从汇编 dump 文件生成 BSV 测试程序编码。

用法：
    python3 tools/asm_to_bsv.py firmware/pipeline_test.dump > src/soc/test_program.bsv

然后在 TestBench.bsv 中 import TestProgram::*;
"""

import sys
import re

def parse_dump(dump_file):
    """从 objdump 输出解析指令"""
    instructions = []

    with open(dump_file, 'r') as f:
        for line in f:
            # 格式: "80000000:	40a9                	li	ra,10"
            match = re.match(r'(\w+):\s+(\w+)', line)
            if match:
                addr = int(match.group(1), 16)
                # 处理压缩指令（16位）和普通指令（32位）
                instr_hex = match.group(2)
                if len(instr_hex) == 4:  # 16位压缩指令
                    # 需要转换为32位（简化：目前不支持）
                    print(f"// Warning: 16-bit compressed instruction at {addr:#x}: {instr_hex}")
                    instr = int(instr_hex, 16)
                    # 扩展为32位（低位补0）
                    instructions.append((addr, instr, f"c.{instr_hex}"))
                elif len(instr_hex) == 8:  # 32位指令
                    instr = int(instr_hex, 16)
                    instructions.append((addr, instr, instr_hex))
                else:
                    print(f"// Warning: Unknown instruction format at {addr:#x}: {instr_hex}")

    return instructions

def generate_bsv(instructions, max_words=1024):
    """生成 BSV Vector 定义"""
    print("// Auto-generated test program")
    print("// Include in TestBench.bsv: import TestProgram::*;")
    print("")
    print("package TestProgram;")
    print("import Types::*;")
    print("import Vector::*;")
    print("")
    print(f"function Vector#({max_words}, Word) testProgram();")
    print(f"    Vector#({max_words}, Word) prog = replicate(0);")

    # 计算索引（PC基址 0x80000000）
    base_addr = 0x80000000

    for addr, instr, comment in instructions:
        idx = (addr - base_addr) // 4
        if idx >= 0 and idx < max_words:
            print(f"    prog[{idx}] = 32'h{instr:08x};  // {comment}")

    print("    return prog;")
    print("endfunction")
    print("")
    print("endpackage")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 tools/asm_to_bsv.py <dump_file>", file=sys.stderr)
        sys.exit(1)

    instructions = parse_dump(sys.argv[1])
    generate_bsv(instructions)

if __name__ == "__main__":
    main()