#include <stdio.h>
#include "rsa.h"

#define DEF_SHIFR               "419529693641281414842251130008422950947927526"
#define DEF_N                   (int64)(517758144238469)
#define DEF_E                   (int64)(15931)

int main(int argc, char *argv[])
{
    printf("\n-----------------------------------------The RSA algorithm-----------------------------------------\n\n");

    int64 d;

    sprintf(rsa_shifro_text, "%s", DEF_SHIFR);

    d = Find_d(Eiler(DEF_N), DEF_E);

    printf("Inputed message:\t%s\n", DEF_SHIFR);

    Dec(DEF_N, d);
    printf("Decoded message:\t%s\n", rsa_dtext);

    Enc(DEF_N, DEF_E);
    printf("Encoded message:\t%s\n", rsa_etext);

    printf("\nProgram result:\t\t");
    if(!strcmp(DEF_SHIFR, rsa_etext))
    {
        printf("Sucsess!\n");
    }
    else
    {
        printf("Failed!\n");
    }

    printf("---------------------------------------------------------------------------------------------------\n");

    return 0;
}
