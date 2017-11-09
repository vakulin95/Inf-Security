#include "enct.h"
#include "feistel.h"

int encrypt(void)
{
    size_t i, j, k;
    int64 mes, enc;
    uchar *buf;

    init_block(DEF_X_OFFSET, DEF_Y_OFFSET);

    COMP_LEN = mcompress();

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

    lsb(DEF_K2_LSB);

    set_block(DEF_X_OFFSET, DEF_Y_OFFSET);

    free(buf);

    return 0;
}

int lsb(int key)
{
    size_t i, j, k, p;

    p = 0;
    for(i = 0; i < DEF_IM_HEIGHT; i += key)
    {
        for(j = 0; j < DEF_IM_WIDTH; j += key)
        {
            for(k = 0; k < DEF_IM_NOFC; k++)
            {
                if((i > DEF_Y_OFFSET - 2 * key && i < DEF_Y_OFFSET + DEF_BL_SIZE + 2 * key) \
                && (j > DEF_X_OFFSET - 2 * key && j < DEF_X_OFFSET + DEF_BL_SIZE + 2 * key))
                {
                    continue;
                }

                if(p < COMP_LEN - 1)
                {
                    (COMP_BLOCK[p++]) ? ON_K_BIT(IM[i][j][k], 2) : OFF_K_BIT(IM[i][j][k], 2);
                    (COMP_BLOCK[p++]) ? ON_K_BIT(IM[i][j][k], 1) : OFF_K_BIT(IM[i][j][k], 1);
                }
                else
                {
                    i = DEF_IM_HEIGHT;
                    j = DEF_IM_WIDTH;
                    k = DEF_IM_NOFC;
                }
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
    uInt len;

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    // setup "a" as the input and "b" as the compressed output
    defstream.avail_in = (uInt)(DEF_BL_SIZE * DEF_BL_SIZE * DEF_IM_NOFC); // size of input, string + terminator
    defstream.next_in = (Bytef *)BLOCK; // input char array
    defstream.avail_out = (uInt)(sizeof(COMP_BLOCK)); // size of output
    defstream.next_out = (Bytef *)COMP_BLOCK; // output char array

    deflateInit2(&defstream, Z_BEST_COMPRESSION, Z_DEFLATED, 8, 1, 4);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    len = defstream.avail_out;
    if(defstream.avail_out % 8)
    {
        len = defstream.avail_out + (8 - (defstream.avail_out % 8));
        for(i = defstream.avail_out; i < len; i++)
        {
            COMP_BLOCK[i] = 0;
        }
    }

    printf("Input size is:\t\t%lu\n", sizeof(BLOCK));
    printf("Compressed size is:\t%u\n", len);
    printf("\n----------\n");

    return len;
}

void mdecompress(void)
{
    size_t i;

    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    // setup "b" as the input and "c" as the compressed output
    infstream.avail_in = sizeof(COMP_BLOCK); // size of input
    infstream.next_in = (Bytef *)COMP_BLOCK; // input char array
    infstream.avail_out = (uInt)(sizeof(DECOMP_BLOCK)); // size of output
    infstream.next_out = (Bytef *)DECOMP_BLOCK; // output char array

    // the actual DE-compression work.
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);

    printf("Uncompressed size is:\t%u\n", infstream.avail_out);
    for(i = 0; i < DEF_BL_SIZE * DEF_BL_SIZE * DEF_IM_NOFC; i++)
    {
        // printf("%zu\t- %d | %d\n", i, BLOCK[i], DECOMP_BLOCK[i]);
        if(BLOCK[i] != DECOMP_BLOCK[i])
        {
            printf("FALSE!\n");
            exit(1);
        }
    }
    printf("\n----------\n\n");
}

int init_block(size_t x, size_t y)
{
    size_t i, j, k;

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

    for(i = 0; i < DEF_BL_LEN; i++)
    {
        BLOCK[i] = 0;
    }

    for(i = 0; i < DEF_BL_LEN * 2; i++)
    {
        COMP_BLOCK[i] = 0;
        DECOMP_BLOCK[i] = 0;
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
