#include <cpuid.h>
#include <stdint.h>

void cpu_get_cpu_brand(char *brand_string) {
    uint32_t *u32_str = (uint32_t *)brand_string;
    
    __get_cpuid(0x80000002, &u32_str[0], &u32_str[1], &u32_str[2], &u32_str[3]);
    __get_cpuid(0x80000003, &u32_str[4], &u32_str[5], &u32_str[6], &u32_str[7]);
    __get_cpuid(0x80000004, &u32_str[8], &u32_str[9], &u32_str[10], &u32_str[11]);
    
    brand_string[48] = '\0';
}
