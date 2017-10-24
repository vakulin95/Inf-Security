#ifndef __DECT_H__
    #define __DECT_H__
#endif

#include "meta.h"
#include "enct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uchar FPHASH[DEF_HASH_LEN];

int decrypt(char *key);
int fhash(char *key);
