#include "rand_gen.h"

void rand_gen(void)
{
    int i, temp_i;

    R[0] = DEF_R0;
    for(i = 0; i < DEF_ARR_LEN - 1; i++)
    {
        temp_i = i + 1;

        R[temp_i] = (int)(pow(R[i], 2) * pow(10, DEF_A)) * pow(10, -1 * DEF_B) \
        - (int)(pow(R[i], 2) * pow(10, DEF_A - DEF_B));

        if(check_mas(R[temp_i], temp_i))
        {
            IND = temp_i;
            goto ret;
        }
    }

ret:
    return;
}

int check_mas(double val, int max_ind)
{
    int i;

    for(RIND = 0, i = 0; i < max_ind; i++)
    {
        if(val == R[i])
        {
            RIND = i;
            goto ret;
        }
    }

ret:
    return RIND;
}

void print_res(int list_val)
{
    int i, j, k, ind;

    printf("A\t\t%d\nB\t\t%d\nR[0]\t\t%f\nNum of val\t%d\nRep R[%d]\t%f%d\n\n", \
    DEF_A, DEF_B, R[0], IND - 1, RIND, R[RIND]);

    if(list_val)
    {
        printf("List of generted values:\n");

        for(i = 0; i < (int)(DEF_ARR_LEN / DEF_NOP); i++)
        {
            for(j = 0, ind = i; j < DEF_NOP; j++, ind += DEF_NOP)
            {
                if(ind == IND)
                {
                    goto ret;
                }
                printf("R[%3d]: %f;   ", ind, R[ind]);
            }
            printf("\n");
        }
    }

ret:
    printf("\n");
    return;
}
