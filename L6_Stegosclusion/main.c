#include "lib/meta.h"
#include "lib/pngio.h"
#include "lib/enct.h"
#include "lib/dect.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    float avhem;

    printf("\n----------------------------------------------------------\n\n");

    if(argc == 2 && !strcmp(argv[1], "-e"))
    {
        setall();
        load_png(DEF_INFILE);
        encrypt(DEF_K2);
        write_png(DEF_ENCFILE);
    }
    else if(argc == 2 && !strcmp(argv[1], "-d"))
    {
        setall();
        load_png(DEF_ENCFILE);

        avhem = decrypt(DEF_K2);
        printf("Heming average:\t%f\n", avhem);
        if(avhem > DEF_AVHEM)
        {
            write_png(DEF_DECFILE);
        }
    }
    else
    {
        setall();
        if(load_png(DEF_INFILE))
        {
            return 1;
        }

        encrypt(DEF_K2);

        write_png(DEF_ENCFILE);
        setall();

        if(load_png(DEF_ENCFILE))
        {
            return 1;
        }

        avhem = decrypt(DEF_K2);
        printf("Heming average:\t%f\n", avhem);
        if(avhem > DEF_AVHEM)
        {
            write_png(DEF_ENCFILE);
        }
    }

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}
