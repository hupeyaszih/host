#include "kernel/kernel.h"
#include "utils/hstring.h"
#include <stdint.h>
void kernel_entry(void) {kernel_main();}
#include "kernel/vga.h"

#include <kernel/cpu.h>

struct pmm_e820_entry {
    uint64_t base_address;
    uint64_t length;
    uint32_t type;
    uint32_t extended_attributes;
} __attribute__((packed));

void kernel_main(void) {
    vga_clear_screen();


    vga_print_string("HUPEYASZIH", VGA_COLOR_CYAN, VGA_COLUMNS/2, VGA_ROWS/2-12);
    vga_print_string("Designed by Poyraz BAKIRTAS", VGA_COLOR_LIGHT_GRAY, VGA_COLUMNS/2, VGA_ROWS/2-10);
    vga_print_string("-HOST-", VGA_COLOR_LIGHT_RED, VGA_COLUMNS/2, VGA_ROWS/2-8);


    char cpu_str[49];
    cpu_get_cpu_brand(cpu_str);
    vga_print_string(cpu_str, VGA_COLOR_GREEN, VGA_COLUMNS/2, VGA_ROWS/2-6);

    //

    uint32_t *entry_count_ptr = (uint32_t *) 0x4FC;
    uint32_t entry_count = *entry_count_ptr;

    struct pmm_e820_entry *mmap = (struct pmm_e820_entry *) 0x500;
    uint32_t print_row = VGA_ROWS/2-4;
    uint32_t total_ram = 0;        //KB
    uint32_t total_usable_ram = 0; //KB


    ++print_row;
    vga_print_string("-RAM-", VGA_COLOR_MAGENTA, VGA_COLUMNS/2, print_row);
    ++print_row;

    for(uint32_t i = 0;i < entry_count; ++i) {
        uint64_t len  = mmap[i].length / (1024); // KB
        total_ram += len;
        if(mmap[i].type != 1) continue; // not usable RAM
        //uint64_t base = mmap[i].base_address;
        total_usable_ram += len;
    }

    char total_len_str[20];
    ++print_row;
    vga_print_string("TOTAL RAM (MB)", VGA_COLOR_LIGHT_GRAY, VGA_COLUMNS/2, print_row);
    ++print_row;
    hstring_int_to_string(total_len_str, 20, total_ram/1024);
    vga_print_string(total_len_str, VGA_COLOR_LIGHT_GREEN, VGA_COLUMNS/2, print_row);
    ++print_row;

    vga_print_string("TOTAL USABLE RAM (MB)", VGA_COLOR_LIGHT_GRAY, VGA_COLUMNS/2, print_row);
    ++print_row;
    hstring_int_to_string(total_len_str, 20, total_usable_ram/1024);
    vga_print_string(total_len_str, VGA_COLOR_LIGHT_GREEN, VGA_COLUMNS/2, print_row);
    ++print_row;

}
