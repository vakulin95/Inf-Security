#include "lib/meta.h"
#include "lib/enct.h"
#include "lib/jpgio.h"

#include <stdio.h>

int main(void)
{
    size_t i, j;

    load_jpg("in.jpg");

    encrypt();

    write_jpg("out.jpg");

    // def_key();
    // printf("%s\n", DEF_K2);

    return 0;
}
