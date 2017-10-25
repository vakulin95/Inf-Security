#include "enct.h"

void encrypt(char *key)
{
    size_t i, j, u, v;
    u = 0;
    v = 0;

    // for(u = 0; u < DEF_IM_HEIGHT; u += DEF_BL_SIZE)
    // {
    //     for(v = 0; v < DEF_IM_WIDTH; v += DEF_BL_SIZE)
    //     {
            memset(PHASH, 0, DEF_HASH_LEN);
            clean_block();

            init_block(u, v);
            pHash();

            lsb(key);

            for (i = 0; i < DEF_BL_SIZE; i++)
            {
                for(j = 0; j < DEF_BL_SIZE; j++)
                {
                    R(IM2[u + i][v + j]) = R(BLOCK[i][j]);
                    G(IM2[u + i][v + j]) = G(BLOCK[i][j]);
                    B(IM2[u + i][v + j]) = B(BLOCK[i][j]);
                }
            }

    //     }
    // }

    printf("encrypt finished\n");
}

float pool(size_t I, size_t J)
{
    size_t i, j;
    uchar tR, tG, tB;
    uchar R[DEF_IM_DIM];
    int scale;
    float avg;

    tR = 0;
    tG = 0;
    tB = 0;
    scale = DEF_BL_SIZE / DEF_PHB1_SIZE;
    for(i = I; i < I + scale; i++)
    {
        for(j = J; j < J + scale; j++)
        {
            tR += R(BLOCK[i][j]);
            tG += G(BLOCK[i][j]);
            tB += B(BLOCK[i][j]);
        }
    }
    R(R) = tR / scale;
    G(R) = tG / scale;
    B(R) = tB / scale;

    // Приведение к яркостному представлению
    avg = (R(R) + G(R) + B(R)) / DEF_IM_DIM;

    return avg;
}

void pHash(void)
{
    size_t i, j;
    float **PHB_32, **DCT;
    float P, avg;
    int scale;

    PHB_32 = (float**)malloc(sizeof(float*) * DEF_PHB1_SIZE);
    DCT = (float**)malloc(sizeof(float*) * DEF_PHB1_SIZE);

    for(i = 0 ; i < DEF_PHB1_SIZE; i++)
    {
        PHB_32[i] = (float*)malloc(sizeof(float) * DEF_PHB1_SIZE);
        DCT[i] = (float*)malloc(sizeof(float) * DEF_PHB1_SIZE);
    }

    // Масштабирование
    scale = DEF_BL_SIZE / DEF_PHB1_SIZE;
    for(i = 0; i < DEF_PHB1_SIZE; i++)
    {
        for(j = 0; j < DEF_PHB1_SIZE; j++)
        {
            P = pool(i*scale, j*scale);
            PHB_32[i][j] = P;
        }
    }

    dct(DCT, PHB_32, DEF_PHB1_SIZE, DEF_PHB1_SIZE);

    // Вычисление порога
    avg = 0;
    for(i = 0; i < DEF_PHB2_SIZE; i++)
    {
        for(j = 0; j < DEF_PHB2_SIZE; j++)
        {
            // printf("%8.2f ", DCT[i][j]);
            avg += DCT[i][j];
        }
        // printf("\n");
    }
    avg -= DCT[0][0];
    avg /= pow(DEF_PHB2_SIZE, 2);
    // printf("%5.3f\n", avg);

    for(i = 0; i < DEF_PHB2_SIZE; i++)
    {
        for(j = 0; j < DEF_PHB2_SIZE; j++)
        {
            if(DCT[i][j] >= avg)
            {
                PHASH[i * DEF_PHB2_SIZE + j] = 1;
            }
            else
            {
                PHASH[i * DEF_PHB2_SIZE + j] = 0;
            }
        }
    }

    free(PHB_32);
    free(DCT);
}

void dct(float **DCTMatrix, float **Matrix, int N, int M)
{

    int i, j, u, v;

    for (u = 0; u < N; ++u)
    {
        for (v = 0; v < M; ++v)
        {
            DCTMatrix[u][v] = 0;
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    DCTMatrix[u][v] += Matrix[i][j] * cos(M_PI / ((float)N) * (i + 1. / 2.) * u) \
                    * cos(M_PI / ((float)M) * (j + 1. / 2.) * v);
                }
            }
        }
    }
 }

// LSB без ключа
void lsb(char *key)
{
    size_t i, j, k, p;

    for(i = 0; i < DEF_HASH_LEN; i++)
    {
        printf("%d", PHASH[i]);
    }
    printf("\n--------------\n");

    for(k = 0, p = 0; k < DEF_K2_LEN && p < DEF_HASH_LEN; k += 2, p += 2)
    {
        i = (size_t)key[k] - DEF_ADD;
        j = (size_t)key[k + 1] - DEF_ADD;

        // printf("%zu %zu\n", i, j);
        // R(BLOCK[i][j]) = 0;
        // G(BLOCK[i][j]) = 0;
        // B(BLOCK[i][j]) = 0;

        printf("%d %d\n", PHASH[p], PHASH[p + 1]);
        print_bits(B(BLOCK[i][j]));

        (PHASH[p]) ? ON_K_BIT(B(BLOCK[i][j]), 2) : OFF_K_BIT(B(BLOCK[i][j]), 2);
        (PHASH[p + 1]) ? ON_K_BIT(B(BLOCK[i][j]), 1) : OFF_K_BIT(B(BLOCK[i][j]), 1);

        print_bits(B(BLOCK[i][j]));
        printf("--------------\n");
        getchar();
    }

}

 void def_key(void)
 {
     size_t i, j, step, rt;
     int k;
     char ci, cj;
     char key[DEF_HASH_LEN + 1];

     srand(time(0));

     step = 10;
     k = 0;
     for(i = 0; i < DEF_BL_SIZE - step; i += step)
     {
         for(j = 0; j < DEF_BL_SIZE - step; j += step)
         {
            if(k < DEF_HASH_LEN - 1)
            {
                ci = rand() % step + i + DEF_ADD;
                key[k] = ci;
                k++;
                cj = rand() % step + j + DEF_ADD;
                key[k] = cj;
                k++;
            }
            else
            {
                i = DEF_BL_SIZE;
                j = DEF_BL_SIZE;
            }
         }
     }
     key[DEF_HASH_LEN] = '\0';
     printf("%s\n%d\n", key, k);

     i = 0;
     while(i < DEF_HASH_LEN * DEF_HASH_LEN)
     {
         ci = key[0];
         cj = key[1];

         rt = rand() % (DEF_HASH_LEN - 3) + 2;
         if(rt % 2)
         {
             rt++;
         }

         key[0] = key[rt];
         key[1] = key[rt + 1];

         key[rt] = ci;
         key[rt + 1] = cj;

         i++;
     }

     printf("%s\n", key);
 }

 int init_block(size_t x, size_t y)
 {
     size_t i, j;

     for (i = 0; i < DEF_BL_SIZE; i++)
     {
         for(j = 0; j < DEF_BL_SIZE; j++)
         {
             R(BLOCK[i][j]) = R(IM[x + i][y + j]);
             G(BLOCK[i][j]) = G(IM[x + i][y + j]);
             B(BLOCK[i][j]) = B(IM[x + i][y + j]);
         }
     }

     return 0;
 }

 int clean_block(void)
 {
     size_t i, j;

     for(i = 0; i < DEF_BL_SIZE; i++)
     {
         for(j = 0; j < DEF_BL_SIZE; j++)
         {
             R(BLOCK[i][j]) = 0;
             G(BLOCK[i][j]) = 0;
             B(BLOCK[i][j]) = 0;
         }
     }

     return 0;
 }

int setall(void)
{
    size_t i, j;

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        for(j = 0; j < DEF_IM_WIDTH; j++)
        {
            R(IM[i][j]) = 0;
            G(IM[i][j]) = 0;
            B(IM[i][j]) = 0;
        }
    }

    clean_block();

    memset(PHASH, 0, DEF_HASH_LEN);

    return 0;
}

void print_bits(uchar x)
{
    size_t i;
    int len = sizeof(uchar) * 8;
    int bit_str[len];

    for(i = 0; i < len; i++)
    {
        bit_str[i] = x & 0x01;
        x >>= 1;
    }

    for(i = 1; i <= len; i++)
    {
        printf("%d", bit_str[len - i]);
    }
    printf("\n");
}
