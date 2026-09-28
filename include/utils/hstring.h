/**
* @file   : utils/hstring.h
* @brief  : utils/hstring.h aims to help to the kernel by processing strings to reduce kernel complexity.
* @details: This module's work is to process strings without any dependency.
*/

#ifndef HSTRING_H
#define HSTRING_H

#include <stdint.h>

void hstring_int_to_string(char *buffer, uint64_t buffer_len, const char *prefix, uint32_t prefix_len, int64_t num, uint32_t base);
uint32_t hstring_strlen(const char *restrict str);

#endif
