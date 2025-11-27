PROJECT = riscv-bsv-processor
BSC = bsc
BSC_FLAGS = -show-schedule -wait-for-license -aggressive-conditions
VERILATOR = verilator
CC = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump

# Bluespec include paths
BSC_PATHS = -p src:src/common:src/core:src/memory:src/soc:%/Libraries

BSV_SOURCES = $(wildcard src/*.bsv) \
              $(wildcard src/common/*.bsv) \
              $(wildcard src/core/*.bsv) \
              $(wildcard src/memory/*.bsv) \
              $(wildcard src/soc/*.bsv)

ASM_TESTS = $(wildcard tests/assembly/*.s)
C_TESTS   = $(wildcard tests/c/*.c)

all: compile

compile: $(BSV_SOURCES)
	mkdir -p build
	$(BSC) -verilog $(BSC_PATHS) -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv

firmware/%.hex: tests/assembly/%.s
	$(CC) -nostdlib -T scripts/link.ld $< -o firmware/$*.elf
	$(OBJCOPY) -O verilog firmware/$*.elf firmware/$*.hex
	$(OBJDUMP) -d firmware/$*.elf > firmware/$*.dump

simulate: firmware/simple_test.hex compile
	$(BSC) -verilog $(BSC_PATHS) -bdir build -vdir build \
	    -D TEST_PROGRAM=\"firmware/simple_test.hex\" \
	    -u -g mkTestBench src/soc/TestBench.bsv
	$(VERILATOR) --cc --exe --build -o VmkTestBench build/mkTestBench.v tests/c/test_bench.cpp -Wno-STMTDLY
	./obj_dir/VmkTestBench
clean:
	rm -rf mk*.v *.bo build/* firmware/*.hex firmware/*.elf firmware/*.dump
