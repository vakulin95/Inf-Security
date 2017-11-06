#include "lib/meta.h"
#include "lib/pngio.h"
#include "lib/enct.h"
#include "lib/dect.h"

int main(int argc, char *argv[])
{
    printf("\n----------------------------------------------------------\n\n");

    if(argc == 2 && !strcmp(argv[1], "-e"))
    {
        // ecrtypt
    }
    else if(argc == 2 && !strcmp(argv[1], "-d"))
    {
        // decrypt
    }
    else
    {
        if(load_png(DEF_INFILE))
        {
            return 1;
        }

        encrypt();

        write_png(DEF_ENCFILE);
    }

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}
