#ifndef __RAND_GEN_H__
#define __RAND_GEN_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <gmp.h>

#define DEF_STR_LEN         255
#define DEF_SIFR_LEN        46
#define DEF_BLOCK_LEN       ((DEF_SIFR_LEN - 1) / 3)

typedef unsigned long long int  int64;

//---------------------------------------------------------------------------//

char rsa_etext[DEF_STR_LEN];
char rsa_dtext[DEF_STR_LEN];
char rsa_shifro_text[DEF_SIFR_LEN];
char rsa_block[DEF_STR_LEN];

//---------------------------------------------------------------------------//

int64 Eiler(int64 n);
int64 Find_d(int64 fi, int64 e);
void Enc(int64 n, int64 e);
void Dec(int64 n, int64 d);
void ins_null(void);

#endif
