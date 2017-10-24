#ifndef __JPGIO_H__
    #define __JPGIO_H__
#endif

#include "meta.h"

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <setjmp.h>

int load_jpg(char *filename);
void write_jpg(char *filename);
