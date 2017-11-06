#ifndef __ENCT_H__
    #define __ENCT_H__
#endif

#include "meta.h"

#define ON_K_BIT(X, K)      (X |= (1 << (K - 1)))
#define OFF_K_BIT(X, K)     (X &= (~(1 << (K - 1))))

int mcompress(void);
int encrypt(void);
int init_block(size_t x, size_t y);
int set_block(size_t x, size_t y);
int clean_block(void);
void print_bits(uchar x);
