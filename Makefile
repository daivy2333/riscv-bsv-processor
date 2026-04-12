PROJECT = riscv-bsv-processor
BSC = bsc
BSC_FLAGS = -show-schedule -aggressive-conditions -no-warn-action-shadowing
VERILATOR = verilator
CC = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump

# Bluespec include paths
BSC_PATHS = -p src:src/common:src/core:src/memory:src/soc:src/branch:%/Libraries

BSV_SOURCES = $(wildcard src/*.bsv) \
              $(wildcard src/common/*.bsv) \
              $(wildcard src/core/*.bsv) \
              $(wildcard src/memory/*.bsv) \
              $(wildcard src/soc/*.bsv) \
              $(wildcard src/branch/*.bsv)

ASM_TESTS = $(wildcard tests/assembly/*.s)

all: compile

compile: $(BSV_SOURCES)
	mkdir -p build
	$(BSC) -verilog $(BSC_PATHS) $(BSC_FLAGS) -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv

# 编译汇编测试为二进制
firmware/%.elf: tests/assembly/%.s scripts/link.ld
	mkdir -p firmware
	$(CC) -nostdlib -T scripts/link.ld $< -o $@

firmware/%.hex: firmware/%.elf
	$(OBJCOPY) -O verilog $< $@
	$(OBJDUMP) -d $< > firmware/$*.dump

# 编译二进制为内存初始化文件（用于BSV加载）
firmware/%.mem: firmware/%.elf
	$(OBJCOPY) -O binary $< $@
	xxd -i $@ > firmware/$*_mem.h

# Verilator仿真
verilate: compile
	$(VERILATOR) --cc --exe --build -o VmkTestBench \
		build/mkTestBench.v \
		tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH

# 运行仿真（需要先编译测试）
simulate: firmware/pipeline_test.mem verilate
	./obj_dir/VmkTestBench

# 快速测试（只编译BSV，不运行仿真）
test-compile: compile

clean:
	rm -rf build/* firmware/*.elf firmware/*.hex firmware/*.mem firmware/*.dump obj_dir/*