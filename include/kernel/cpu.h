/**
* @file   : kernel/cpu.h
* @brief  : Arch independent codes about cpu
* @details: This module provides structures and functions etc. independently from the architecture
*/

#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

void cpu_get_cpu_brand(char *brand_string);
void cpu_stop_cpu();

#include <cpu.h>

#endif
