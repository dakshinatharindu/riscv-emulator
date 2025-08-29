BIN_FILE=program.bin
ELF_FILE=program.elf
DEBUG_FILE=program.debug.txt
LINKER_SCRIPT=linker.lds

TARGETS = $(BIN_FILE) $(ELF_FILE) $(DEBUG_FILE)

CC=../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-gcc
OBJCOPY=../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-objcopy
OBJDUMP=../buildroot/output/host/bin/riscv32-buildroot-linux-uclibc-objdump

CFLAGS:=-fno-stack-protector
CFLAGS+=-static-libgcc -fdata-sections -ffunction-sections
CFLAGS+=-g -Os -march=rv32ima_zicsr -mabi=ilp32 -static
LDFLAGS:= -T $(LINKER_SCRIPT) -nostdlib -Wl,--gc-sections

SOURCES = program.c init.S
DEPENDENCIES = $(SOURCES) $(LINKER_SCRIPT) Makefile 

all: $(TARGETS)

$(ELF_FILE): $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(ELF_FILE) $(SOURCES)

$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY) -O binary $(ELF_FILE) $(BIN_FILE)

$(DEBUG_FILE): $(ELF_FILE)
	$(OBJDUMP) -t $(ELF_FILE) > $(DEBUG_FILE)
	$(OBJDUMP) -S $(ELF_FILE) >> $(DEBUG_FILE)
	xxd $(BIN_FILE) >> $(DEBUG_FILE)

clean:
	rm -f $(TARGETS)

