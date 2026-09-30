/**
* @file   : kernel/idt.h
* @brief  : Interrupt Descriptor Table (IDT) configuration and setup functions.
* @details: This module provides structures and functions to initialize and manage
*           the IDT table and handle CPU exceptions.
*/

#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H

#include <stdint.h>

extern const uint32_t IDT_TABLE_ENTRY_COUNT;
extern const uint32_t IDT_TABLE_MAX_ENTRY_COUNT;


/**
 * @brief IDT table's entry for x86 64
 * @details x86_64 IDT table's entry. Its size is 16 bytes.
*/
struct idt_entry {
    uint16_t offset_1;
    uint16_t selector;       ///< @brief code segment selector
    uint8_t ist;             ///< @brief bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t type_attributes; ///< @brief gate type
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t reserved;
} __attribute__((packed));

/**
 * @brief IDT table pointer
*/
struct idt_ptr {
    uint16_t limit; ///< @brief Length of the IDT table in bytes.
    uint64_t base;  ///< @brief Memory address of the IDT table.
} __attribute__((packed));

struct idt_interrupt_frame {
    uint64_t instruction_pointer;
    uint64_t code_segment;
    uint64_t flags;
    uint64_t stack_pointer;
    uint64_t stack_segment;
} __attribute__((packed));

/**
 * @brief Initializes the IDT table, loads the entries
*/
void idt_init_idt(void);

/**
 * @brief Tells where the IDT table to the CPU.
 * @details Tells cpu where the IDT table, and doesn't make any change in IDT table. The only task of this function is to tell CPU where the table is.
 * @pre @ref idt_init_idt(struct idt_table64 *table)
*/
void idt_load_idt(void);

#include <idt.h>

#endif
