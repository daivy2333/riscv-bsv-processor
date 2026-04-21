# Makefile for RISC-V BSV Processor
# ============================================================

PROJECT = riscv-bsv-processor
BSC = /opt/bsc/bin/bsc
BSC_FLAGS = -no-warn-action-shadowing
VERILATOR = verilator
CC = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump

# Bluespec include paths
BSC_PATHS = -p src:src/common:src/core:src/memory:src/soc:src/branch:src/peripheral:%/Libraries

# ============================================================
# 测试列表
# ============================================================

# 基线测试（10个，全部通过）
BASELINE_TESTS = loop_test simple_arith_test load_test csr_basic_test \
                  privilege_m_mode_test csr_immediate_test rtype_complete_test \
                  itype_alu_test simple_branch_test simple_loop

# 定时器中断测试（新增，通过）
TIMER_TESTS = mtime_increment_verify mtimecmp_mtip_test

# 所有测试
ALL_TESTS = $(BASELINE_TESTS) $(TIMER_TESTS)

# FreeRTOS 测试
FREERTOS_TEST = freertos_demo

# ============================================================
# 默认目标
# ============================================================

all: compile verilator

# ============================================================
# 快捷测试命令
# ============================================================

# 运行单个测试：make test-loop_test
test-%:
	@echo "=== Running $* ==="
	@if [ ! -f "firmware/$*.hex" ]; then \
		echo "Compiling $*.s..."; \
		$(MAKE) asm-$*; \
	fi
	python3 tools/hex_to_bsv.py firmware/$*.hex > src/soc/TestProgram.bsv
	$(MAKE) compile
	$(MAKE) verilator
	timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep -E "Test Results"

# 运行所有基线测试
test-baseline:
	@echo "=== Running all baseline tests ==="
	@passed=0; failed=0; \
	for test in $(BASELINE_TESTS); do \
		result=$$($(MAKE) test-$$test 2>&1 | grep "Test Results"); \
		echo "$$test: $$result"; \
		if echo "$$result" | grep -q "PASSED"; then \
			passed=$$((passed + 1)); \
		else \
			failed=$$((failed + 1)); \
		fi; \
	done; \
	echo ""; \
	echo "=== Summary: $$passed passed, $$failed failed ==="

# 运行定时器中断测试
test-timer:
	@echo "=== Running timer interrupt tests ==="
	@for test in $(TIMER_TESTS); do \
		$(MAKE) test-$$test; \
	done

# 运行所有测试
test-all:
	@echo "=== Running all tests ==="
	@passed=0; failed=0; \
	for test in $(ALL_TESTS); do \
		result=$$($(MAKE) test-$$test 2>&1 | grep "Test Results"); \
		echo "$$test: $$result"; \
		if echo "$$result" | grep -q "PASSED"; then \
			passed=$$((passed + 1)); \
		else \
			failed=$$((failed + 1)); \
		fi; \
	done; \
	echo ""; \
	echo "=== Summary: $$passed passed, $$failed failed ==="

# ============================================================
# 编译流程
# ============================================================

compile:
	mkdir -p build
	$(BSC) -verilog $(BSC_PATHS) $(BSC_FLAGS) \
		-bdir build -vdir build \
		-u -g mkTestBench \
		src/soc/TestBench.bsv \
		+RTS -K32M -RTS

verilator:
	rm -rf obj_dir
	$(VERILATOR) --cc --exe --build \
		-o VmkTestBench \
		--top-module mkTestBench \
		build/mkTestBench.v \
		/opt/bsc/lib/Verilog/FIFO2.v \
		tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH

run:
	./obj_dir/VmkTestBench

# ============================================================
# 汇编编译（从 .s 到 .hex）
# ============================================================

# 编译单个汇编文件：make asm-loop_test
asm-%:
	@echo "=== Compiling $*.s ==="
	@if [ -f "tests/assembly/$*.s" ]; then \
		mkdir -p firmware; \
		$(CC) -march=rv32i_zicsr -mabi=ilp32 \
			-nostdlib -T scripts/link.ld \
			tests/assembly/$*.s -o firmware/$*.elf; \
		$(OBJCOPY) -O verilog firmware/$*.elf firmware/$*.hex; \
		echo "Generated firmware/$*.hex"; \
	else \
		echo "Error: tests/assembly/$*.s not found"; \
	fi

# 编译所有汇编测试
asm-all:
	@for test in $(ALL_TESTS); do \
		$(MAKE) asm-$$test; \
	done

# ============================================================
# FreeRTOS 测试
# ============================================================

test-freertos:
	@echo "=== Running FreeRTOS Demo ==="
	python3 tools/hex_to_bsv.py firmware/$(FREERTOS_TEST).hex > src/soc/TestProgram.bsv
	$(MAKE) compile
	$(MAKE) verilator
	timeout 120 ./obj_dir/VmkTestBench 2>&1 | tail -30

# ============================================================
# 调试模式
# ============================================================

# 详细调试输出
debug-%:
	@echo "=== Debug mode for $* ==="
	python3 tools/hex_to_bsv.py firmware/$*.hex > src/soc/TestProgram.bsv
	$(MAKE) compile
	$(MAKE) verilator
	./obj_dir/VmkTestBench 2>&1 | tee debug_$*.log

# ============================================================
# 清理
# ============================================================

clean:
	rm -rf build obj_dir firmware/*.elf firmware/*.hex firmware/*.dump
	rm -f debug_*.log freertos_debug.log

clean-all: clean
	rm -f src/soc/TestProgram.bsv

# ============================================================
# 帮助
# ============================================================

help:
	@echo "RISC-V BSV Processor - Makefile"
	@echo ""
	@echo "快速测试:"
	@echo "  make test-<name>      运行单个测试"
	@echo "  make test-baseline    运行所有基线测试（10个）"
	@echo "  make test-timer       运行定时器中断测试"
	@echo "  make test-all         运行所有测试（12个）"
	@echo "  make test-freertos    运行 FreeRTOS demo"
	@echo ""
	@echo "汇编编译:"
	@echo "  make asm-<name>       编译单个汇编文件"
	@echo "  make asm-all          编译所有汇编测试"
	@echo ""
	@echo "构建:"
	@echo "  make all              编译 BSV + Verilator"
	@echo "  make compile          仅编译 BSV"
	@echo "  make verilator        仅构建 Verilator"
	@echo "  make run              运行当前程序"
	@echo ""
	@echo "调试:"
	@echo "  make debug-<name>     详细调试输出"
	@echo ""
	@echo "清理:"
	@echo "  make clean            清理构建产物"
	@echo "  make clean-all        清理所有（含 TestProgram.bsv）"
	@echo ""
	@echo "示例:"
	@echo "  make test-loop_test"
	@echo "  make test-baseline"
	@echo "  make asm-all && make test-all"

.PHONY: all compile verilator run clean clean-all help \
        test-baseline test-timer test-all test-freertos \
        asm-all