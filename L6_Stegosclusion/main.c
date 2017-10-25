#include "lib/meta.h"
#include "lib/jpgio.h"
#include "lib/enct.h"
#include "lib/dect.h"

#include <stdio.h>

int main(void)
{
    // def_key(64);
    // encrypt
    // --------------------------------------
    load_jpg("in.jpg");

    encrypt(DEF_K2_KDB);

    write_jpg("enc_out.jpg");
    //--------------------------------------

    // setall();
    //
    // //decrypt
    // //--------------------------------------
    // load_jpg("enc_out.jpg");
    //
    // if(decrypt(DEF_K2_LSB))
    // {
    //     write_jpg("dec_out.jpg");
    // }
    //--------------------------------------

    return 0;
}
