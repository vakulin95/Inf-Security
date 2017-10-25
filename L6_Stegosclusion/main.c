#include "lib/meta.h"
#include "lib/jpgio.h"
#include "lib/enct.h"
#include "lib/dect.h"

#include <stdio.h>

int main(void)
{
    float avhem;

    // def_key(64);
    // encrypt
    // --------------------------------------
    load_jpg("in_1.jpg");

    encrypt(DEF_K2);

    // write_jpg("enc_out.jpg");
    // --------------------------------------

    // setall();

    //decrypt
    //--------------------------------------
    // load_jpg("enc_out.jpg");

    avhem = decrypt(DEF_K2);
    printf("Heming average:\t%f\n", avhem);
    if(avhem > 30)
    {
        write_jpg("dec_out.jpg");
    }
    //--------------------------------------

    return 0;
}
