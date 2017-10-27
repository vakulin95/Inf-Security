#ifndef __DECT_H__
    #define __DECT_H__
#endif

#include "meta.h"
#include "enct.h"

#define CHECK_K_BIT(X, K)   (X & (1 << (K - 1)))

#ifdef __LSB__
    #define FHASH(key)           fhash_lsb(key)
#endif

#ifdef __KDB__
    #define FHASH(key)           fhash_kdb(key)
#endif

uchar FPHASH[DEF_HASH_LEN];

int decrypt(char *key);
int fhash_lsb(char *key);
int fhash_kdb(char *key);
int hem_dist(void);
int mark_bl(size_t u, size_t v);
