# FreeRTOS Demo Makefile for RV32I Processor

CC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-gcc
LD = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy

# Compiler flags
CFLAGS = -march=rv32i_zicsr -mabi=ilp32 -nostdlib -ffreestanding -O2 -Wall
CFLAGS += -I freertos/include -I freertos/portable/GCC/RV32I
CFLAGS += -I firmware

# Assembler flags
ASFLAGS = -march=rv32i_zicsr -mabi=ilp32 -nostdlib

# Linker flags
LDFLAGS = -march=rv32i_zicsr -mabi=ilp32 -nostdlib -T firmware/freertos.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -lgcc

# Source files
FREERTOS_SRCS = freertos/tasks.c freertos/queue.c freertos/list.c
FREERTOS_SRCS += freertos/portable/MemMang/heap_4.c
PORT_SRCS = freertos/portable/GCC/RV32I/port.c freertos/portable/GCC/RV32I/portASM.S
LIBC_SRCS = firmware/libc.c
DEMO_SRCS = firmware/freertos_demo.c firmware/startup.S

# All sources
SRCS = $(FREERTOS_SRCS) $(PORT_SRCS) $(LIBC_SRCS) $(DEMO_SRCS)

# Object files
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.S=.o)

# Output
TARGET = firmware/freertos_demo.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -lgcc -o $(TARGET)
	$(OBJCOPY) -O verilog $(TARGET) firmware/freertos_demo.hex
	@echo "FreeRTOS demo compiled: firmware/freertos_demo.hex"

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile assembly files
%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) firmware/freertos_demo.hex

.PHONY: all clean