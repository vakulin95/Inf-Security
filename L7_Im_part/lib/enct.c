#include "enct.h"

void print_bits(uchar x)
{
    size_t i;
    int len = sizeof(uchar) * 8;
    int bit_str[len];

    for(i = 0; i < len; i++)
    {
        bit_str[i] = x & 0x01;
        x >>= 1;
    }

    for(i = 1; i <= len; i++)
    {
        printf("%d", bit_str[len - i]);
    }
    printf("\n");
}
