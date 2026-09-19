TARGET = build/host

ASM = nasm
ASFLAGS = -f bin

LD = ld
LDFLAGS =

BUILD_DIRECTORY = build

SOURCES = $(wildcard boot/*.asm)
OBJECTS = $(addprefix $(BUILD_DIRECTORY)/, $(SOURCES:.asm=.bin))

$(TARGET): $(OBJECTS)
	cat $^ > $(TARGET)

$(BUILD_DIRECTORY)/%.bin: %.asm | $(BUILD_DIRECTORY)
	mkdir -p $(dir $@)
	$(ASM) $(ASFLAGS) $< -o $@

build:
	mkdir -p $(BUILD_DIRECTORY)

run: $(TARGET)
	qemu-system-i386 -drive format=raw,file=$(TARGET) -display sdl

clean:
	rm -rf $(BUILD_DIRECTORY)
