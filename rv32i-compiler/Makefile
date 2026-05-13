CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99 -O2
SRCDIR   = src
BUILDDIR = build
RTDIR    = runtime
TSTDIR   = tests

SRCS = $(SRCDIR)/main.c $(SRCDIR)/lexer.c $(SRCDIR)/parser.c \
       $(SRCDIR)/codegen.c $(SRCDIR)/asm.c $(SRCDIR)/linker.c \
       $(SRCDIR)/ast.c $(SRCDIR)/types.c

OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/lexer.o $(BUILDDIR)/parser.o \
       $(BUILDDIR)/codegen.o $(BUILDDIR)/asm.o $(BUILDDIR)/linker.o \
       $(BUILDDIR)/ast.o $(BUILDDIR)/types.o

.PHONY: all test clean test-phase2 test-phase2-a test-phase2-b test-phase2-c \
        test-phase2-d test-phase2-e test-phase2-f test-phase2-g \
        test-phase3 test-phase3-precedence test-phase3-if-true test-phase3-if-false \
        test-phase3-if-else test-phase3-while test-phase3-for \
        test-phase4 test-phase4-fib test-phase4-add test-phase4-call test-phase4-multi \
        test-phase5 test-phase5-swap \
        test-phase6 test-phase6-array

all: $(BUILDDIR)/microcc

$(BUILDDIR)/microcc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Phase 1 regression test with lib.S
$(BUILDDIR)/test.hex: $(BUILDDIR)/microcc $(TSTDIR)/test.c $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $(TSTDIR)/test.c $@ $(RTDIR)/crt0.s $(BUILDDIR)/_user.s $(RTDIR)/lib.S

test: $(BUILDDIR)/test.hex
	@cp $(BUILDDIR)/test.hex ../build/test.hex 2>/dev/null || mkdir -p ../build && cp $(BUILDDIR)/test.hex ../build/test.hex
	@cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv
	@cd .. && $(MAKE) -s compile verilator 2>/dev/null
	@echo "--- CPU Output ---"
	@cd .. && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost="); \
	echo "$$result"; \
	if echo "$$result" | grep -q "tohost=0x0000002a\|tohost=0x2a"; then \
		echo "✓ PASSED: tohost=42"; \
	else \
		echo "✗ FAILED: expected tohost=42"; \
	fi

# ----- Phase 2 test hex targets -----
HEX2 = build/phase2_a.hex build/phase2_b.hex build/phase2_c.hex \
       build/phase2_d.hex build/phase2_e.hex build/phase2_f.hex build/phase2_g.hex

$(HEX2): build/phase2_%.hex: tests/phase2/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase2_$*.s $(RTDIR)/lib.S

# ----- Phase 2 test execution targets -----
test-phase2-a: build/phase2_a.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000003" && echo "✓ PASSED (tohost=3)" || echo "✗ FAILED (expected tohost=3)"

test-phase2-b: build/phase2_b.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000007" && echo "✓ PASSED (tohost=7)" || echo "✗ FAILED (expected tohost=7)"

test-phase2-c: build/phase2_c.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x0000002a" && echo "✓ PASSED (tohost=42)" || echo "✗ FAILED (expected tohost=42)"

test-phase2-d: build/phase2_d.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000006" && echo "✓ PASSED (tohost=6)" || echo "✗ FAILED (expected tohost=6)"

test-phase2-e: build/phase2_e.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000004" && echo "✓ PASSED (tohost=4)" || echo "✗ FAILED (expected tohost=4)"

test-phase2-f: build/phase2_f.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x0000000f" && echo "✓ PASSED (tohost=15)" || echo "✗ FAILED (expected tohost=15)"

test-phase2-g: build/phase2_g.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000003" && echo "✓ PASSED (tohost=3)" || echo "✗ FAILED (expected tohost=3)"

test-phase2: test-phase2-a test-phase2-b test-phase2-c test-phase2-d \
             test-phase2-e test-phase2-f test-phase2-g
	@echo "=== All Phase 2 tests done ==="

# ----- Phase 3 test hex targets -----
HEX3 = build/phase3_precedence.hex build/phase3_if_true.hex build/phase3_if_false.hex \
       build/phase3_if_else.hex build/phase3_while.hex build/phase3_for.hex

$(HEX3): build/phase3_%.hex: tests/phase3/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase3_$*.s $(RTDIR)/lib.S

# ----- Phase 3 test execution targets -----
test-phase3-precedence: build/phase3_precedence.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000007" && echo "✓ PASSED (tohost=7)" || echo "✗ FAILED (expected tohost=7)"

test-phase3-if-true: build/phase3_if_true.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000003" && echo "✓ PASSED (tohost=3)" || echo "✗ FAILED (expected tohost=3)"

test-phase3-if-false: build/phase3_if_false.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000005" && echo "✓ PASSED (tohost=5)" || echo "✗ FAILED (expected tohost=5)"

test-phase3-if-else: build/phase3_if_else.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000003" && echo "✓ PASSED (tohost=3)" || echo "✗ FAILED (expected tohost=3)"

test-phase3-while: build/phase3_while.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000003" && echo "✓ PASSED (tohost=3)" || echo "✗ FAILED (expected tohost=3)"

test-phase3-for: build/phase3_for.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000003" && echo "✓ PASSED (tohost=3)" || echo "✗ FAILED (expected tohost=3)"

test-phase3: test-phase3-precedence test-phase3-if-true test-phase3-if-false \
             test-phase3-if-else test-phase3-while test-phase3-for
	@echo "=== All Phase 3 tests done ==="

# ----- Phase 4 test hex targets -----
HEX4 = build/phase4_fib.hex build/phase4_add.hex build/phase4_call.hex build/phase4_multi.hex

$(HEX4): build/phase4_%.hex: tests/phase4/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase4_$*.s $(RTDIR)/lib.S

# ----- Phase 4 test execution targets -----
test-phase4-fib: build/phase4_fib.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 90 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000037" && echo "✓ PASSED (tohost=55)" || echo "✗ FAILED (expected tohost=55)"

test-phase4-add: build/phase4_add.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000008" && echo "✓ PASSED (tohost=8)" || echo "✗ FAILED (expected tohost=8)"

test-phase4-call: build/phase4_call.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x0000002a" && echo "✓ PASSED (tohost=42)" || echo "✗ FAILED (expected tohost=42)"

test-phase4-multi: build/phase4_multi.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000006" && echo "✓ PASSED (tohost=6)" || echo "✗ FAILED (expected tohost=6)"

test-phase4: test-phase4-fib test-phase4-add test-phase4-call test-phase4-multi
	@echo "=== All Phase 4 tests done ==="

# ----- Phase 5 test hex targets -----
HEX5 = build/phase5_swap.hex

$(HEX5): build/phase5_%.hex: tests/phase5/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase5_$*.s $(RTDIR)/lib.S

# ----- Phase 5 test execution targets -----
test-phase5-swap: build/phase5_swap.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x00000002" && echo "✓ PASSED (tohost=2)" || echo "✗ FAILED (expected tohost=2)"

test-phase5: test-phase5-swap
	@echo "=== All Phase 5 tests done ==="

# ----- Phase 6 test hex targets -----
HEX6 = build/phase6_array.hex

$(HEX6): build/phase6_%.hex: tests/phase6/test_%.c $(BUILDDIR)/microcc $(RTDIR)/crt0.s $(RTDIR)/lib.S
	@mkdir -p $(BUILDDIR)
	./$(BUILDDIR)/microcc $< $@ $(RTDIR)/crt0.s $(BUILDDIR)/_phase6_$*.s $(RTDIR)/lib.S

# ----- Phase 6 test execution targets -----
test-phase6-array: build/phase6_array.hex
	@cp $< ../build/test.hex && cd .. && python3 tools/hex_to_bsv.py build/test.hex > src/soc/TestProgram.bsv && $(MAKE) -s compile verilator 2>/dev/null && result=$$(timeout 30 ./obj_dir/VmkTestBench 2>&1 | grep "tohost=") && echo "$$result" && echo "$$result" | grep -q "tohost=0x0000000f" && echo "✓ PASSED (tohost=15)" || echo "✗ FAILED (expected tohost=15)"

test-phase6: test-phase6-array
	@echo "=== All Phase 6 tests done ==="

clean:
	rm -rf $(BUILDDIR)
