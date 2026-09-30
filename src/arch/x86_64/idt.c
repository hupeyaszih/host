#include "kernel/idt.h"
#include "kernel/vga.h"
#include "utils/klibc.h"

#define STOP_CPU __asm__ __volatile__ ("cli; hlt")

const uint32_t IDT_TABLE_ENTRY_COUNT     = 22;
const uint32_t IDT_TABLE_MAX_ENTRY_COUNT = 256;

struct idt_entry entries[256]; ///< @brief Entries of the IDT table in x86_64. @attention The reason why this is defined as a global is that it shouldn't be in stack and doesn't need to be in a specific address.
struct idt_ptr idt_ptr;

static void idt_set_gate(int16_t entry_id, void(*handler)(struct idt_interrupt_frame *frame), uint8_t type_attributes) {
    uint64_t handler_address = (uint64_t) handler;

    entries[entry_id].offset_1 = (uint16_t)(handler_address & 0xFFFF);
    entries[entry_id].selector = 0x08; // Kernel Code Segment (see long mode GDT)
    entries[entry_id].ist = 0;
    entries[entry_id].type_attributes = type_attributes;
    entries[entry_id].offset_2 = (uint16_t)((handler_address >> 16) & 0xFFFF);
    entries[entry_id].offset_3 = (uint32_t)((handler_address >> 32) & 0xFFFFFFFF);
    entries[entry_id].reserved = 0;
}

void idt_init_idt(void) {
    idt_set_gate(0, x86_64_idt_divide_error, 0x8E);
    idt_set_gate(1, x86_64_idt_debug_exception, 0x8E);
    idt_set_gate(2, x86_64_idt_nmi_interrupt, 0x8E);
    idt_set_gate(3, x86_64_idt_breakpoint, 0x8E);
    idt_set_gate(4, x86_64_idt_overflow, 0x8E);

    for(uint32_t i = 5;i < IDT_TABLE_MAX_ENTRY_COUNT; ++i) {
        if(i == 13) continue;
        idt_set_gate(i, x86_64_idt_default, 0x8E);
    }

    idt_set_gate(13, x86_64_idt_gp, 0x8E);

    idt_ptr.limit = (sizeof(struct idt_entry) * IDT_TABLE_MAX_ENTRY_COUNT) - 1;
    idt_ptr.base  = (uint64_t) &entries[0];
}

void idt_load_idt(void) {
    __asm__ __volatile__ ("lidt %0" : : "m"(idt_ptr));
    __asm__ __volatile__ ("sti");
}

__attribute__((interrupt))
void x86_64_idt_divide_error   (struct idt_interrupt_frame *frame) {
    kprintf(VGA_COLOR_RED, 0, 0, "KERNEL PANIC: division error, instrution: %lx", frame->instruction_pointer);
    STOP_CPU;
}

__attribute__((interrupt))
void x86_64_idt_debug_exception(struct idt_interrupt_frame *frame) {
    kprintf(VGA_COLOR_RED, 0, 0, "KERNEL PANIC: debug exception, instrution: %lx", frame->instruction_pointer);
    STOP_CPU;
}

__attribute__((interrupt))
void x86_64_idt_nmi_interrupt  (struct idt_interrupt_frame *frame) {
    kprintf(VGA_COLOR_RED, 0, 0, "KERNEL PANIC: nmi interrupt, instrution: %lx", frame->instruction_pointer);
    STOP_CPU;
}

__attribute__((interrupt))
void x86_64_idt_breakpoint     (struct idt_interrupt_frame *frame) {
    kprintf(VGA_COLOR_RED, 0, 0, "KERNEL PANIC: breakpoint, instrution: %lx", frame->instruction_pointer);
    STOP_CPU;
}

__attribute__((interrupt))
void x86_64_idt_overflow       (struct idt_interrupt_frame *frame) {
    kprintf(VGA_COLOR_RED, 0, 0, "KERNEL PANIC: overflow, instrution: %lx", frame->instruction_pointer);
    STOP_CPU;
}

__attribute__((interrupt))
void x86_64_idt_gp             (struct idt_interrupt_frame *frame) {
    kprintf(VGA_COLOR_RED, 0, 0, "KERNEL PANIC: General Protection (GP), instrution: %lx", frame->instruction_pointer);
    STOP_CPU;
}

__attribute__((interrupt))
void x86_64_idt_default        (struct idt_interrupt_frame *frame) {
    kprintf(VGA_COLOR_RED, 0, 0, "KERNEL PANIC: default interrupt handler, instrution: %lx", frame->instruction_pointer);
    STOP_CPU;
}
