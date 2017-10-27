#ifndef __PNGIO_H__
    #define __PNGIO_H__
#endif

#include "meta.h"

#include <stdlib.h>
#include <png.h>

int load_png(char *filename);
int write_png(char *filename);
