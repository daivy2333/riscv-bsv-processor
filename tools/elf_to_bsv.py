#!/usr/bin/env python3
"""
ELF to BSV Memory Initializer
Parses an ELF file and generates BSV initialization vector for memory.
"""

import struct
import sys
import os

# ELF constants
ELFMAG = b'\x7fELF'
ELFCLASS32 = 1
ELFDATA2LSB = 1
EV_CURRENT = 1
ET_EXEC = 2
EM_RISCV = 243

# Program segment types
PT_LOAD = 1

def read_elf_header(f):
    """Read and validate ELF header."""
    magic = f.read(4)
    if magic != ELFMAG:
        raise ValueError("Not a valid ELF file")

    ei_class = struct.unpack('<B', f.read(1))[0]  # 32 or 64 bit
    ei_data = struct.unpack('<B', f.read(1))[0]   # little or big endian

    if ei_class != ELFCLASS32:
        raise ValueError("Only 32-bit ELF files are supported")
    if ei_data != ELFDATA2LSB:
        raise ValueError("Only little-endian ELF files are supported")

    # Skip rest of EI to reach offset 16 (skip 10 bytes after reading class and data)
    f.read(10)

    # Read ELF header fields
    e_type = struct.unpack('<H', f.read(2))[0]
    e_machine = struct.unpack('<H', f.read(2))[0]
    e_version = struct.unpack('<I', f.read(4))[0]

    if e_machine != EM_RISCV:
        raise ValueError(f"Not a RISC-V ELF (machine type {e_machine})")

    # Entry point
    e_entry = struct.unpack('<I', f.read(4))[0]

    # Program header offset
    e_phoff = struct.unpack('<I', f.read(4))[0]

    # Section header offset
    e_shoff = struct.unpack('<I', f.read(4))[0]

    # Flags
    e_flags = struct.unpack('<I', f.read(4))[0]

    # ELF header size
    e_ehsize = struct.unpack('<H', f.read(2))[0]

    # Program header entry size
    e_phentsize = struct.unpack('<H', f.read(2))[0]

    # Number of program headers
    e_phnum = struct.unpack('<H', f.read(2))[0]

    # Section header entry size
    e_shentsize = struct.unpack('<H', f.read(2))[0]

    # Number of section headers
    e_shnum = struct.unpack('<H', f.read(2))[0]

    # Section header string table index
    e_shstrndx = struct.unpack('<H', f.read(2))[0]

    return {
        'entry': e_entry,
        'phoff': e_phoff,
        'shoff': e_shoff,
        'phentsize': e_phentsize,
        'phnum': e_phnum,
        'shentsize': e_shentsize,
        'shnum': e_shnum,
        'shstrndx': e_shstrndx,
    }

def read_program_headers(f, header):
    """Read program headers and find LOAD segments."""
    f.seek(header['phoff'])

    segments = []
    for _ in range(header['phnum']):
        p_type = struct.unpack('<I', f.read(4))[0]
        p_offset = struct.unpack('<I', f.read(4))[0]
        p_vaddr = struct.unpack('<I', f.read(4))[0]
        p_filesz = struct.unpack('<I', f.read(4))[0]
        p_memsz = struct.unpack('<I', f.read(4))[0]
        p_flags = struct.unpack('<I', f.read(4))[0]

        if p_type == PT_LOAD:
            segments.append({
                'offset': p_offset,
                'vaddr': p_vaddr,
                'filesz': p_filesz,
                'memsz': p_memsz,
                'flags': p_flags,
            })
        else:
            # Skip non-LOAD segments
            f.read(16)

    return segments

def elf_to_bsv(elf_path, output_path=None):
    """Convert ELF file to BSV initialization vector."""

    with open(elf_path, 'rb') as f:
        header = read_elf_header(f)
        segments = read_program_headers(f, header)

    if not segments:
        print("No LOAD segments found in ELF file")
        return None

    # Find the smallest memory base address
    min_vaddr = min(s['vaddr'] for s in segments)
    max_vaddr = max(s['vaddr'] + s['filesz'] for s in segments)

    # Align to word boundary
    aligned_min = (min_vaddr // 4) * 4
    aligned_max = ((max_vaddr + 3) // 4) * 4

    # Create memory image
    mem_size = (aligned_max - aligned_min) // 4
    memory = [0] * mem_size

    # Load segments into memory
    with open(elf_path, 'rb') as f:
        for seg in segments:
            offset = seg['offset']
            vaddr = seg['vaddr']
            filesz = seg['filesz']

            f.seek(offset)
            data = f.read(filesz)

            # Write words to memory (little-endian)
            for i in range(0, filesz, 4):
                word = 0
                for j in range(4):
                    if i + j < filesz:
                        word |= data[i + j] << (8 * j)

                mem_idx = (vaddr + i - aligned_min) // 4
                if 0 <= mem_idx < mem_size:
                    memory[mem_idx] = word

    # Generate BSV code
    lines = []
    lines.append("// Auto-generated from {}".format(os.path.basename(elf_path)))
    lines.append("// Entry point: 0x{:08x}".format(header['entry']))
    lines.append("// Memory size: {} words".format(mem_size))
    lines.append("// Base address: 0x{:08x}".format(aligned_min))
    lines.append("")
    lines.append("function Vector#(1024, Word) loadFirmware();")
    lines.append("    Vector#(1024, Word) prog = replicate(0);")
    lines.append("")

    # Write non-zero words
    count = 0
    for i, word in enumerate(memory):
        if word != 0:
            addr = aligned_min + i * 4
            lines.append("    prog[{}] = 32'h{:08x};  // @ 0x{:08x}".format(i, word, addr))
            count += 1

    lines.append("")
    lines.append("    return prog;")
    lines.append("endfunction")

    # Write output
    output = '\n'.join(lines)
    if output_path:
        with open(output_path, 'w') as f:
            f.write(output)
        print(f"Generated BSV code: {output_path} ({count} non-zero words)")
    else:
        print(output)

    return {
        'entry': header['entry'],
        'memory': memory,
        'base': aligned_min,
        'size': mem_size,
    }

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: {} <elf-file> [output-file]".format(sys.argv[0]))
        print("\nExample:")
        print("  {} firmware/test_add.elf > src/soc/FirmwareData.bsv".format(sys.argv[0]))
        sys.exit(1)

    elf_path = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) > 2 else None

    try:
        result = elf_to_bsv(elf_path, output_path)
    except Exception as e:
        print("Error: {}".format(e))
        import traceback
        traceback.print_exc()
        sys.exit(1)
