#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <setjmp.h>

#define DEF_PATH            "files/"
#define DEF_PATH_STR_LEN    125

#define DEF_IM_WIDTH        400
#define DEF_IM_HEIGHT       400
#define DEF_IM_QUALITY      75

unsigned char T[DEF_IM_WIDTH][DEF_IM_HEIGHT][3];

typedef struct jpeg_decompress_struct JPG_DEC;

int read_jpg(unsigned char **pBuf);
int load_im_meta(int *w, int *h, int *n);
void load_im_mass(unsigned char **im);
void write_jpg(unsigned char *im, char *filename);

int main(void)
{
    int im_width, im_height, im_comp;
    unsigned char *im;

    im = (unsigned char *)malloc(load_im_meta(&im_width, &im_height, &im_comp));
    printf("%d %d %d\n", im_width, im_height, im_comp);
    load_im_mass(&im);



    write_jpg(im, "out.jpg");

    return 0;
}

int read_jpg(unsigned char **im)
{
    size_t i, j;
    struct jpeg_decompress_struct d1;
    struct jpeg_error_mgr m1;

    d1.err = jpeg_std_error (&m1);
    jpeg_create_decompress(&d1);
    FILE *f = fopen("files/in.jpg","rb");
    jpeg_stdio_src(&d1, f);
    jpeg_read_header(&d1, TRUE);

    int w,h;
    int n;
    w = d1.image_width;
    h = d1.image_height;
    n = d1.num_components;
    printf ("Passed %d x %d x %d.\n", w, h, n);

    int n_s = w * n; // RGB, num. of the samples
    unsigned char *pBuf;
    unsigned char aR,aG,aB;
    unsigned long sR = 0;
    unsigned long sG = 0;
    unsigned long sB = 0;

    pBuf = (unsigned char *)malloc(n_s * h);
    jpeg_start_decompress(&d1);
    i = 0;
    while (d1.output_scanline < d1.output_height)
    {
        // Получить экранную строку
        i += jpeg_read_scanlines(&d1,(JSAMPARRAY)&(pBuf),1);
        // for (j = 0; j < w; j++)
        // {
        //     sR += pBuf[j*n + 0];
        //     sG += pBuf[j*n + 1];
        //     sB += pBuf[j*n + 2];
        // }
    }
    // aR = sR/(w*h);
    // aG = sG/(w*h);
    // aB = sB/(w*h);
    //
    // printf("%02X %02X %02X\n",aR,aG,aB);
    jpeg_finish_decompress(&d1);
    jpeg_destroy_decompress(&d1);

    fclose(f);

    *im = pBuf;
    free(pBuf);

    return 0;
}

int load_im_meta(int *w, int *h, int *n)
{
    int retval;
    JPG_DEC Y;
    struct jpeg_error_mgr m1;

    Y.err = jpeg_std_error (&m1);
    jpeg_create_decompress(&Y);
    FILE *f = fopen("files/in.jpg","rb");
    jpeg_stdio_src(&Y, f);
    jpeg_read_header(&Y, TRUE);

    *w = Y.image_width;
    *h = Y.image_height;
    *n = Y.num_components;

    retval = (*w) * (*h) * (*n);

    jpeg_destroy_decompress(&Y);

    fclose(f);

    return retval;
}

void load_im_mass(unsigned char **im)
{
    JPG_DEC Y;
    size_t i, j, k;

    struct jpeg_error_mgr m1;

    Y.err = jpeg_std_error (&m1);
    jpeg_create_decompress(&Y);

    FILE *f = fopen("files/in.jpg","rb");

    jpeg_stdio_src(&Y, f);
    jpeg_read_header(&Y, TRUE);

    jpeg_start_decompress(&Y);
    j = 0;
    while (Y.output_scanline < Y.output_height)
    {
        // Получить экранную строку
        jpeg_read_scanlines(&Y, (JSAMPARRAY)im, 1);
        for (i = 0; i < Y.image_width; i++)
        {
            T[j][i][0] = (*im)[i*Y.num_components + 0];
            T[j][i][1] = (*im)[i*Y.num_components + 1];
            T[j][i][2] = (*im)[i*Y.num_components + 2];
        }
        j++;
    }

    jpeg_finish_decompress(&Y);
    jpeg_destroy_decompress(&Y);

    fclose(f);
}

void write_jpg(unsigned char *scr, char *filename)
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
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, DEF_IM_QUALITY, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride;
    row_stride = cinfo.image_width*3;

    i = 0;
    while (cinfo.next_scanline < cinfo.image_height)
    {
        // row_pointer[0] = (JSAMPLE *)(scr+cinfo.next_scanline*row_stride);
        row_pointer[0] = (JSAMPLE *)(T[i]);
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
        i++;
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    free(scr);
}
