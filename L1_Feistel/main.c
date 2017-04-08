#include "feistel.h"

int main()
{
    char message[DEF_MES_LEN];

    sprintf(message, "qwertyfl");
    //int64 message = 880035355599669969;

    printf("-------------------------Feistel network-------------------------\n");

    printb("INP:\t", message);
    message = fl_hide(message);
    printb("ENC:\t", message);
    message = fl_show(message);
    printb("DEC:\t", message);

    printf("-----------------------------------------------------------------\n");

    return 0;
}
