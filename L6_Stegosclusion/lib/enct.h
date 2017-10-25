#ifndef __ENCT_H__
    #define __ENCT_H__
#endif

#include "meta.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define ON_K_BIT(X, K)      (X |= (1 << (K - 1)))
#define OFF_K_BIT(X, K)     (X &= (~(1 << (K - 1))))

#ifdef __LSB__
    #define HASH(key)           lsb(key)
#endif

#ifdef __KDB__
    #define HASH(key)           kdb(key)
#endif

void encrypt(char *key);
float pool(size_t I, size_t J);
void pHash(void);
void dct(float **DCTMatrix, float **Matrix, int N, int M);
void lsb(char *key);
int kdb(char *key);
void def_key(int nofpix);
int init_block(size_t x, size_t y);
int clean_block(void);
int setall(void);
void print_bits(uchar x);
