# Mini-OS Makefile

CC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-gcc
LD = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy

CFLAGS = -march=rv32i_zicsr -mabi=ilp32 -nostdlib -ffreestanding -O2 -Wall
CFLAGS += -I mini-os/include

ASFLAGS = -march=rv32i_zicsr -mabi=ilp32 -nostdlib

LDFLAGS = -march=rv32i_zicsr -mabi=ilp32 -nostdlib -T mini-os/mini-os.ld
LDFLAGS += -Wl,--gc-sections

SRCS = mini-os/src/os.c mini-os/src/task.c mini-os/src/uart.c mini-os/src/timer.c
SRCS += mini-os/src/trap.S mini-os/src/startup.S mini-os/src/libc.c

TEST_SRC = mini-os/tests/round_robin_demo.c

OBJS_DIR = build/mini-os

OBJS = $(OBJS_DIR)/os.o $(OBJS_DIR)/task.o $(OBJS_DIR)/uart.o $(OBJS_DIR)/timer.o
OBJS += $(OBJS_DIR)/trap.o $(OBJS_DIR)/startup.o $(OBJS_DIR)/libc.o

TARGET = $(OBJS_DIR)/mini-os.elf

all: $(TARGET)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(TARGET): $(OBJS_DIR) $(OBJS) $(TEST_SRC)
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $(OBJS_DIR)/demo.o
	$(LD) $(LDFLAGS) $(OBJS) $(OBJS_DIR)/demo.o -o $(TARGET)
	$(OBJCOPY) -O verilog $(TARGET) $(OBJS_DIR)/mini-os.hex
	@echo "Mini-OS built: $(OBJS_DIR)/mini-os.hex"

$(OBJS_DIR)/%.o: mini-os/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: mini-os/src/%.S
	$(AS) $(ASFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

.PHONY: all clean