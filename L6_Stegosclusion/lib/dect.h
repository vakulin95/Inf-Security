#ifndef __DECT_H__
    #define __DECT_H__
#endif

#include "meta.h"
#include "enct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_K_BIT(X, K)   (X & (1 << (K - 1)))

uchar FPHASH[DEF_HASH_LEN];

int decrypt(char *key);
int fhash(char *key);
int hem_dist(void);
int init_block_d(size_t x, size_t y);
