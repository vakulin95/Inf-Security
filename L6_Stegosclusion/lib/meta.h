#ifndef __META_H__
    #define __META_H__
#endif

#define __KDB__

#define DEF_PATH            "files/"
#define DEF_PATH_STR_LEN    125

#define DEF_IM_WIDTH        512
#define DEF_IM_HEIGHT       DEF_IM_WIDTH // 512
#define DEF_IM_QUALITY      100
#define DEF_IM_DIM          3

#define DEF_BL_SIZE         64
#define DEF_PHB1_SIZE       32
#define DEF_PHB2_SIZE       8
#define DEF_HASH_LEN        (DEF_PHB2_SIZE * DEF_PHB2_SIZE)
#define DEF_NOF_BL          (DEF_IM_WIDTH / DEF_BL_SIZE)

#define R(X)                (X[0])
#define G(X)                (X[1])
#define B(X)                (X[2])

#define DEF_K2_LSB          "J;34,[B;&\\K1,$'94?0KG3(J!-%AH#=N<-5*$\":CR(NMT,46NAGF=Y@Q>:T\"MYEU"
#define DEF_K2_LEN_LSB      64

#define DEF_K2_KDB          "ROKV\\GD]!<S<VUS.=,V\"@_0X_N5F+0TD<I`2-C1(S[]X[*P?A7(]J[MC@@9G\"1CS"\
                            "?Q1++!.`3MN(YZ(D<7#*+=12P)Y<*1OKO7BODB!KA(!V2^(\"A)X3\\\"H=3R:$6@0M"
#define DEF_K2_LEN_KDB      128

#ifdef __LSB__
    #define DEF_K2          DEF_K2_LSB
#endif

#ifdef __KDB__
    #define DEF_K2          DEF_K2_KDB
#endif

#define DEF_ADD             33

typedef unsigned char uchar;

uchar IM[DEF_IM_WIDTH][DEF_IM_HEIGHT][DEF_IM_DIM];
uchar BLOCK[DEF_BL_SIZE][DEF_BL_SIZE][DEF_IM_DIM];
uchar PHASH[DEF_HASH_LEN];
