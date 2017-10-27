#ifndef __META_H__
    #define __META_H__
#endif

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define __KDB__

#define DEF_PATH            "files/"
#define DEF_PATH_STR_LEN    125

#define DEF_INFILE          "in.png"
#define DEF_ENCFILE         "enc_out.png"
#define DEF_DECFILE         "dec_out.png"
#define DEF_MAX_HEM         20

#define DEF_IM_WIDTH        512
#define DEF_IM_HEIGHT       DEF_IM_WIDTH // 512
#define DEF_IM_BITD         8
#define DEF_IM_NOFC         3

#define DEF_BL_SIZE         64
#define DEF_PHB1_SIZE       32
#define DEF_PHB2_SIZE       8
#define DEF_HASH_LEN        (DEF_PHB2_SIZE * DEF_PHB2_SIZE)
#define DEF_NOF_BL          (DEF_IM_WIDTH / DEF_BL_SIZE)

#define DEF_KDB_SIG         3
#define DEF_KDB_LDA         0.4

#define R(X)                (X[0])
#define G(X)                (X[1])
#define B(X)                (X[2])

#define DEF_K2_LSB          "J01P$X.>KFE5CQ@$3A+HP%C?W+5S6@GH/',/HS,;)';/NHO>+E7$7NF;8Q;>33U2"
#define DEF_K2_LEN_LSB      DEF_HASH_LEN

#define DEF_K2_KDB          "F()SQXW+FBUE)X5U8%6D9+)1.W4S'L)91&HM@6>V<6VP$$?=-20JKAK,Y*'8K$9)"\
                            "EO/:OMB=J6+FHS768.;B.T@[>LP:4I;N)AX>O@V7/-B0DGTT3=N*XMMVQ8J>T+ZV"
#define DEF_K2_LEN_KDB      DEF_HASH_LEN * 2

#ifdef __LSB__
    #define DEF_K2          DEF_K2_LSB
#endif

#ifdef __KDB__
    #define DEF_K2          DEF_K2_KDB
#endif

#define DEF_ADD             33

typedef unsigned char uchar;

uchar IM[DEF_IM_WIDTH][DEF_IM_HEIGHT][DEF_IM_NOFC];
uchar BLOCK[DEF_BL_SIZE][DEF_BL_SIZE][DEF_IM_NOFC];
uchar PHASH[DEF_HASH_LEN];
