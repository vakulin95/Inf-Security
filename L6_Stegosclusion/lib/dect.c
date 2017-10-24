#include "dect.h"

int decrypt(char *key)
{
    size_t i, j, u, v;

    for(u = 0; u < DEF_IM_HEIGHT; u += DEF_BL_SIZE)
    {
        for(v = 0; v < DEF_IM_WIDTH; v += DEF_BL_SIZE)
        {
            memset(PHASH, 0, DEF_HASH_LEN);
            memset(FPHASH, 0, DEF_HASH_LEN);
            clean_block();

            init_block(u, v);
            pHash();

            fhash(key);

            printf("%d\n", hem_dist());
            getchar();
        }
    }


    return 0;
}

int fhash(char *key)
{
    size_t i, j, k, p;

    for(k = 0, p = 0; k < DEF_K2_LEN && p < DEF_HASH_LEN; k += 2, p += 2)
    {
        i = (size_t)key[k] - DEF_ADD;
        j = (size_t)key[k + 1] - DEF_ADD;

        CHECK_K_BIT(B(BLOCK[i][j]), 1) ? (FPHASH[p] = 1) : (FPHASH[p] = 0);
        CHECK_K_BIT(B(BLOCK[i][j]), 2) ? (FPHASH[p + 1] = 1) : (FPHASH[p + 1] = 0);
    }

    // for(i = 0; i < DEF_HASH_LEN; i++)
    // {
    //     printf("%d", FPHASH[i]);
    // }
    // getchar();

    return 0;
}

int hem_dist(void)
{
    size_t i;
    int Y;

    Y = 0;
    for(i = 0; i < DEF_HASH_LEN; i++)
    {
        if(PHASH[i] != FPHASH[i])
        {
            Y++;
        }
    }

    return Y;
}
