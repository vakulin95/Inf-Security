#include "lib/meta.h"
#include "lib/jpgio.h"
#include "lib/enct.h"
#include "lib/dect.h"

#include <stdio.h>
#include <string.h>

#define DEF_INFILE      "in_1.jpg"
#define DEF_ENCFILE     "enc_out.jpg"
#define DEF_DECFILE     "dec_out.jpg"

int main(int argc, char *argv[])
{
    float avhem;

    printf("\n----------------------------------------------------------\n\n");

    if(argc == 2 && !strcmp(argv[1], "-e"))
    {
        printf("argc = -e\n");

        setall();
        load_jpg(DEF_INFILE);
        encrypt(DEF_K2);
        write_jpg(DEF_ENCFILE);
    }
    else if(argc == 2 && !strcmp(argv[1], "-d"))
    {
        printf("argc = -d\n");

        setall();
        load_jpg(DEF_ENCFILE);

        avhem = decrypt(DEF_K2);
        printf("Heming average:\t%f\n", avhem);
        if(avhem > 20)
        {
            write_jpg(DEF_DECFILE);
        }
    }
    else
    {
        printf("no argc\n");

        setall();
        load_jpg(DEF_INFILE);
        encrypt(DEF_K2);
        write_jpg(DEF_ENCFILE);

        setall();
        load_jpg(DEF_ENCFILE);

        avhem = decrypt(DEF_K2);
        printf("Heming average:\t%f\n", avhem);
        if(avhem > 20)
        {
            write_jpg(DEF_DECFILE);
        }
    }

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}
