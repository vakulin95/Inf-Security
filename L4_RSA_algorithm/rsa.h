#ifndef __RAND_GEN_H__
#define __RAND_GEN_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <gmp.h>

#define DEF_STR_LEN         46
#define DEF_BLOCK_LEN       (DEF_STR_LEN / 3)

typedef unsigned long long int  int64;

//---------------------------------------------------------------------------//

char rsa_etext[255];
char rsa_dtext[255];
char rsa_shifro_text[DEF_STR_LEN];
char rsa_block[DEF_BLOCK_LEN];

//---------------------------------------------------------------------------//

int64 Eiler(int64 n);
int64 Find_d(int64 fi, int64 e);
void Enc(int64 n, int64 e);
void Dec(int64 n, int64 d);
void ull2mpz(mpz_t z, unsigned long long ull);
int64 mpz2ull(mpz_t z);

#endif
