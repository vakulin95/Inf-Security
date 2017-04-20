#ifndef __RAND_GEN_H__
#define __RAND_GEN_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <gmp.h>

#define DEF_STR_LEN         256
#define DEF_NOF_BLOCK       3

typedef unsigned long long int  int64;

//---------------------------------------------------------------------------//

char rsa_ETEXT[DEF_STR_LEN];
char rsa_DTEXT[DEF_STR_LEN];
char rsa_INIT[DEF_STR_LEN];
char rsa_BLOCK[DEF_STR_LEN];

int rsa_Block_len;

int64 rsa_Eil;
int64 rsa_D;

//---------------------------------------------------------------------------//

void rsa_init(char *str, int64 n, int64 e);
void rsa_encode(int64 n, int64 e);
void rsa_decode(int64 n, int64 d);

#endif
