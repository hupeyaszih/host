#include "kernel/vga.h"

void vga_clear_screen() {
    for(int y = 0;y < VGA_ROWS; ++y) {
        for(int x = 0;x < VGA_COLUMNS; ++x) {
            vga_print_char(' ', 0x00, x, y);
        }
    }
}

void vga_print_char(char ch, unsigned int color, int x, int y) {
    volatile unsigned short *vga = (unsigned short *)0xB8000;
    int index = y*VGA_COLUMNS + x;
    vga[index] = (color << 8) | ch;
}

void vga_print_string(char *string, unsigned int color, int x, int y) {
    int len = 0;
    while (string[len] != '\0') {
        len++;
    }

    int x_offset = x - len / 2;
    for (int i = 0; i < len; ++i) {
        if (x_offset + i >= 0 && x_offset + i < VGA_COLUMNS) {
            vga_print_char(string[i], color, x_offset + i, y);
        }
    }
}
