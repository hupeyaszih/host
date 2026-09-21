TARGET = build/host

ASM = nasm
ASFLAGS = -f bin

LD = ld
LDFLAGS =

BUILD_DIRECTORY = build

SOURCES = $(wildcard boot/*.asm)
#SOURCES = boot/boot_stage1.asm boot/boot_stage2.asm
MAIN_SOURCES = boot/boot_stage1.asm boot/boot_stage2.asm
OBJECTS = $(addprefix $(BUILD_DIRECTORY)/, $(MAIN_SOURCES:.asm=.bin))

$(TARGET): $(OBJECTS)
	cat $^ > $(TARGET)

$(BUILD_DIRECTORY)/%.bin: %.asm | $(BUILD_DIRECTORY)
	mkdir -p $(dir $@)
	$(ASM) $(ASFLAGS) $< -o $@

build:
	mkdir -p $(BUILD_DIRECTORY)

run: $(TARGET)
	qemu-system-x86_64 -drive format=raw,file=$(TARGET) -display sdl

clean:
	rm -rf $(BUILD_DIRECTORY)
