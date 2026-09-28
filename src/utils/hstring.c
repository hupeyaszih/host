#include "utils/hstring.h"

#include <stdint.h>
#include <stddef.h>

void hstring_int_to_string(char *buffer, uint64_t buffer_len, const char *prefix, uint32_t prefix_len, int64_t num, uint32_t base) {
    if(!buffer || buffer_len == 0) return;
    if (base < 2 || base > 36)     goto exit;
    if (prefix_len >= buffer_len)  goto exit;
    uint64_t pos = 0;
    if (prefix && prefix_len > 0) {
        for (uint32_t i = 0; i < prefix_len; ++i) {
            buffer[pos++] = prefix[i];
        }
    }

    uint64_t abs_num;
    if (num < 0) {
        if(buffer_len <= pos) goto exit;
        buffer[pos++] = '-';
        abs_num = (uint64_t) (-(num+1))+1; // I preferred this way to handle the situation (num=INT64_MIN) to reduce branch
    } else {
        abs_num = (uint64_t)  num;
    }

    uint64_t digits_start = pos;
    static const char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    do {
        if(buffer_len <= pos) goto exit;
        buffer[pos++] = alphabet[abs_num % base];
        abs_num /= base;
    } while (abs_num > 0);

    if(buffer_len <= pos) goto exit;
    buffer[pos] = '\0';

    uint64_t digits_end = pos - 1;
    while (digits_start < digits_end) {
        char temp            = buffer[digits_start];
        buffer[digits_start] = buffer[digits_end];
        buffer[digits_end]   = temp;
        ++digits_start;
        --digits_end;
    }

    return;
exit:
    buffer[0] = '\0';
    return;
}

uint32_t hstring_strlen(const char *restrict str) {
    if(!str) return 0;
    uint32_t len = 0;
    while(str+len && str[len] != '\0') {
        ++len;
    }
    return len;
}
