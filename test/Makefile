# Makefile for bare-metal RISC-V32 Hello World

# Toolchain - adjust if your toolchain has different prefix
CROSS_COMPILE ?= riscv32-unknown-elf-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# Flags
CFLAGS = -march=rv32ima -mabi=ilp32 -nostdlib -nostartfiles -ffreestanding -O2 -Wall
LDFLAGS = -T linker.ld -nostdlib -nostartfiles

# Files
TARGET = hello.elf
BINARY = hello.bin
SOURCES = hello.c start.S

all: $(TARGET) $(BINARY) disasm

$(TARGET): $(SOURCES) linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES)

$(BINARY): $(TARGET)
	$(OBJCOPY) -O binary $< $@

disasm: $(TARGET)
	$(OBJDUMP) -d $< > hello.asm

clean:
	rm -f $(TARGET) $(BINARY) hello.asm

run: $(TARGET)
	qemu-system-riscv32 -cpu rv32,mmu=false -machine virt -nographic -bios none -kernel $(TARGET)

debug: $(TARGET)
	qemu-system-riscv32 -cpu rv32,mmu=false -machine virt -nographic -bios none -kernel $(TARGET) -s -S

trace: $(TARGET)
	qemu-system-riscv32 -cpu rv32,mmu=false -machine virt -nographic -bios none -kernel $(TARGET) -d in_asm 2>&1 | head -200

.PHONY: all clean run debug trace disasm
