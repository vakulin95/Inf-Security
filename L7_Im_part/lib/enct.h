#ifndef __ENCT_H__
    #define __ENCT_H__
#endif

#include "meta.h"

#define ON_K_BIT(X, K)      (X |= (1 << (K - 1)))
#define OFF_K_BIT(X, K)     (X &= (~(1 << (K - 1))))

void print_bits(uchar x);
