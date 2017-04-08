#include <stdio.h>
#include <string.h>
#include "feistel.h"

#define DEF_STR     "FeistelCBC enc: 012346789qwerty"

int main(int argc, char *argv[])
{
    int64 *mes, *enc, *dec;
    char *buf;

    printf("-------------------------Feistel network-------------------------\n");

    buf = (char*)malloc(sizeof(char) * DEF_CBC_PART_LEN * DEF_NUM_OF_CBC_PARTS);
    mes = (int64*)malloc(sizeof(int64) * DEF_NUM_OF_CBC_PARTS);
    enc = (int64*)malloc(sizeof(int64) * DEF_NUM_OF_CBC_PARTS);
    dec = (int64*)malloc(sizeof(int64) * DEF_NUM_OF_CBC_PARTS);

    conv_str(DEF_STR, &mes);
    flCBC_hide(mes, &enc);
    flCBC_show(enc, &dec);

    conv_int(mes, &buf);
    printf("Input message:\n%s\n\n", buf);

    conv_int(enc, &buf);
    printf("Encrypted message:\n%s\n\n", buf);

    conv_int(dec, &buf);
    printf("Decoded message:\n%s\n\n", buf);

    if(argc == 2 && !strcmp(argv[1], "-b"))
    {
        printb("Input message:\n", mes);
        printb("Encrypted message:\n", enc);
        printb("Decoded message:\n", dec);
    }
    else if(argc == 2)
    {
        printf("Invalid argument in main()!\nTry -b - to see the message in binary form\n");
    }

    printf("-----------------------------------------------------------------\n");

    free(buf);
    return 0;
}
