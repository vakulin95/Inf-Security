#ifndef __FEISTEL_H__
    #define __FEISTEL_H__
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define DEF_ROUNDS              10
#define DEF_MES_LEN             8
#define DEF_NUM_OF_PARTS        4

#define GET_BIT(X, NUM)         (( (X) & ( (int64)(1) << (NUM) )) >> (NUM) )
#define GET_PART(X, NUM)        ((int16)((X) >> (NUM) * 16))
#define SET_PART(X, PART, NUM)  (((int64)(PART) << 16 * (NUM)) | (int64)(X))
#define MOOVE_R_B(X, Y)         (( (X) >> (Y) ) | ( (X) << ( (Y) & (int32)(65535) )))
#define MOOVE_L_B(X, Y)         (( (X) << (Y) ) | ( (X) >> ( (Y) & (int32)(65535) )))

//--------------------------------------------------------------------------------//

typedef unsigned short int      int16;
typedef unsigned int            int32;
typedef unsigned long long int  int64;

int16 KEYS[DEF_ROUNDS];

//--------------------------------------------------------------------------------//

int64 fl_hide(int64 message);
int64 fl_show(int64 message);
int64 conv_str(unsigned char str[DEF_MES_LEN]);
void conv_int(int64 X, unsigned char **str);
void cr_keys(void);
int64 join_parts(int16 *part);
int16 gen_func(int16 *part, int16 key);