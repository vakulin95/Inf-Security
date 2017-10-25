#include "lib/meta.h"
#include "lib/jpgio.h"
#include "lib/enct.h"
#include "lib/dect.h"

#include <stdio.h>

int main(void)
{
    //encrypt
    //--------------------------------------
    load_jpg("in.jpg");

    encrypt(DEF_K2);

    // write_jpg("enc_out.jpg");
    //--------------------------------------

    // setall();

    //decrypt
    //--------------------------------------
    // load_jpg("in.jpg");

    if(decrypt(DEF_K2))
    {
        write_jpg("dec_out.jpg");
    }
    //--------------------------------------

    return 0;
}
