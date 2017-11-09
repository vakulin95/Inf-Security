#include "enct.h"

int encrypt(void)
{
    init_block(DEF_X_OFFSET, DEF_Y_OFFSET);

    mcompress();
    fbl();
    lsb(DEF_K2_LSB);

    set_block(DEF_X_OFFSET, DEF_Y_OFFSET);

    return 0;
}

int fbl(void)
{
    size_t i, j;
    int64 mes, enc;
    uchar *buf;

    // for(i = COMP_LEN - 20; i < COMP_LEN; i++)
    // {
    //     printf("%d- %d\n", i, COMP_BLOCK[i]);
    // }
    // printf("-----------\n");

    buf = (uchar*)malloc(sizeof(uchar) * DEF_MES_LEN);

    for(i = 0; i < COMP_LEN; i += DEF_MES_LEN)
    {
        mes = conv_str(COMP_BLOCK + i);
        enc = fl_hide(mes);

        conv_int(enc, &buf);
        for(j = i; j < i + DEF_MES_LEN; j++)
        {
            COMP_BLOCK[j] = buf[j % DEF_MES_LEN];
        }
        memset(buf, 0, DEF_MES_LEN);
    }

    free(buf);

    return 0;
}

int lsb(int key)
{
    size_t i, j, k, p, b;

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
                CHECK_K_BIT(COMP_BLOCK[p], 1) ? ON_K_BIT(IM[i][j][1], 1) : OFF_K_BIT(IM[i][j][1], 1);
                CHECK_K_BIT(COMP_BLOCK[p], 2) ? ON_K_BIT(IM[i][j][1], 2) : OFF_K_BIT(IM[i][j][1], 2);
                CHECK_K_BIT(COMP_BLOCK[p], 3) ? ON_K_BIT(IM[i][j][1], 3) : OFF_K_BIT(IM[i][j][1], 3);

                CHECK_K_BIT(COMP_BLOCK[p], 4) ? ON_K_BIT(IM[i][j][2], 1) : OFF_K_BIT(IM[i][j][2], 1);
                CHECK_K_BIT(COMP_BLOCK[p], 5) ? ON_K_BIT(IM[i][j][2], 2) : OFF_K_BIT(IM[i][j][2], 2);
                CHECK_K_BIT(COMP_BLOCK[p], 6) ? ON_K_BIT(IM[i][j][2], 3) : OFF_K_BIT(IM[i][j][2], 3);

                CHECK_K_BIT(COMP_BLOCK[p], 7) ? ON_K_BIT(IM[i][j][3], 1) : OFF_K_BIT(IM[i][j][3], 1);
                CHECK_K_BIT(COMP_BLOCK[p], 8) ? ON_K_BIT(IM[i][j][3], 2) : OFF_K_BIT(IM[i][j][3], 2);
                p++;
            }
            else
            {
                i = DEF_IM_HEIGHT;
                j = DEF_IM_WIDTH;
            }
        }
    }

    if(p < COMP_LEN)
    {
        printf("DEF_K2_LSB is too large!\n");
        exit(1);
    }

    return 0;
}

uInt mcompress(void)
{
    size_t i;

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    // setup "a" as the input and "b" as the compressed output
    defstream.avail_in = (uInt)(DEF_BL_SIZE * DEF_BL_SIZE * DEF_IM_NOFC); // size of input, string + terminator
    defstream.next_in = (Bytef *)BLOCK; // input char array
    defstream.avail_out = (uInt)(sizeof(COMP_BLOCK)); // size of output
    defstream.next_out = (Bytef *)COMP_BLOCK; // output char array

    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    tlen = (uInt)((uchar*)defstream.next_out - COMP_BLOCK);

    COMP_LEN = tlen;
    if(defstream.avail_out % 8)
    {
        COMP_LEN = tlen + (8 - (tlen % 8));
        for(i = tlen; i < COMP_LEN; i++)
        {
            COMP_BLOCK[i] = 0;
        }
    }

    printf("Input size is:\t\t%lu\n", sizeof(BLOCK));
    printf("Compressed size is:\t%u\n", COMP_LEN);

    return 0;
}

int init_block(size_t x, size_t y)
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
            BLOCK[i * DEF_BL_SIZE + j]                                 = R(IM[y + i][x + j]);
            BLOCK[i * DEF_BL_SIZE + j + DEF_BL_SIZE * DEF_BL_SIZE]     = G(IM[y + i][x + j]);
            BLOCK[i * DEF_BL_SIZE + j + 2 * DEF_BL_SIZE * DEF_BL_SIZE] = B(IM[y + i][x + j]);
        }
    }

    return 0;
}

int set_block(size_t x, size_t y)
{
    size_t i, j;

    if(x + DEF_BL_SIZE > DEF_IM_WIDTH || y + DEF_BL_SIZE > DEF_IM_HEIGHT)
    {
        printf("Wrong OFFSET!\n");
        exit(1);
    }

    for(i = 0; i < DEF_BL_SIZE; i++)
    {
        for(j = 0; j < DEF_BL_SIZE; j++)
        {
            R(IM[y + i][x + j]) = 0;
            G(IM[y + i][x + j]) = 0;
            B(IM[y + i][x + j]) = 0;
        }
    }

    return 0;
}

int setall(void)
{
    size_t i, j;

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        for(j = 0; j < DEF_IM_WIDTH; j++)
        {
            R(IM[i][j]) = 0;
            G(IM[i][j]) = 0;
            B(IM[i][j]) = 0;
        }
    }

    // for(i = 0; i < DEF_BL_LEN; i++)
    // {
    //     BLOCK[i] = 0;
    // }

    for(i = 0; i < COMP_LEN * 2; i++)
    {
        COMP_BLOCK[i] = 0;
        DECOMP_BLOCK[i] = 125;
    }

    return 0;
}

void print_bits(uchar x)
{
    size_t i;
    int len = sizeof(uchar) * 8;
    int bit_str[len];

    for(i = 0; i < len; i++)
    {
        bit_str[i] = x & 0x01;
        x >>= 1;
    }

    for(i = 1; i <= len; i++)
    {
        printf("%d", bit_str[len - i]);
    }
    printf("\n");
}
