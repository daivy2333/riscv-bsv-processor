PROJECT = riscv-bsv-processor
BSC = /opt/bsc/bin/bsc
BSC_FLAGS = -no-warn-action-shadowing
VERILATOR = verilator
CC = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump

# Bluespec include paths
BSC_PATHS = -p src:src/common:src/core:src/memory:src/soc:src/branch:src/peripheral:%/Libraries

# 所有测试名称
TESTS = simple_arith_test load_test csr_basic_test csr_immediate_test \
        privilege_m_mode_test rtype_complete_test itype_alu_test \
        simple_branch_test simple_loop

# FreeRTOS 测试
FREERTOS_TEST = freertos_demo

all: test-all

# ============================================================
# 完整测试流程（一个命令搞定）
# ============================================================

# 运行单个测试：make test TEST=simple_arith_test
test: verilate
	@if [ -z "$(TEST)" ]; then \
		echo "Usage: make test TEST=<test_name>"; \
		echo "Available tests: $(TESTS)"; \
		exit 1; \
	fi
	@echo "=== Running $(TEST) ==="
	python3 tools/hex_to_bsv.py firmware/$(TEST).hex > src/soc/TestProgram.bsv
	$(BSC) -verilog $(BSC_PATHS) $(BSC_FLAGS) -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS
	rm -rf obj_dir && $(VERILATOR) --cc --exe --build -o VmkTestBench \
		build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH
	./obj_dir/VmkTestBench | grep -E "(PASSED|FAILED|Cycles)"

# 运行所有测试：make test-all
test-all:
	@for test in $(TESTS); do \
		echo "=== $$test ==="; \
		$(MAKE) test TEST=$$test 2>&1 | tail -3; \
	done

# ============================================================
# 编译流程
# ============================================================

compile: src/soc/TestProgram.bsv
	mkdir -p build
	$(BSC) -verilog $(BSC_PATHS) $(BSC_FLAGS) -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS

verilate: compile
	rm -rf obj_dir
	$(VERILATOR) --cc --exe --build -o VmkTestBench \
		build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH

# ============================================================
# 汇编编译（从 .s 到 .hex）
# ============================================================

firmware/%.elf: tests/assembly/%.s scripts/link.ld
	mkdir -p firmware
	$(CC) -march=rv32i_zicsr -mabi=ilp32 -nostdlib -T scripts/link.ld $< -o $@

firmware/%.hex: firmware/%.elf
	$(OBJCOPY) -O verilog $< $@
	$(OBJDUMP) -d $< > firmware/$*.dump

# 编译所有汇编测试
asm-tests:
	@for f in $(TESTS); do \
		echo "Compiling $$f..."; \
		$(MAKE) firmware/$$f.hex; \
	done

# ============================================================
# 调试模式（详细输出）
# ============================================================

debug: verilate
	@if [ -z "$(TEST)" ]; then \
		echo "Usage: make debug TEST=<test_name>"; \
		exit 1; \
	fi
	python3 tools/hex_to_bsv.py firmware/$(TEST).hex > src/soc/TestProgram.bsv
	$(BSC) -verilog $(BSC_PATHS) $(BSC_FLAGS) -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS
	rm -rf obj_dir && $(VERILATOR) --cc --exe --build -o VmkTestBench \
		build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH
	./obj_dir/VmkTestBench 2>&1 | tee debug.log

# ============================================================
# FreeRTOS 测试
# ============================================================

freertos: verilate
	@echo "=== Running FreeRTOS Demo ==="
	python3 tools/hex_to_bsv.py firmware/$(FREERTOS_TEST).hex > src/soc/TestProgram.bsv
	$(BSC) -verilog $(BSC_PATHS) $(BSC_FLAGS) -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS
	rm -rf obj_dir && $(VERILATOR) --cc --exe --build -o VmkTestBench \
		build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH
	./obj_dir/VmkTestBench | head -100

# FreeRTOS 详细调试（保存日志）
freertos-debug: verilate
	python3 tools/hex_to_bsv.py firmware/$(FREERTOS_TEST).hex > src/soc/TestProgram.bsv
	$(BSC) -verilog $(BSC_PATHS) $(BSC_FLAGS) -bdir build -vdir build -u -g mkTestBench src/soc/TestBench.bsv +RTS -K32M -RTS
	rm -rf obj_dir && $(VERILATOR) --cc --exe --build -o VmkTestBench \
		build/mkTestBench.v /opt/bsc/lib/Verilog/FIFO2.v tests/c/test_bench.cpp \
		-Wno-STMTDLY -Wno-WIDTH
	./obj_dir/VmkTestBench 2>&1 | tee freertos_debug.log

# ============================================================
# 清理
# ============================================================

clean:
	rm -rf build obj_dir firmware/*.elf firmware/*.hex firmware/*.mem firmware/*.dump debug.log

.PHONY: all test test-all compile verilate asm-tests debug freertos freertos-debug clean