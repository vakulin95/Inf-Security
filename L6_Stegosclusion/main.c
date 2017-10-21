#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <math.h>
#include <string.h>

#define DEF_PATH            "files/"
#define DEF_PATH_STR_LEN    125

#define DEF_IM_WIDTH        512
#define DEF_IM_HEIGHT       DEF_IM_WIDTH // 512
#define DEF_IM_QUALITY      75
#define DEF_IM_DIM          3

#define DEF_BL_SIZE         64
#define DEF_PHB1_SIZE       32
#define DEF_PHB2_SIZE       8
#define DEF_NOF_BL          DEF_IM_WIDTH / DEF_BL_SIZE

#define R(X)                (X[0])
#define G(X)                (X[1])
#define B(X)                (X[2])

unsigned char IM[DEF_IM_WIDTH][DEF_IM_HEIGHT][DEF_IM_DIM];
unsigned char BLOCK[DEF_BL_SIZE][DEF_BL_SIZE][DEF_IM_DIM];
unsigned char PHASH[DEF_PHB2_SIZE * DEF_PHB2_SIZE];

int load_jpg(char *filename);
void write_jpg(char *filename);
void init_block(size_t x, size_t y);
void clean_block(void);
float pool(size_t I, size_t J);
void pHash(void);
void dct(float **DCTMatrix, float **Matrix, int N, int M);
void encrypt(void);

int main(void)
{
    size_t i, j;

    load_jpg("in.jpg");

    encrypt();

    write_jpg("out.jpg");

    return 0;
}

void encrypt(void)
{
    size_t i;
    int hlen;

    hlen = DEF_PHB2_SIZE * DEF_PHB2_SIZE;

    init_block(0, 32);
    memset(PHASH, 0, hlen);
    pHash();


    for(i = 0; i < hlen; i++)
    {
        printf("%d", PHASH[i]);
    }

    printf("\nencrypt finished\n");
    getchar();
}

int load_jpg(char  *filename)
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
        printf("load_jpg(): Image size!\n");
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
            IM[i][j][0] = pBuf[j*Y.num_components + 0];
            IM[i][j][1] = pBuf[j*Y.num_components + 1];
            IM[i][j][2] = pBuf[j*Y.num_components + 2];
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
        row_pointer[0] = (JSAMPLE *)(IM[i]);
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
        i++;
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
}

void init_block(size_t x, size_t y)
{
    size_t i, j;

    for (i = 0; i < DEF_BL_SIZE; i++)
    {
        for(j = 0; j < DEF_BL_SIZE; j++)
        {
            R(BLOCK[i][j]) = R(IM[x + i][y + j]);
            G(BLOCK[i][j]) = G(IM[x + i][y + j]);
            B(BLOCK[i][j]) = B(IM[x + i][y + j]);
        }
    }
}

void clean_block(void)
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
}

float pool(size_t I, size_t J)
{
    size_t i, j;
    unsigned char tR, tG, tB;
    unsigned char R[DEF_IM_DIM];
    int scale;
    float avg;

    tR = 0;
    tG = 0;
    tB = 0;
    scale = DEF_BL_SIZE / DEF_PHB1_SIZE;
    for(i = I; i < I + scale; i++)
    {
        for(j = J; j < J + scale; j++)
        {
            tR += R(BLOCK[i][j]);
            tG += G(BLOCK[i][j]);
            tB += B(BLOCK[i][j]);
        }
    }
    R(R) = tR / scale;
    G(R) = tG / scale;
    B(R) = tB / scale;

    // Приведение к яркостному представлению
    avg = (R(R) + G(R) + B(R)) / DEF_IM_DIM;

    return avg;
}

void pHash(void)
{
    size_t i, j;
    float **PHB_32, **DCT;
    float P, avg;
    int scale;

    PHB_32 = (float**)malloc(sizeof(float*) * DEF_PHB1_SIZE);
    DCT = (float**)malloc(sizeof(float*) * DEF_PHB1_SIZE);

    for(i = 0 ; i < DEF_PHB1_SIZE; i++)
    {
        PHB_32[i] = (float*)malloc(sizeof(float) * DEF_PHB1_SIZE);
        DCT[i] = (float*)malloc(sizeof(float) * DEF_PHB1_SIZE);
    }

    // Масштабирование
    scale = DEF_BL_SIZE / DEF_PHB1_SIZE;
    for(i = 0; i < DEF_PHB1_SIZE; i++)
    {
        for(j = 0; j < DEF_PHB1_SIZE; j++)
        {
            P = pool(i*scale, j*scale);
            PHB_32[i][j] = P;
        }
    }

    dct(DCT, PHB_32, DEF_PHB1_SIZE, DEF_PHB1_SIZE);

    // Вычисление порога
    avg = 0;
    for(i = 0; i < DEF_PHB2_SIZE; i++)
    {
        for(j = 0; j < DEF_PHB2_SIZE; j++)
        {
            printf("%8.2f ", DCT[i][j]);
            avg += DCT[i][j];
        }
        printf("\n");
    }
    avg -= DCT[0][0];
    avg /= pow(DEF_PHB2_SIZE, 2);
    printf("%5.3f\n", avg);

    for(i = 0; i < DEF_PHB2_SIZE; i++)
    {
        for(j = 0; j < DEF_PHB2_SIZE; j++)
        {
            if(DCT[i][j] >= avg)
            {
                PHASH[i * DEF_PHB2_SIZE + j] = 1;
            }
            else
            {
                PHASH[i * DEF_PHB2_SIZE + j] = 0;
            }
        }
    }

    free(PHB_32);
    free(DCT);
}

void dct(float **DCTMatrix, float **Matrix, int N, int M)
{

    int i, j, u, v;
    for (u = 0; u < N; ++u)
    {
        for (v = 0; v < M; ++v)
        {
            DCTMatrix[u][v] = 0;
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    DCTMatrix[u][v] += Matrix[i][j] * cos(M_PI / ((float)N) * (i + 1. / 2.) * u) \
                    * cos(M_PI / ((float)M) * (j + 1. / 2.) * v);
                }
            }
        }
    }
 }
