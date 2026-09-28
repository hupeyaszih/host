/**
* @file   : arch/x86_64/idt.h
* @brief  : x86_64 dependent codes about Interrupt Descriptor Table (IDT)
* @details: This module provides structures and functions etc. ,which depend on the x86_64, for the IDT
*/

#ifndef ARCH_IDT_H
#define ARCH_IDT_H

#include <stdint.h>
struct kernel_context;
struct idt_interrupt_frame;

void x86_64_idt_divide_error   (struct idt_interrupt_frame *frame); ///< @details Type:Fault, Name: Divide Error
void x86_64_idt_debug_exception(struct idt_interrupt_frame *frame); ///< @details Type:Trap, Name: Debug Exception 
void x86_64_idt_nmi_interrupt  (struct idt_interrupt_frame *frame); ///< @details Type:Interrupt, Name: NMI Interrupt 
void x86_64_idt_breakpoint     (struct idt_interrupt_frame *frame); ///< @details Type:Trap, Name: Breakpoint 
void x86_64_idt_overflow       (struct idt_interrupt_frame *frame); ///< @details Type:Trap, Name: Overflow 
void x86_64_idt_default        (struct idt_interrupt_frame *frame); ///< @brief Default
void x86_64_idt_gp             (struct idt_interrupt_frame *frame); ///< @details Type: Fault, Name: General Protection (GP)

#endif
