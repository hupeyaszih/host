/**
* @file   : kernel/idt.h
* @brief  : Interrupt Descriptor Table (IDT) configuration and setup functions.
* @details: This module provides structures and functions to initialize and manage
*           the IDT table and handle CPU exceptions.
*/

#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H

extern const int IDT_TABLE_ADDRESS;

#include <idt.h>

#endif
