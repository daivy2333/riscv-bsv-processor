#!/usr/bin/env python3
"""
预处理 Verilator hex 文件，适配 BSV 内存配置。

riscv-tests 生成的 hex 文件使用 @address 格式，
需要转换为 BSV loadProgram 可用的 Vector 格式。

用法：
    python3 tools/preprocess_hex.py firmware/test.hex > firmware/test_mem.h
"""

import sys
import re

def preprocess_hex(hex_file):
    """读取 hex 文件并转换为 BSV 格式"""
    words = {}
    max_addr = 0

    with open(hex_file, 'r') as f:
        current_addr = 0
        for line in f:
            line = line.strip()
            if not line:
                continue

            # @address 格式设置当前地址
            if line.startswith('@'):
                addr = int(line[1:], 16)
                current_addr = addr
                continue

            # 数据行：每行一个 32-bit word
            # Verilog hex 格式：高位在前
            word_val = int(line, 16)
            # 转换地址为索引（PC 从 0x80000000 开始）
            idx = (current_addr - 0x80000000) // 4
            if idx >= 0 and idx < 1024:  # IMem 限制
                words[idx] = word_val
                max_addr = max(max_addr, idx)
            current_addr += 4

    # 生成 BSV 格式
    print(f"// Generated from {hex_file}")
    print(f"// Memory layout: IMem[{max_addr+1}] words used")
    print()
    print("#include <cstdint>")
    print("#include <vector>")
    print()
    print("const uint32_t test_program[] = {")

    for i in range(max_addr + 1):
        word = words.get(i, 0)
        print(f"    0x{word:08x},  // imem[{i}]")

    print("};")
    print(f"const size_t test_program_size = {max_addr + 1};")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 preprocess_hex.py <hex_file>", file=sys.stderr)
        sys.exit(1)

    preprocess_hex(sys.argv[1])

if __name__ == "__main__":
    main()