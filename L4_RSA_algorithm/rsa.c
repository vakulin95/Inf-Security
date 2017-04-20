#include "rsa.h"

//---------------------------------------------------------------------------//

void rsa_ins_null(void);
int64 rsa_eiler(int64 n);
int64 rsa_set_d(int64 fi, int64 e);

//---------------------------------------------------------------------------//

void rsa_init(char *str, int64 n, int64 e)
{
    sprintf(rsa_INIT, "%s", str);

    rsa_Block_len = strlen(str) / DEF_NOF_BLOCK;
    rsa_Eil = rsa_eiler(n);
    rsa_D = rsa_set_d(rsa_Eil, e);

    return;
}

void rsa_encode(int64 n, int64 e)
{
    mpz_t gmp_modpow, gmp_iblock, gmp_e, gmp_n;
    int64 modpow;
    char buf[DEF_STR_LEN];
    char copy[DEF_STR_LEN];
    int copy_len;

    mpz_init(gmp_e);
    mpz_init(gmp_n);
    mpz_import(gmp_n, 1, -1, sizeof(n), 0, 0, &n);
    mpz_import(gmp_e, 1, -1, sizeof(e), 0, 0, &e);

    strcpy(copy, rsa_DTEXT);
    copy_len = strlen(copy);
    while(copy_len)
    {
        mpz_init(gmp_iblock);
        mpz_init(gmp_modpow);

        if(rsa_Block_len < copy_len)
        {
            memcpy(buf, copy, rsa_Block_len);
            buf[rsa_Block_len] = '\0';
            mpz_set_str(gmp_iblock, buf, 10);

            strcpy(buf, copy);
            memcpy(copy, buf + rsa_Block_len, copy_len - rsa_Block_len + 1);
            copy_len = strlen(copy);
        }
        else
        {
            mpz_set_str(gmp_iblock, copy, 10);
            copy_len = 0;
        }

        mpz_powm(gmp_modpow, gmp_iblock, gmp_e, gmp_n);
        mpz_export(&modpow, 0, -1, sizeof(modpow), 0, 0, gmp_modpow);

        sprintf(rsa_BLOCK, "%llu", modpow);
        rsa_ins_null();
        strcat(rsa_ETEXT, rsa_BLOCK);

        mpz_clear(gmp_iblock);
        mpz_clear(gmp_modpow);
    }

    return;
}

void rsa_decode(int64 n, int64 d)
{
    mpz_t gmp_modpow, gmp_iblock, gmp_d, gmp_n;
    int64 modpow;
    char buf[DEF_STR_LEN];
    char copy[DEF_STR_LEN];
    int copy_len;

    mpz_init(gmp_d);
    mpz_init(gmp_n);
    mpz_import(gmp_n, 1, -1, sizeof(n), 0, 0, &n);
    mpz_import(gmp_d, 1, -1, sizeof(d), 0, 0, &d);

    strcpy(copy, rsa_INIT);
    copy_len = strlen(copy);
    while(copy_len)
    {
        mpz_init(gmp_iblock);
        mpz_init(gmp_modpow);

        if(rsa_Block_len < copy_len)
        {
            memcpy(buf, copy, rsa_Block_len);
            buf[rsa_Block_len] = '\0';
            mpz_set_str(gmp_iblock, buf, 10);
            strcpy(buf, copy);
            memcpy(copy, buf + rsa_Block_len, copy_len - rsa_Block_len + 1);
            copy_len = strlen(copy);
        }
        else
        {
            mpz_set_str(gmp_iblock, copy, 10);
            copy_len = 0;
        }

        mpz_powm(gmp_modpow, gmp_iblock, gmp_d, gmp_n);
        mpz_export(&modpow, 0, -1, sizeof(modpow), 0, 0, gmp_modpow);

        sprintf(rsa_BLOCK, "%llu", modpow);
        rsa_ins_null();
        strcat(rsa_DTEXT, rsa_BLOCK);

        mpz_clear(gmp_iblock);
        mpz_clear(gmp_modpow);
    }

    return;
}

//---------------------------------------------------------------------------//

void rsa_ins_null(void)
{
    char buf[DEF_STR_LEN];

    while(strlen(rsa_BLOCK) < rsa_Block_len)
    {
        sprintf(buf, "0");
        strcat(buf, rsa_BLOCK);
        strcpy(rsa_BLOCK, buf);
    }

    return;
}

int64 rsa_eiler(int64 n)
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

int64 rsa_set_d(int64 fi, int64 e)
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
