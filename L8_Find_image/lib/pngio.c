#include "pngio.h"

int load_png(char  *filename)
{
    size_t i, j;
    char path[DEF_PATH_STR_LEN];

    png_bytep * row_pointers;
    png_structp png_ptr;
    png_infop info_ptr;

    sprintf(path, "%s%s", DEF_PATH, filename);
    FILE *fp = fopen(path, "rb");

    fseek(fp, 8, SEEK_CUR);

    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);

    setjmp(png_jmpbuf(png_ptr));

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB)
    {
        printf("load_png(): invalid num of components!\n");
        return 1;
    }

    if(png_get_image_width(png_ptr, info_ptr) != DEF_IM_WIDTH || png_get_image_height(png_ptr, info_ptr) != DEF_IM_HEIGHT)
    {
        printf("load_png(): invalid image size!\n");
        return 1;
    }

    png_read_update_info(png_ptr, info_ptr);

    /* read file */
    setjmp(png_jmpbuf(png_ptr));

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * DEF_IM_HEIGHT);
    for (i = 0; i < DEF_IM_HEIGHT; i++)
    {
        row_pointers[i] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        png_byte* row = row_pointers[i];

        for (j = 0; j < DEF_IM_WIDTH; j++)
        {
            png_byte* ptr = &(row[j * DEF_IM_NOFC]);

            IM[i][j][0] = ptr[0];
            IM[i][j][1] = ptr[1];
            IM[i][j][2] = ptr[2];
        }
    }

    /* cleanup heap allocation */
    for (i = 0; i < DEF_IM_HEIGHT; i++)
    {
        free(row_pointers[i]);
    }
    free(row_pointers);

    fclose(fp);

    return 0;
}

int write_png(char *filename)
{
    size_t i, j;
    char path[DEF_PATH_STR_LEN];

    png_bytep * row_pointers;
    png_structp png_ptr;
    png_infop info_ptr;

    sprintf(path, "%s%s", DEF_PATH, filename);
    FILE *fp = fopen(path, "wb");

    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);

    setjmp(png_jmpbuf(png_ptr));

    png_init_io(png_ptr, fp);

    /* write header */
    setjmp(png_jmpbuf(png_ptr));

    png_set_IHDR(png_ptr, info_ptr, DEF_IM_WIDTH, DEF_IM_HEIGHT,
    DEF_IM_BITD, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * DEF_IM_HEIGHT);
    for (i = 0; i < DEF_IM_HEIGHT; i++)
    {
        row_pointers[i] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        png_byte* row = row_pointers[i];

        for (j = 0; j < DEF_IM_WIDTH; j++)
        {
            png_byte* ptr = &(row[j * DEF_IM_NOFC]);

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
    for (i = 0; i < DEF_IM_HEIGHT; i++)
    {
        free(row_pointers[i]);
    }
    free(row_pointers);

    fclose(fp);

    return 0;
}
