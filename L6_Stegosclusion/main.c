#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <setjmp.h>

#define DEF_PATH            "files/"
#define DEF_PATH_STR_LEN    125

#define DEF_IM_WIDTH        400
#define DEF_IM_HEIGHT       400
#define DEF_IM_QUALITY      75
#define DEF_IM_DIM          3

unsigned char T[DEF_IM_WIDTH][DEF_IM_HEIGHT][DEF_IM_DIM];

int load_im_mass(char *filename);
void write_jpg(char *filename);

int main(void)
{
    size_t i, j;

    load_im_mass("in1.jpg");
    write_jpg("out.jpg");

    return 0;
}

int load_im_mass(char  *filename)
{
    size_t i, j;
    unsigned char *pBuf;
    char path[DEF_PATH_STR_LEN];

    struct jpeg_decompress_struct Y;
    struct jpeg_error_mgr m1;

    Y.err = jpeg_std_error (&m1);
    jpeg_create_decompress(&Y);

    sprintf(path, "%s%s", DEF_PATH, filename);

    FILE *f = fopen(path,"rb");

    jpeg_stdio_src(&Y, f);
    jpeg_read_header(&Y, TRUE);

    if(Y.image_width != DEF_IM_WIDTH || Y.image_height != DEF_IM_HEIGHT || Y.num_components != DEF_IM_DIM)
    {
        printf("load_im_mass(): Image size!\n");
        getchar();
        return 1;
    }

    jpeg_start_decompress(&Y);
    i = 0;
    pBuf = (unsigned char *)malloc(DEF_IM_HEIGHT * DEF_IM_WIDTH * DEF_IM_DIM);
    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        // Получить экранную строку
        jpeg_read_scanlines(&Y, (JSAMPARRAY)&(pBuf), 1);
        for (j = 0; j < DEF_IM_WIDTH; j++)
        {
            T[i][j][0] = pBuf[j*Y.num_components + 0];
            T[i][j][1] = pBuf[j*Y.num_components + 1];
            T[i][j][2] = pBuf[j*Y.num_components + 2];
        }
        // i++;
    }

    jpeg_finish_decompress(&Y);
    jpeg_destroy_decompress(&Y);
    free(pBuf);

    fclose(f);

    return 0;
}

void write_jpg(char *filename)
{
    FILE *out;
    char path[DEF_PATH_STR_LEN];
    size_t i;

    sprintf(path, "%s%s", DEF_PATH, filename);

    out = fopen(path, "w");

    /* Compress to JPEG */
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    jpeg_stdio_dest(&cinfo, out);

    cinfo.image_width = DEF_IM_WIDTH;
    cinfo.image_height = DEF_IM_HEIGHT;
    cinfo.input_components = DEF_IM_DIM;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, DEF_IM_QUALITY, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride;
    row_stride = cinfo.image_width*DEF_IM_DIM;

    i = 0;
    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = (JSAMPLE *)(T[i]);
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
        i++;
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
}