#include "utils/klibc.h"
#include "utils/hstring.h"
#include "globals.h"
#include "kernel/vga.h"
#include <stdarg.h>

void kprintf(uint8_t color, uint8_t x, uint8_t y, const char *format, ...) {
    va_list arguments;
    va_start(arguments, format);

    uint8_t current_color = color;
    uint8_t current_x     = x;
    uint8_t current_y     = y;
    for (uint32_t i = 0; format[i] != '\0'; ++i) {
        if(format[i] == '%') {
            i++;

            switch (format[i]) {
                case 'd': {
                    int num = (int) va_arg(arguments, int);
                    char buffer[21];
                    hstring_int_to_string(buffer, 21, GLOBALS_PREFIX_DEC, GLOBALS_PREFIX_DEC_LEN, num, GLOBALS_BASE_DEC);
                    vga_print_string(buffer, current_color, current_x, current_y, false);

                    int32_t len = hstring_strlen(buffer);
                    current_x += len - 1;
                    break;
                }case 'l': {
                    if(format[i+1] == 'd') {
                        int num = (uint64_t) va_arg(arguments, uint64_t);
                        char buffer[21];
                        hstring_int_to_string(buffer, 21, GLOBALS_PREFIX_DEC, GLOBALS_PREFIX_DEC_LEN, num, GLOBALS_BASE_DEC);
                        vga_print_string(buffer, current_color, current_x, current_y, false);

                        int32_t len = hstring_strlen(buffer);
                        current_x += len - 1;
                    }else if(format[i+1] == 'x') {
                        int num = (uint64_t) va_arg(arguments, uint64_t);
                        char buffer[21];
                        hstring_int_to_string(buffer, 21, GLOBALS_PREFIX_HEX, GLOBALS_PREFIX_HEX_LEN, num, GLOBALS_BASE_HEX);
                        vga_print_string(buffer, current_color, current_x, current_y, false);

                        int32_t len = hstring_strlen(buffer);
                        current_x += len - 1;
                    }
                    ++i;
                    break;
                }case 'c': {
                    char ch = (char) va_arg(arguments, int);
                    vga_print_char(ch, current_color, current_x, current_y);
                    break;
                }case 's': {
                    char *str = (char *) va_arg(arguments, char *);
                    vga_print_string(str, current_color, current_x, current_y, false);

                    int32_t len = hstring_strlen(str);
                    current_x += len - 1;
                    break;
                }case 'h': {
                    if(format[i+1] == 's' && format[i+2] == 'c') {
                        current_color = (uint8_t) va_arg(arguments, int);
                    }else if(format[i+1] == 'r' && format[i+2] == 'c') {
                        current_color = color;
                    }else if(format[i+1] == 's' && format[i+2] == 'x') {
                        uint8_t new_x = (uint8_t) va_arg(arguments, int);
                        current_x = new_x;
                    }else if(format[i+1] == 'r' && format[i+2] == 'x') {
                        current_x = x;
                    }else if(format[i+1] == 's' && format[i+2] == 'y') {
                        uint8_t new_y = (uint8_t) va_arg(arguments, int);
                        current_y = new_y;
                    }else if(format[i+1] == 'r' && format[i+2] == 'y') {
                        current_y = y;
                    }
                    i += 2;
                    continue;
                }default: {
                    vga_print_char('%', current_color, current_x, current_y);
                    ++current_x;
                    vga_print_char(format[i], current_color, current_x, current_y);
                    break;
                }
            }

        }else if(format[i] == '\n') {
            ++current_y;
            current_x = x;
            continue;
        }else {
            vga_print_char(format[i], current_color, current_x, current_y);
        }
        ++current_x;
    }
}
