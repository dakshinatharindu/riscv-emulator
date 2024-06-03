BIN_FILE=program.bin
ELF_FILE=program.elf
DEBUG_FILE=program.debug.txt
LINKER_SCRIPT=linker.lds

TARGETS = $(BIN_FILE) $(ELF_FILE) $(DEBUG_FILE)

CC=/opt/riscv/bin/riscv32-unknown-elf-gcc
OBJCOPY=/opt/riscv/bin/riscv32-unknown-elf-objcopy
OBJDUMP=/opt/riscv/bin/riscv32-unknown-elf-objdump

CFLAGS = -march=rv32i -mabi=ilp32
LDFLAGS = -nostdlib -T $(LINKER_SCRIPT) #-g -nostartfiles

SOURCES = program.c
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

