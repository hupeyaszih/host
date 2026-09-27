/**
* @file   : kernel/kernel.h
* @brief  : kernel main
* @details: This module is the main entry point and manager of the kernel
*/

#ifndef KERNEL_H
#define KERNEL_H

void kernel_main(void); ///< @brief The entry point of the kernel. Bootloader calls this. @details Function's address is 0x8200, Note: check the linker.ld for the most accurate information.

#endif
