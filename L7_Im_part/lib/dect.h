#ifndef __DECT_H__
    #define __DECT_H__
#endif

#include "meta.h"
#include "enct.h"

int decrypt(void);
int unfbl(void);
int flsb(int key);
int mdecompress(void);
int write_decbl(size_t x, size_t y);
