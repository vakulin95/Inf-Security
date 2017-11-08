#include "enct.h"

#include "zlib.h"

uInt mcompress(void)
{
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    // setup "a" as the input and "b" as the compressed output
    defstream.avail_in = (uInt)(DEF_BL_SIZE * DEF_BL_SIZE * DEF_IM_NOFC); // size of input, string + terminator
    defstream.next_in = (Bytef *)BLOCK1; // input char array
    defstream.avail_out = (uInt)(sizeof(COMP_BLOCK)); // size of output
    defstream.next_out = (Bytef *)COMP_BLOCK; // output char array

    deflateInit2(&defstream, Z_BEST_COMPRESSION, Z_DEFLATED, 8, 1, 4);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    printf("Input size is:\t\t%lu\n", sizeof(BLOCK1));
    printf("Compressed size is:\t%u\n", defstream.avail_out);
    printf("\n----------\n\n");

    return defstream.avail_out;
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
        // printf("%zu\t- %d | %d\n", i, BLOCK1[i], DECOMP_BLOCK[i]);
        if(BLOCK1[i] != DECOMP_BLOCK[i])
        {
            printf("FALSE!\n");
            exit(1);
        }
    }
    printf("\n----------\n\n");
}

int encrypt(void)
{
    size_t i, j, k;
    uInt len;

    init_block(DEF_X_OFFSET, DEF_Y_OFFSET);

    len = mcompress();
    mdecompress();

    for (i = 0; i < DEF_BL_SIZE; i++)
    {
        for(j = 0; j < DEF_BL_SIZE; j++)
        {
            R(BLOCK[i][j]) = 0;
            G(BLOCK[i][j]) = 0;
            B(BLOCK[i][j]) = 0;

            // R(BLOCK[i][j]) = DECOMP_BLOCK[i * DEF_BL_SIZE + j];
            // G(BLOCK[i][j]) = DECOMP_BLOCK[i * DEF_BL_SIZE + j + DEF_BL_SIZE * DEF_BL_SIZE];
            // B(BLOCK[i][j]) = DECOMP_BLOCK[i * DEF_BL_SIZE + j + 2 * DEF_BL_SIZE * DEF_BL_SIZE];
        }
    }

    set_block(DEF_X_OFFSET, DEF_Y_OFFSET);

    return 0;
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
            R(BLOCK[i][j]) = R(IM[y + i][x + j]);
            G(BLOCK[i][j]) = G(IM[y + i][x + j]);
            B(BLOCK[i][j]) = B(IM[y + i][x + j]);

            BLOCK1[i * DEF_BL_SIZE + j]                     = R(IM[y + i][x + j]);
            BLOCK1[i * DEF_BL_SIZE + j + DEF_BL_SIZE * DEF_BL_SIZE]       = G(IM[y + i][x + j]);
            BLOCK1[i * DEF_BL_SIZE + j + 2 * DEF_BL_SIZE * DEF_BL_SIZE]   = B(IM[y + i][x + j]);
            // printf("%zu %zu %zu\n", i * DEF_BL_SIZE + j, i * DEF_BL_SIZE + j + DEF_BL_SIZE * DEF_BL_SIZE, i * DEF_BL_SIZE + j + 2 * DEF_BL_SIZE * DEF_BL_SIZE);
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
            R(IM[y + i][x + j]) = R(BLOCK[i][j]);
            G(IM[y + i][x + j]) = G(BLOCK[i][j]);
            B(IM[y + i][x + j]) = B(BLOCK[i][j]);
        }
    }

    return 0;
}

int clean_block(void)
{
    size_t i, j;

    for(i = 0; i < DEF_BL_SIZE; i++)
    {
        for(j = 0; j < DEF_BL_SIZE; j++)
        {
            R(BLOCK[i][j]) = 0;
            G(BLOCK[i][j]) = 0;
            B(BLOCK[i][j]) = 0;
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

    clean_block();

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
