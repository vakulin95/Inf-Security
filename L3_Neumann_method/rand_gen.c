#include "rand_gen.h"

void rand_gen(void)
{
    int i, temp_i, rep_num;

    R[0] = DEF_R0;
    rep_num = 0;
    for(i = 0; i < DEF_ARR_LEN - 1; i++)
    {
        temp_i = i + 1;

        R[temp_i] = (int)(pow(R[i], 2) * pow(10, DEF_A)) * pow(10, -1 * DEF_B) \
        - (int)(pow(R[i], 2) * pow(10, DEF_A - DEF_B));

        if(check_mas(R[temp_i], temp_i))
        {
            //rep_num++;
            IND = temp_i;
            goto ret;
        }

        // if(i > 1 && R[temp_i] == R[1])
        // {
        //     IND = temp_i;
        //     goto ret;
        // }
    }

    IND = DEF_ARR_LEN;
    RIND = -1;

ret:
    //printf("rep_num:\t%d\n", rep_num);
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
    int i, j, ind, str_num;

    printf("A\t\t%d\nB\t\t%d\nR[0]\t\t%f\nNum of val\t%d\n", \
    DEF_A, DEF_B, R[0], IND - 1);

    if(RIND != -1)
    {
        printf("Rep R[%d]\t%f%d\n", RIND, R[RIND]);
    }

    if(list_val)
    {
        printf("\nList of generted values:\n");

        str_num = (int)ceil((float)IND / (float)DEF_NOP);
        for(i = 1; i < str_num; i++)
        {
            for(j = 0, ind = i; j < DEF_NOP; j++, ind += str_num)
            {
                if(ind <= IND)
                {
                    if(ind != RIND && ind != IND)
                    {
                        printf("R[%3d]: %.6f;   ", ind, R[ind]);
                    }
                    else
                    {
                        printf("*R[%3d]: %.6f;   ", ind, R[ind]);
                    }
                }
                else
                {
                    goto ret;
                }
            }
            printf("\n");
        }
    }

ret:
    printf("\n");
    return;
}
