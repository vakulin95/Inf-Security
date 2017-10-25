#include "dect.h"

float decrypt(char *key)
{
    size_t i, j, u, v;
    int hem;
    float avhem;

    avhem = 0;
    for(u = 0; u < DEF_IM_HEIGHT; u += DEF_BL_SIZE)
    {
        for(v = 0; v < DEF_IM_WIDTH; v += DEF_BL_SIZE)
        {
            memset(PHASH, 0, DEF_HASH_LEN);
            memset(FPHASH, 0, DEF_HASH_LEN);
            clean_block();

            init_block(u, v);
            pHash();

            FHASH(key);

            hem = hem_dist();
            // printf("%d\n", hem);
            avhem += hem;
        }
    }
    avhem /= pow(DEF_NOF_BL, 2);

    printf("decrypt finished\n");
    return avhem;
}

int fhash_lsb(char *key)
{
    size_t i, j, k, p;

    for(k = 0, p = 0; k < DEF_K2_LEN_LSB && p < DEF_HASH_LEN; k += 2, p += 2)
    {
        i = (size_t)key[k] - DEF_ADD;
        j = (size_t)key[k + 1] - DEF_ADD;

        CHECK_K_BIT(B(BLOCK[i][j]), 2) ? (FPHASH[p] = 1) : (FPHASH[p] = 0);
        CHECK_K_BIT(B(BLOCK[i][j]), 1) ? (FPHASH[p + 1] = 1) : (FPHASH[p + 1] = 0);
    }

    return 0;
}

int fhash_kdb(char *key)
{
    size_t i, j, k, p, ia, sig;
    float avB;

    sig = 8;
    for(k = 0, p = 0; k < DEF_K2_LEN_KDB && p < DEF_HASH_LEN; k += 2, p++)
    {
        i = (size_t)key[k] - DEF_ADD;
        j = (size_t)key[k + 1] - DEF_ADD;

        avB = 0;
        ((int)(i - sig) > 0) ? (ia = i - sig) : (ia = 0);
        for(; (ia <= i + sig) && (ia < DEF_BL_SIZE); ia++)
        {
            avB += (float)B(BLOCK[ia][j]);
        }

        ((int)(j - sig) > 0) ? (ia = j - sig) : (ia = 0);
        for(; (ia <= j + sig) && (ia < DEF_BL_SIZE); ia++)
        {
            avB += (float)B(BLOCK[i][ia]);
        }
        avB /= (float)(4 * sig);

        if((float)B(BLOCK[i][j]) >= avB)
        {
            FPHASH[p] = 1;
        }
        else
        {
            FPHASH[p] = 0;
        }
    }

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