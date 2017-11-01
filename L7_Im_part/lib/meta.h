#ifndef __META_H__
    #define __META_H__
#endif

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define DEF_PATH            "files/"
#define DEF_PATH_STR_LEN    125

#define DEF_INFILE          "in.png"
#define DEF_ENCFILE         "enc_out.png"
#define DEF_DECFILE         "dec_out.png"

#define DEF_IM_WIDTH        512
#define DEF_IM_HEIGHT       DEF_IM_WIDTH // 512
#define DEF_IM_BITD         8
#define DEF_IM_NOFC         3

#define R(X)                (X[0])
#define G(X)                (X[1])
#define B(X)                (X[2])

typedef unsigned char uchar;

uchar IM[DEF_IM_WIDTH][DEF_IM_HEIGHT][DEF_IM_NOFC];
