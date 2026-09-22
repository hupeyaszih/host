#include "kernel/kernel.h"
void kernel_entry(void) {kernel_main();}
#include "kernel/vga.h"

#include "arch/x86_64/x86_64_cpu.h"

void kernel_main(void) {
    vga_clear_screen();


    vga_print_string("HUPEYASZIH", VGA_COLOR_CYAN, VGA_COLUMNS/2, VGA_ROWS/2-3);
    vga_print_string("Designed by Poyraz BAKIRTAS", VGA_COLOR_LIGHT_GRAY, VGA_COLUMNS/2, VGA_ROWS/2-1);
    vga_print_string("-HOST-", VGA_COLOR_LIGHT_RED, VGA_COLUMNS/2, VGA_ROWS/2+1);


    char cpu_str[49];
    x86_64_get_cpu_brand(cpu_str);
    vga_print_string(cpu_str, VGA_COLOR_GREEN, VGA_COLUMNS/2, VGA_ROWS/2+3);
}
