#ifndef __PNGIO_H__
    #define __PNGIO_H__
#endif

#include "meta.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>

int load_png(char *filename);
int write_png(char *filename);
