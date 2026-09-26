BUILD_DIR = build
TARGET = $(BUILD_DIR)/host.bin

ASM_SOURCES = boot/boot_stage1.asm \
			  boot/boot_stage2.asm

C_SOURCES = src/kernel/kernel.c \
			src/kernel/vga.c \
			src/utils/hstring.c

COMPILER  = gcc
ASSEMBLER = nasm
LINKER = ld


# ARCH (currently, the only available arch is x86_64)
ARCH ?= x86_64
ARCH_INCLUDE = include/arch/$(ARCH)
C_SOURCES += $(wildcard src/arch/$(ARCH)/*.c)
#


CFLAGS = -m64 -ffreestanding -mno-red-zone -mno-sse -mno-mmx -fno-pie -fno-stack-protector -fno-builtin -Wall -Wextra -Iinclude -I$(ARCH_INCLUDE) -c
ASFLAGS = -f elf64
ASFLAGS_BIN = -f bin
LDFLAGS = -n -T linker.ld -nostdlib

OBJECTS_C = $(C_SOURCES:%.c=$(BUILD_DIR)/%.o)
OBJECTS_ASM = $(ASM_SOURCES:%.asm=$(BUILD_DIR)/%.o)

BOOT1_BIN = $(BUILD_DIR)/boot_stage1.bin
BOOT2_BIN = $(BUILD_DIR)/boot_stage2.bin
KERNEL_ELF = $(BUILD_DIR)/kernel.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin

all: $(TARGET)

$(TARGET): $(BOOT1_BIN) $(BOOT2_BIN) $(KERNEL_BIN)
	cat $(BOOT1_BIN) $(BOOT2_BIN) $(KERNEL_BIN) > $(TARGET)
	@echo "Compiling process is finished! HOST IS COMPILED!"

$(BOOT1_BIN): boot/boot_stage1.asm | $(BUILD_DIR)
	$(ASSEMBLER) $(ASFLAGS_BIN) $< -o $@

$(BOOT2_BIN): boot/boot_stage2.asm | $(BUILD_DIR)
	$(ASSEMBLER) $(ASFLAGS_BIN) $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(COMPILER) $(CFLAGS) $< -o $@

$(KERNEL_ELF): $(OBJECTS_C) linker.ld
	$(LINKER) $(LDFLAGS) $(OBJECTS_C) -o $@

$(KERNEL_BIN): $(KERNEL_ELF)
	objcopy -O binary $< $@
	@size=$$(stat -c%s $@); \
	    rem=$$((size % 512)); \
		if [ $$rem -ne 0 ]; then \
		pad=$$((512 - rem)); \
		dd if=/dev/zero bs=1 count=$$pad >> $@ 2>/dev/null; \
		fi

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	qemu-system-x86_64 -drive format=raw,file=$(TARGET) -display sdl -m 4G

clean:
	rm -rf $(BUILD_DIR)
