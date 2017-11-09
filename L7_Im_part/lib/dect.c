#include "dect.h"

int decrypt(void)
{
    size_t i, j;

    flsb(DEF_K2_LSB);
    unfbl();
    mdecompress();

    write_decbl(DEF_X_OFFSET, DEF_Y_OFFSET);

    return 0;
}

int unfbl(void)
{
    size_t i, j;
    int64 enc, dec;
    uchar *buf;

    buf = (uchar*)malloc(sizeof(uchar) * DEF_MES_LEN);

    for(i = 0; i < COMP_LEN; i += DEF_MES_LEN)
    {
        enc = conv_str(COMP_BLOCK + i);
        dec = fl_show(enc);

        conv_int(dec, &buf);
        for(j = i; j < i + DEF_MES_LEN; j++)
        {
            COMP_BLOCK[j] = buf[j % DEF_MES_LEN];
        }
        memset(buf, 0, DEF_MES_LEN);
    }
    //
    // for(i = COMP_LEN - 20; i < COMP_LEN; i++)
    // {
    //     printf("%d- %d\n", i, COMP_BLOCK[i]);
    // }
    // printf("-----------\n");

    free(buf);

    return 0;
}

int flsb(int key)
{
    size_t i, j, k, p;

    p = 0;
    for(i = 0; i < DEF_IM_HEIGHT; i += key)
    {
        for(j = 0; j < DEF_IM_WIDTH; j += key)
        {
            if((i > DEF_Y_OFFSET - 2 * key && i < DEF_Y_OFFSET + DEF_BL_SIZE + 2 * key) \
            && (j > DEF_X_OFFSET - 2 * key && j < DEF_X_OFFSET + DEF_BL_SIZE + 2 * key))
            {
                continue;
            }

            if(p < COMP_LEN)
            {
                CHECK_K_BIT(IM[i][j][1], 1) ? ON_K_BIT(COMP_BLOCK[p], 1) : OFF_K_BIT(COMP_BLOCK[p], 1);
                CHECK_K_BIT(IM[i][j][1], 2) ? ON_K_BIT(COMP_BLOCK[p], 2) : OFF_K_BIT(COMP_BLOCK[p], 2);
                CHECK_K_BIT(IM[i][j][1], 3) ? ON_K_BIT(COMP_BLOCK[p], 3) : OFF_K_BIT(COMP_BLOCK[p], 3);

                CHECK_K_BIT(IM[i][j][2], 1) ? ON_K_BIT(COMP_BLOCK[p], 4) : OFF_K_BIT(COMP_BLOCK[p], 4);
                CHECK_K_BIT(IM[i][j][2], 2) ? ON_K_BIT(COMP_BLOCK[p], 5) : OFF_K_BIT(COMP_BLOCK[p], 5);
                CHECK_K_BIT(IM[i][j][2], 3) ? ON_K_BIT(COMP_BLOCK[p], 6) : OFF_K_BIT(COMP_BLOCK[p], 6);

                CHECK_K_BIT(IM[i][j][3], 1) ? ON_K_BIT(COMP_BLOCK[p], 7) : OFF_K_BIT(COMP_BLOCK[p], 7);
                CHECK_K_BIT(IM[i][j][3], 2) ? ON_K_BIT(COMP_BLOCK[p], 8) : OFF_K_BIT(COMP_BLOCK[p], 8);
                p++;
            }
            else
            {
                i = DEF_IM_HEIGHT;
                j = DEF_IM_WIDTH;
            }
        }
    }

    if(p != COMP_LEN)
    {
        printf("Some problem in flsb()!\n");
        exit(1);
    }

    return 0;
}

int mdecompress(void)
{
    size_t i;

    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    // setup "b" as the input and "c" as the compressed output
    infstream.avail_in = tlen; // size of input
    infstream.next_in = (Bytef*)COMP_BLOCK; // input char array
    infstream.avail_out = (uInt)(sizeof(DECOMP_BLOCK)); // size of output
    infstream.next_out = (Bytef*)DECOMP_BLOCK; // output char array

    // the actual DE-compression work.
    // inflateInit2(&infstream, Z_BEST_COMPRESSION, Z_DEFLATED, 8, 1, 4);
    // inflateInit2(&infstream, 9);
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);

    printf("Uncompressed size is:\t%u\n", infstream.avail_out);
    for(i = 0; i < DEF_BL_LEN; i++)
    {
        if(BLOCK[i] != DECOMP_BLOCK[i])
        {
            // printf("%zu\t- %d | %d\n", i - 1, BLOCK[i - 1], DECOMP_BLOCK[i - 1]);
            printf("%zu\t- %d | %d\n", i, BLOCK[i], DECOMP_BLOCK[i]);
            // printf("FALSE!\n");
            break;
            // exit(1);
            // getchar();
        }
    }

    return 0;
}

int write_decbl(size_t x, size_t y)
{
    size_t i, j;

    if(x + DEF_BL_SIZE > DEF_IM_WIDTH || y + DEF_BL_SIZE > DEF_IM_HEIGHT)
    {
        printf("Wrong OFFSET!\n");
        exit(1);
    }

    for (i = 0; i < DEF_BL_SIZE; i++)
    {
        for(j = 0; j < DEF_BL_SIZE; j++)
        {
            R(IM[y + i][x + j]) = DECOMP_BLOCK[i * DEF_BL_SIZE + j];
            G(IM[y + i][x + j]) = DECOMP_BLOCK[i * DEF_BL_SIZE + j + DEF_BL_SIZE * DEF_BL_SIZE];
            B(IM[y + i][x + j]) = DECOMP_BLOCK[i * DEF_BL_SIZE + j + 2 * DEF_BL_SIZE * DEF_BL_SIZE];
        }
    }

    return 0;
}
