#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

int main(void)
{
    printf("Content-Type: image/jpeg\n\n");

    FILE *out;

    out = fopen("out.jpeg", "w");

    int width=400;
    int height=400;
    int quality=75;
    char *scr=(char*)malloc(width*height*3);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            char *p = scr + (j*width + i) * 3;
            *p = i + j;
            p++;
            *p = i - j;
            p++;
            *p = i*j;
        }
    }


    /* Compress to JPEG */
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    jpeg_stdio_dest(&cinfo, out);

    cinfo.image_width=width;
    cinfo.image_height=height;
    cinfo.input_components=3;
    cinfo.in_color_space=JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride;
    row_stride = cinfo.image_width*3;

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0]=(JSAMPLE *)(scr+cinfo.next_scanline*row_stride);
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    free(scr);
}
