#include "rsa.h"

int64 Eiler(int64 n)
{
    int64 i;
    int64 fi = n;
    int64 tn = n;
    int64 en = (int64)(sqrt((double)(n) + 1));

    for (i = 2; i <= en; i++)
    {
        if (!(tn % i))
        {
            while (!(tn % i))
            {
                tn = (double)tn / (double)i;
            }

            fi = fi - (int64)((double)fi / (double)i);
        }
    }

    if (tn > 1)
    {
        fi = fi - (int64)((double)fi / (double)tn);
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

// void Enc(int64 n, int64 e)
// {
//     int64 iblok, modpow;
//     char buf[DEF_STR_LEN];
//     char copy[DEF_STR_LEN];
//     int k = DEF_BLOCK_LEN; //длина шифруемого блока = rsa_block
//
//     strcpy(copy, rsa_shifro_text);
//
//     while (strlen(copy) > 0) //блоки из текста
//     {
//         if (k < strlen(copy))
//         {
//             memcpy(buf, copy, k);
//             iblok = (int64)atoi(buf);
//             //iblok = (ulong)Convert.ToInt64(copy.Substring(0, k));
//             strcpy(buf, copy);
//             memcpy(copy, buf + k, strlen(copy) - k);
//             //copy = copy.Remove(0, k);
//         }
//         else
//         {
//             iblok = (int64)atoi(copy);
//             //blok = (ulong)Convert.ToInt64(copy);
//             sprintf(copy, "%s", "");
//             // copy = "";
//         }
//
//         modpow = (int64)pow((double)iblok, (double)e) % n;
//         sprintf(rsa_block, "%llu", modpow);
//         // rsa_block = Convert.ToString(BigInteger.ModPow(blok, e, n)); // шифровки ModPow функция, которая считает rsa_block^e mod n
//         while(strlen(rsa_block) < k)
//         {
//             memset(rsa_block, '0', 1);
//         }
//         // while (rsa_block.Length < k) //нули, чтоб потом было удобно расшифровывать и чтоб из n цифр текста получалось n цифр шифротекста
//         //     rsa_block = "0" + rsa_block;
//         strcat(etext, rsa_block);
//         // rsa_shifro_text += rsa_block;
//     }
//
//     return;
// }

void Dec(int64 n, int64 d)
{
    mpz_t gmp_modpow, gmp_iblok, gmp_d, gmp_n;
    int64 modpow;
    char buf[DEF_STR_LEN];
    char copy[DEF_STR_LEN];
    int copy_len;

    mpz_init(gmp_d);
    mpz_init(gmp_n);
    ull2mpz(gmp_d, d);
    ull2mpz(gmp_n, n);

    strcpy(copy, rsa_shifro_text);
    copy_len = strlen(copy);
    while (copy_len)
    {
        mpz_init(gmp_iblok);
        mpz_init(gmp_modpow);

        if (DEF_BLOCK_LEN < copy_len)
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
        modpow = mpz2ull(gmp_modpow);

        sprintf(rsa_block, "%llu", modpow);
        strcat(rsa_dtext, rsa_block);

        mpz_clear(gmp_iblok);
        mpz_clear(gmp_modpow);
    }

    return;
}

void ull2mpz(mpz_t z, int64 ull)
{
    mpz_import(z, 1, -1, sizeof ull, 0, 0, &ull);
}

int64 mpz2ull(mpz_t z)
{
    int64 result = 0;
    mpz_export(&result, 0, -1, sizeof result, 0, 0, z);

    return result;
}
