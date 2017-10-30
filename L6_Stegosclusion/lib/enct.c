#include "enct.h"

void encrypt(char *key)
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

            HASH(key);
            // lsb(key);
            // kdb(key);

            for (i = 0; i < DEF_BL_SIZE; i++)
            {
                for(j = 0; j < DEF_BL_SIZE; j++)
                {
                    R(IM[u + i][v + j]) = R(BLOCK[i][j]);
                    G(IM[u + i][v + j]) = G(BLOCK[i][j]);
                    B(IM[u + i][v + j]) = B(BLOCK[i][j]);
                }
            }

            // u = DEF_IM_HEIGHT;
            // v = DEF_IM_WIDTH;
        }
    }

    printf("encrypt finished\n");
}

float pool(size_t I, size_t J)
{
    size_t i, j;
    uchar tR, tG, tB;
    uchar R[DEF_IM_NOFC];
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
    avg = (R(R) + G(R) + B(R)) / DEF_IM_NOFC;

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

    avg = 0;
    for(i = 0; i < DEF_PHB2_SIZE; i++)
    {
        for(j = 0; j < DEF_PHB2_SIZE; j++)
        {
            avg += DCT[i][j];
        }
    }
    avg -= DCT[0][0];
    avg /= pow(DEF_PHB2_SIZE, 2);

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

void lsb(char *key)
{
    size_t i, j, k, p;

    for(k = 0, p = 0; k < DEF_K2_LEN_LSB && p < DEF_HASH_LEN; k += 2, p += 2)
    {
        i = (size_t)key[k] - DEF_ADD;
        j = (size_t)key[k + 1] - DEF_ADD;

        (PHASH[p]) ? ON_K_BIT(B(BLOCK[i][j]), 2) : OFF_K_BIT(B(BLOCK[i][j]), 2);
        (PHASH[p + 1]) ? ON_K_BIT(B(BLOCK[i][j]), 1) : OFF_K_BIT(B(BLOCK[i][j]), 1);
    }
}

int kdb(char *key)
{
    size_t i, j, k, p;
    float ld, Y;

    ld = DEF_KDB_LDA;
    for(k = 0, p = 0; k < DEF_K2_LEN_KDB && p < DEF_HASH_LEN; k += 2, p++)
    {
        i = (size_t)key[k] - DEF_ADD;
        j = (size_t)key[k + 1] - DEF_ADD;

        Y = ld * (0.2989 * R(BLOCK[i][j]) + 0.58662 * G(BLOCK[i][j]) + 0.11448 * B(BLOCK[i][j]));
        (PHASH[p]) ? (B(BLOCK[i][j]) += Y) : (B(BLOCK[i][j]) -= Y);
    }

    return 0;
}

void def_key(int nofpix)
{
    size_t i, j, step, rt, mix, swind;
    int k, keylen;
    float t;
    char ci, cj;

    keylen = 2 * nofpix + 1;
    char key[keylen];

    srand(time(0));

    t = sqrt((double)nofpix);
    step = (size_t)t;
    if(fmod(t, 1))
    {
        step++;
    }
    swind = DEF_BL_SIZE - DEF_KDB_SIG * 2;
    step = (size_t)(swind / step);
    // printf("%zu\n", step);
    // getchar();

    for(k = 0, i = DEF_KDB_SIG; i < DEF_BL_SIZE - DEF_KDB_SIG - step + 1; i += step)
    {
        for(j = DEF_KDB_SIG; j < DEF_BL_SIZE - DEF_KDB_SIG - step + 1; j += step)
        {
            if(k < keylen - 2)
            {
                ci = rand() % (step - DEF_KDB_SIG) + i + DEF_ADD;
                key[k] = ci;
                k++;
                cj = rand() % (step - DEF_KDB_SIG) + j + DEF_ADD;
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
    key[keylen] = '\0';
    printf("%s\n%d\n", key, k);

    i = 0;
    mix = (size_t)pow(keylen, 4);
    while(i < mix)
    {
        ci = key[0];
        cj = key[1];

        rt = rand() % (keylen - 4) + 2;
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
    getchar();
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
