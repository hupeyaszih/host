#ifndef VGA_H
#define VGA_H

#define VGA_COLUMNS 80
#define VGA_ROWS 25

void vga_clear_screen();
void vga_print_char(char ch, unsigned int color, int x, int y);
void vga_print_string(char *string, unsigned int color, int x, int y);

#endif
