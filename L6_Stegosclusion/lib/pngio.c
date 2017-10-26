#include "pngio.h"

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

int load_png(char  *filename)
{
    size_t i, j;
    char header[8];    // 8 is the maximum size that can be checked
    char path[DEF_PATH_STR_LEN];

    sprintf(path, "%s%s", DEF_PATH, filename);

    /* open file and test for it being a png */
    FILE *fp = fopen(path, "rb");

    fread(header, 1, 8, fp);

    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    info_ptr = png_create_info_struct(png_ptr);

    setjmp(png_jmpbuf(png_ptr));

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    /* read file */
    setjmp(png_jmpbuf(png_ptr));

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (y = 0; y < height; y++)
    {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        png_byte* row = row_pointers[i];

        for (j = 0; j < DEF_IM_WIDTH; j++)
        {
            png_byte* ptr = &(row[j*4]);

            IM[i][j][0] = ptr[0];
            IM[i][j][1] = ptr[1];
            IM[i][j][2] = ptr[2];
        }
    }

    fclose(fp);

    return 0;
}

int write_png(char *filename)
{
    size_t i, j;

    /* create file */
    char path[DEF_PATH_STR_LEN];

    sprintf(path, "%s%s", DEF_PATH, filename);

    FILE *fp = fopen(path, "wb");

    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    info_ptr = png_create_info_struct(png_ptr);

    setjmp(png_jmpbuf(png_ptr));

    png_init_io(png_ptr, fp);

    /* write header */
    setjmp(png_jmpbuf(png_ptr));

    png_set_IHDR(png_ptr, info_ptr, width, height,
    bit_depth, color_type, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        png_byte* row = row_pointers[i];

        for (j = 0; j < DEF_IM_WIDTH; j++)
        {
            png_byte* ptr = &(row[j*4]);

            ptr[0] = IM[i][j][0];
            ptr[1] = IM[i][j][1];
            ptr[2] = IM[i][j][2];
        }
    }

    /* write bytes */
    setjmp(png_jmpbuf(png_ptr));

    png_write_image(png_ptr, row_pointers);

    /* end write */
    setjmp(png_jmpbuf(png_ptr));

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);

    return 0;
}
