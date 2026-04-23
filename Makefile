# Makefile for RISC-V BSV Processor

BSC = /opt/bsc/bin/bsc
VERILATOR = verilator
CC = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy

BSC_PATHS = -p src:src/common:src/core:src/memory:src/soc:src/branch:src/peripheral:%/Libraries

BASELINE_TESTS = loop_test simple_arith_test load_test csr_basic_test \
                  privilege_m_mode_test csr_immediate_test rtype_complete_test \
                  itype_alu_test simple_branch_test simple_loop

TIMER_TESTS = mtime_increment_verify mtimecmp_mtip_test

ALL_TESTS = $(BASELINE_TESTS) $(TIMER_TESTS)

all:
	@echo "Run: make test-all"

# ============================================================
# 测试
# ============================================================

test-%:
	@echo -n "$*: "
	@if [ ! -f "build/$*.hex" ]; then $(MAKE) asm-$* >/dev/null 2>&1; fi
	@python3 tools/hex_to_bsv.py build/$*.hex > src/soc/TestProgram.bsv
	@$(MAKE) compile verilator >/dev/null 2>&1
	@result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep -E "Test Results"); \
	if echo "$$result" | grep -q "PASSED"; then echo "✓ PASSED"; else echo "✗ FAILED"; fi

test-baseline:
	@for t in $(BASELINE_TESTS); do $(MAKE) test-$$t; done

test-timer:
	@for t in $(TIMER_TESTS); do $(MAKE) test-$$t; done

test-all:
	@for t in $(ALL_TESTS); do $(MAKE) test-$$t; done

# ============================================================
# 编译
# ============================================================

compile:
	mkdir -p build
	$(BSC) -verilog $(BSC_PATHS) -no-warn-action-shadowing \
		-bdir build -vdir build \
		-u -g mkTestBench src/soc/TestBench.bsv \
		+RTS -K32M -RTS

verilator:
	rm -rf obj_dir
	$(VERILATOR) --cc --exe --build \
		-o VmkTestBench --top-module mkTestBench \
		build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v \
		tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH

run:
	./obj_dir/VmkTestBench

# ============================================================
# 汇编
# ============================================================

asm-%:
	@mkdir -p build
	$(CC) -march=rv32i_zicsr -mabi=ilp32 -nostdlib -T scripts/link.ld \
		tests/assembly/$*.s -o build/$*.elf
	$(OBJCOPY) -O verilog build/$*.elf build/$*.hex

asm-all:
	@for t in $(ALL_TESTS); do $(MAKE) asm-$$t; done

# ============================================================
# Mini-OS
# ============================================================

test-mini-os:
	@echo "=== Mini-OS Demo ==="
	$(MAKE) -f mini-os/Makefile
	python3 tools/hex_to_bsv.py build/mini-os/mini-os.hex > src/soc/TestProgram.bsv
	mkdir -p build
	$(BSC) -verilog $(BSC_PATHS) -no-warn-action-shadowing \
		-bdir build -vdir build \
		-u -g mkMiniOSBench src/soc/MiniOSBench.bsv \
		+RTS -K64M -RTS
	rm -rf obj_dir
	$(VERILATOR) --cc --exe --build \
		-o VmkMiniOSBench --top-module mkMiniOSBench \
		build/mkMiniOSBench.v /opt/bsc/lib/Verilog/FIFO2.v \
		tests/c/mini_os_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH -Wno-TIMESCALEMOD \
		-LDFLAGS "-pthread"
	./obj_dir/VmkMiniOSBench

# ============================================================
# 清理
# ============================================================

clean:
	rm -rf build obj_dir

clean-all: clean
	rm -f src/soc/TestProgram.bsv

help:
	@echo "测试:"
	@echo "  make test-all      全部测试"
	@echo "  make test-<name>   单个测试"
	@echo "  make test-mini-os  Mini-OS Demo"
	@echo ""
	@echo "清理:"
	@echo "  make clean"

.PHONY: all compile verilator run clean clean-all help \
        test-baseline test-timer test-all asm-all test-mini-os