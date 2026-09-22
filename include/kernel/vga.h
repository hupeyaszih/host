#ifndef VGA_H
#define VGA_H

#define VGA_COLUMNS 80
#define VGA_ROWS 25

#define VGA_COLOR_BLACK   0x00
#define VGA_COLOR_BLUE    0x01
#define VGA_COLOR_GREEN   0x02
#define VGA_COLOR_CYAN    0x03
#define VGA_COLOR_RED     0x04
#define VGA_COLOR_MAGENTA 0x05
#define VGA_COLOR_BROWN   0x06

#define VGA_COLOR_LIGHT_GRAY      0x07
#define VGA_COLOR_DARK_GRAY       0x08
#define VGA_COLOR_LIGHT_BLUE      0x09
#define VGA_COLOR_LIGHT_GREEN     0x0A
#define VGA_COLOR_LIGHT_CYAN      0x0B
#define VGA_COLOR_LIGHT_RED       0x0C
#define VGA_COLOR_LIGHT_MAGENTA   0x0D
#define VGA_COLOR_LIGHT_YELLOW    0x0E
#define VGA_COLOR_LIGHT_WHITE     0x0F

void vga_clear_screen();
void vga_print_char(char ch, unsigned int color, int x, int y);
void vga_print_string(char *string, unsigned int color, int x, int y);

#endif
