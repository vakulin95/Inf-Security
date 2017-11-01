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

#define DEF_IM_WIDTH        512
#define DEF_IM_HEIGHT       DEF_IM_WIDTH // 512
#define DEF_IM_BITD         8
#define DEF_IM_NOFC         3

#define DEF_BL_SIZE         64
#define DEF_PHB1_SIZE       32
#define DEF_PHB2_SIZE       8
#define DEF_HASH_LEN        (DEF_PHB2_SIZE * DEF_PHB2_SIZE)
#define DEF_NOF_BL          (DEF_IM_WIDTH / DEF_BL_SIZE)

#define DEF_KDB_SIG         1
#define DEF_KDB_LDA         0.3

#define R(X)                (X[0])
#define G(X)                (X[1])
#define B(X)                (X[2])

#define DEF_K2_LSB          "J01P$X.>KFE5CQ@$3A+HP%C?W+5S6@GH/',/HS,;)';/NHO>+E7$7NF;8Q;>33U2"
#define DEF_K2_LEN_LSB      DEF_HASH_LEN
#define DEF_MAX_HEM_LSB     3

#define DEF_K2_KDB          "P4QJ%C4UBAU-N&9GJ:+HB:+AOOIQ'UGWVI4B.V4+9,%,5PI&<;UU39X$;QUOQXQ@"\
                            "JCHH.++%<%XABXO:$:CI;W'42$-P@OX<45J2-3;CB-C2'&%JU2C$+:5H;2N.'OH,"
#define DEF_K2_LEN_KDB      DEF_HASH_LEN * 2
#define DEF_MAX_HEM_KDB     8

#ifdef __LSB__
    #define DEF_K2          DEF_K2_LSB
    #define DEF_MAX_HEM     DEF_MAX_HEM_LSB
#endif

#ifdef __KDB__
    #define DEF_K2          DEF_K2_KDB
    #define DEF_MAX_HEM     DEF_MAX_HEM_KDB
#endif

#define DEF_ADD             33

typedef unsigned char uchar;

uchar IM[DEF_IM_WIDTH][DEF_IM_HEIGHT][DEF_IM_NOFC];
uchar BLOCK[DEF_BL_SIZE][DEF_BL_SIZE][DEF_IM_NOFC];
uchar PHASH[DEF_HASH_LEN];
