#include "kernel/kernel.h"
void kernel_entry(void) {kernel_main();}
#include "kernel/vga.h"



void kernel_main(void) {
    vga_clear_screen();

    vga_print_string("HUPEYASZIH", 0x0A, VGA_COLUMNS/2, VGA_ROWS/2-3);
    vga_print_string("Designed by Poyraz BAKIRTAS", 0x0A, VGA_COLUMNS/2, VGA_ROWS/2-1);
    vga_print_string("-HOST-", 0x0A, VGA_COLUMNS/2, VGA_ROWS/2+1);
}
