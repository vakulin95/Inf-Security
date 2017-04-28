#include <stdio.h>
#include <locale.h>
#include "caes.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    printf("\n-----------------------------------------Caesar's code-----------------------------------------\n\n");

    printf("String Entered:\n\n%ls\n\nlength: %d\n", TEXT, wcslen(TEXT));

    // if(TEXT[0] == L'w')
    // {
    //     printf("+\n");
    // }
    // else
    // {
    //     printf("-\n");
    // }

    printf("-----------------------------------------------------------------------------------------------\n");

    return 0;
}
