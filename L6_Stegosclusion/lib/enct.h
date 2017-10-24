#ifndef __ENCT_H__
    #define __ENCT_H__
#endif

#include "meta.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void encrypt(void);
void init_block(size_t x, size_t y);
void clean_block(void);
float pool(size_t I, size_t J);
void pHash(void);
void dct(float **DCTMatrix, float **Matrix, int N, int M);
void lsb(char *key);
void def_key(void);
