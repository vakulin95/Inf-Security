#ifndef __RAND_GEN_H__
#define __RAND_GEN_H__

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define DEF_R0          0.51111111
#define DEF_A           8
#define DEF_B           5
#define DEF_ARR_LEN     1200
#define DEF_NOP         5

double R[DEF_ARR_LEN];
int IND;
int RIND;

void rand_gen(void);
int check_mas(double val, int max_ind);
void print_res(int list_val);

#endif
