#include <stdio.h>
#include <string.h>
#include "rand_gen.h"

int main(int argc, char *argv[])
{
    int i;

    printf("-------------------------Feistel network-------------------------\n");

    rand_gen();
    print_res(1);

    printf("-----------------------------------------------------------------\n");

    return 0;
}
