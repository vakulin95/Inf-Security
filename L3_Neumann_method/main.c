#include <stdio.h>
#include <string.h>
#include "rand_gen.h"

int main(int argc, char *argv[])
{
    printf("\n-----------------------------------------Feistel network-----------------------------------------\n\n");

    rand_gen();
    if(argc == 1)
    {
        print_res(0);
    }
    else if(argc == 2 && !strcmp(argv[1], "-l"))
    {
        print_res(1);
    }
    else if(argc >= 2)
    {
        printf("Invalid argument in main()!\nTry -l - to see the message in binary form\n");
    }

    printf("-------------------------------------------------------------------------------------------------\n");

    return 0;
}
