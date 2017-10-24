#include "dect.h"

int decrypt(char *key)
{
    size_t i, j, u, v;

    for(u = 0; u < DEF_IM_HEIGHT; u += DEF_BL_SIZE)
    {
        for(v = 0; v < DEF_IM_WIDTH; v += DEF_BL_SIZE)
        {
            memset(PHASH, 0, DEF_HASH_LEN);
            clean_block();

            init_block(u, v);
            pHash();

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

        
    }

    return 0;
}
