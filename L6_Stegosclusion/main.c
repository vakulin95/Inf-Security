#include "lib/meta.h"
#include "lib/pngio.h"
#include "lib/enct.h"
#include "lib/dect.h"

int main(int argc, char *argv[])
{
    // printf("%s\n", DEF_K2);
    // getchar();
    // def_key(64);

    printf("\n----------------------------------------------------------\n\n");

    if(argc == 2 && !strcmp(argv[1], "-e"))
    {
        setall();
        if(load_png(DEF_INFILE))
        {
            return 1;
        }
        encrypt(DEF_K2);
        write_png(DEF_ENCFILE);
    }
    else if(argc == 2 && !strcmp(argv[1], "-d"))
    {
        setall();

        if(load_png(DEF_ENCFILE))
        {
            return 1;
        }

        if(decrypt(DEF_K2))
        {
            write_png(DEF_DECFILE);
            printf("\nAuthentication: False\n");
        }
        else
        {
            printf("\nAuthentication: True\n");
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

        if(decrypt(DEF_K2))
        {
            write_png(DEF_DECFILE);
            printf("\nAuthentication: False\n");
        }
        else
        {
            printf("\nAuthentication: True\n");
        }
    }

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}
