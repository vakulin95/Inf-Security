#include "feistel.h"

int main()
{
    int64 mes, enc, dec;
    char *buf;

    printf("-------------------------Feistel network-------------------------\n");

    buf = (char*)malloc(sizeof(char) * DEF_MES_LEN);

    mes = conv_str("qwertyfl");
    enc = fl_hide(mes);
    dec = fl_show(enc);

    conv_int(mes, &buf);
    printf("Input message:\n%s\n", buf);

    conv_int(enc, &buf);
    printf("Encrypted message:\n%s\n", buf);

    conv_int(dec, &buf);
    printf("Decoded message:\n%s\n", buf);

    // printb("INP:\t", message);
    // message = fl_hide(message);
    // printb("ENC:\t", message);
    // message = fl_show(message);
    // printb("DEC:\t", message);

    printf("-----------------------------------------------------------------\n");

    free(buf);
    return 0;
}
