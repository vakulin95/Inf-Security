#include <stdio.h>
#include "rsa.h"

// variant # 20
#define DEF_SHIFR               "108230462382949240744446393133139920760825242128635453394626156290136879344"
#define DEF_N                   (int64)(274611845366113)
#define DEF_E                   (int64)(23311)

int main(int argc, char *argv[])
{
    printf("\n-----------------------------------------The RSA algorithm-----------------------------------------\n\n");

    rsa_init(DEF_SHIFR, DEF_N, DEF_E);

    printf("Inputed message:\t%s\n", rsa_INIT);

    rsa_decode(DEF_N, rsa_D);
    printf("Decoded message:\t%s\n", rsa_DTEXT);

    rsa_encode(DEF_N, DEF_E);
    printf("Encoded message:\t%s\n", rsa_ETEXT);

    printf("\nProgram result:\t\t");
    if(!strcmp(rsa_INIT, rsa_ETEXT))
    {
        printf("Success!\n");
    }
    else
    {
        printf("Failed!\n");
    }

    printf("---------------------------------------------------------------------------------------------------\n");

    return 0;
}
