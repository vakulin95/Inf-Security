#include <stdio.h>
#include <string.h>
#include "feistel.h"

#define DEF_STR     "FEISTEL1"

int main(int argc, char *argv[])
{
    int64 *mes, *enc, *dec;

    char *buf;

    printf("-------------------------Feistel network-------------------------\n");

    buf = (char*)malloc(sizeof(char) * DEF_MES_LEN);
    mes = (int64*)malloc(sizeof(int64) * DEF_NUM_OF_CBC_PARTS);
    enc = (int64*)malloc(sizeof(int64) * DEF_NUM_OF_CBC_PARTS);
    dec = (int64*)malloc(sizeof(int64) * DEF_NUM_OF_CBC_PARTS);

    mes[0] = mes[1] = mes[2] = 34567890098765432;
    CBCencode(mes, &enc);
    CBCdecode(enc, &dec);

    printb("INP:\n", mes);
    printb("ENC:\n", enc);
    printb("DEC:\n", dec);


    //mes = conv_str(DEF_STR);
    //enc = fl_hide(mes);
    //dec = fl_show(enc);

    //conv_int(mes, &buf);
    //printf("Input message:\n%s\n\n", buf);

    // conv_int(enc, &buf);
    // printf("Encrypted message:\n%s\n\n", buf);
    //
    // conv_int(dec, &buf);
    // printf("Decoded message:\n%s\n\n", buf);
    //
    // if(argc == 2 && !strcmp(argv[1], "-b"))
    // {
    //     printb("Input message:\t\t", mes);
    //     printb("Encrypted message:\t", enc);
    //     printb("Decoded message:\t", dec);
    // }
    // else if(argc == 2)
    // {
    //     printf("Invalid argument in main()!\nTry -b - to see the message in binary form\n");
    // }

    printf("-----------------------------------------------------------------\n");

    free(buf);
    return 0;
}
