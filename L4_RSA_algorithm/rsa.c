#include "rsa.h"

int64 Eiler(int64 n)
{
    int64 i;
    int64 fi = n;
    int64 en = (int64)(sqrt((double)(n) + 1));

    for (i = 2; i <= en; i++)
    {
        if (!(n % i))
        {
            while (!(n % i))
            {
                n = n / i;
            }
            fi = fi - (fi / i);
        }
    }

    if (n > 1)
    {
        fi = fi - (fi / n);
    }

    return fi;
}

int64 Find_d(int64 fi, int64 e)
{
    int64 i;
    int64 d = 0;

    for (i = 0; ; i++)
    {
        if (!((fi * i + 1) % e))
        {
            d = (fi * i + 1) / e;
            break;
        }
    }

    return d;
}

void Enc(int64 n, int64 e)
{
    mpz_t gmp_modpow, gmp_iblok, gmp_e, gmp_n;
    int64 modpow;
    char buf[DEF_STR_LEN];
    char copy[DEF_STR_LEN];
    int copy_len;

    mpz_init(gmp_e);
    mpz_init(gmp_n);
    mpz_import(gmp_n, 1, -1, sizeof(n), 0, 0, &n);
    mpz_import(gmp_e, 1, -1, sizeof(e), 0, 0, &e);

    strcpy(copy, rsa_dtext);
    copy_len = strlen(copy);
    while(copy_len)
    {
        mpz_init(gmp_iblok);
        mpz_init(gmp_modpow);

        if(DEF_BLOCK_LEN < copy_len)
        {
            memcpy(buf, copy, DEF_BLOCK_LEN);
            buf[DEF_BLOCK_LEN] = '\0';
            mpz_set_str(gmp_iblok, buf, 10);

            strcpy(buf, copy);
            memcpy(copy, buf + DEF_BLOCK_LEN, copy_len - DEF_BLOCK_LEN + 1);
            copy_len = strlen(copy);
        }
        else
        {
            mpz_set_str(gmp_iblok, copy, 10);
            copy_len = 0;
        }

        mpz_powm(gmp_modpow, gmp_iblok, gmp_e, gmp_n);
        mpz_export(&modpow, 0, -1, sizeof(modpow), 0, 0, gmp_modpow);

        sprintf(rsa_block, "%llu", modpow);
        ins_null();
        strcat(rsa_etext, rsa_block);

        mpz_clear(gmp_iblok);
        mpz_clear(gmp_modpow);
    }

    return;
}

void Dec(int64 n, int64 d)
{
    mpz_t gmp_modpow, gmp_iblok, gmp_d, gmp_n;
    int64 modpow;
    char buf[DEF_STR_LEN];
    char copy[DEF_STR_LEN];
    int copy_len;

    mpz_init(gmp_d);
    mpz_init(gmp_n);
    mpz_import(gmp_n, 1, -1, sizeof(n), 0, 0, &n);
    mpz_import(gmp_d, 1, -1, sizeof(d), 0, 0, &d);

    strcpy(copy, rsa_shifro_text);
    copy_len = strlen(copy);
    while(copy_len)
    {
        mpz_init(gmp_iblok);
        mpz_init(gmp_modpow);

        if(DEF_BLOCK_LEN < copy_len)
        {
            memcpy(buf, copy, DEF_BLOCK_LEN);
            buf[DEF_BLOCK_LEN] = '\0';
            mpz_set_str(gmp_iblok, buf, 10);
            strcpy(buf, copy);
            memcpy(copy, buf + DEF_BLOCK_LEN, copy_len - DEF_BLOCK_LEN + 1);
            copy_len = strlen(copy);
        }
        else
        {
            mpz_set_str(gmp_iblok, copy, 10);
            copy_len = 0;
        }

        mpz_powm(gmp_modpow, gmp_iblok, gmp_d, gmp_n);
        mpz_export(&modpow, 0, -1, sizeof(modpow), 0, 0, gmp_modpow);

        sprintf(rsa_block, "%llu", modpow);
        ins_null();
        strcat(rsa_dtext, rsa_block);

        mpz_clear(gmp_iblok);
        mpz_clear(gmp_modpow);
    }

    return;
}

void ins_null(void)
{
    char buf[DEF_STR_LEN];

    while(strlen(rsa_block) < DEF_BLOCK_LEN)
    {
        sprintf(buf, "0");
        strcat(buf, rsa_block);
        strcpy(rsa_block, buf);
    }

    return;
}
