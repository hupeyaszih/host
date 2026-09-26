#include "utils/hstring.h"

void hstring_int_to_string(char *buffer, uint64_t buffer_len, int64_t num) {
    if (buffer_len == 0) return;
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    uint64_t i = 0;
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num > 0 && i < buffer_len - 1) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    if (is_negative && i < buffer_len - 1) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    uint64_t start = 0;
    uint64_t end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}
