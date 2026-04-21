#!/usr/bin/env python3
"""
从 Verilog hex 文件生成 BSV 测试程序。

用法：
    python3 tools/hex_to_bsv.py firmware/pipeline_test.hex > src/soc/test_program.bsv
"""

import sys

def parse_hex(hex_file):
    """解析 Verilog hex 文件（字节序列，小端序）"""
    words = {}
    current_addr = 0

    with open(hex_file, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue

            if line.startswith('@'):
                current_addr = int(line[1:], 16)
                continue

            # 解析字节（小端序，每行多个字节）
            bytes_data = line.split()
            for i in range(0, len(bytes_data), 4):
                if i + 3 < len(bytes_data):
                    # 组合4字节为32位字（小端序）
                    b0 = int(bytes_data[i], 16)
                    b1 = int(bytes_data[i+1], 16)
                    b2 = int(bytes_data[i+2], 16)
                    b3 = int(bytes_data[i+3], 16)
                    word = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24)

                    # 地址索引
                    idx = (current_addr - 0x80000000) // 4
                    words[idx] = word
                    current_addr += 4

    return words

def generate_bsv(words, max_words=4096):
    """生成 BSV 程序定义"""
    print("// Auto-generated test program from hex file")
    print("package TestProgram;")
    print("import Types::*;")
    print("import Vector::*;")
    print("")
    print(f"function Vector#({max_words}, Word) testProgram();")
    print(f"    Vector#({max_words}, Word) prog = replicate(0);")
    print("")

    for idx in sorted(words.keys()):
        if idx >= 0 and idx < max_words:
            word = words[idx]
            addr = 0x80000000 + idx * 4
            print(f"    prog[{idx}] = 32'h{word:08x};  // @ {addr:#x}")

    print("")
    print("    return prog;")
    print("endfunction")
    print("endpackage")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 tools/hex_to_bsv.py <hex_file>", file=sys.stderr)
        sys.exit(1)

    words = parse_hex(sys.argv[1])
    generate_bsv(words)
    print(f"\n// Generated {len(words)} words")

if __name__ == "__main__":
    main()