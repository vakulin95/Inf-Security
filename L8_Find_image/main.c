#include "lib/meta.h"
#include "lib/pngio.h"

int get_mass(char *filename);
int get_image(void);
size_t reverse_bits(size_t ind);

int main(int argc, char *argv[])
{
    printf("\n----------------------------------------------------------\n\n");

    get_mass("out.dat");
    get_image();

    write_png(DEF_ENCFILE);

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}

int get_mass(char *filename)
{
    size_t i, j;
    char path[DEF_PATH_STR_LEN];

    sprintf(path, "%s%s", DEF_PATH, filename);
    FILE *fp = fopen(path, "r");

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        for(j = 0; j < DEF_IM_HEIGHT; j++)
        {
            if(!fscanf(fp, "%lf   ", &K_IM[i][j]))
            {
                printf("get_mass(): error while reading file!\n");
                exit(1);
            }
        }
    }

    fclose(fp);

    return 0;
}

int get_image(void)
{
    size_t i, j, ti, tj;
    double max;

    uchar T_IM[DEF_IM_HEIGHT][DEF_IM_WIDTH];
    uchar RB_IM[DEF_IM_HEIGHT][DEF_IM_WIDTH];

    max = K_IM[0][0];
    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        for(j = 1; j < DEF_IM_WIDTH; j++)
        {
            if(K_IM[i][j] > max)
            {
                max = K_IM[i][j];
            }
        }
    }

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        for(j = 0; j < DEF_IM_WIDTH; j++)
        {
            T_IM[i][j] = (uchar)(K_IM[i][j] / max * 32);
        }
    }

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        for(j = 0; j < DEF_IM_WIDTH; j++)
        {
            ti = reverse_bits(i);
            tj = reverse_bits(j);
            RB_IM[ti][tj] = T_IM[i][j];
        }
    }

    for(i = 0; i < DEF_IM_HEIGHT; i++)
    {
        for(j = 0; j < DEF_IM_WIDTH; j++)
        {
            R(IM[i][j]) = RB_IM[i][j] * 10;
            G(IM[i][j]) = RB_IM[i][j] * 10;
            B(IM[i][j]) = RB_IM[i][j] * 10;
        }
    }

    return 0;
}

size_t reverse_bits(size_t ind)
{
    size_t Y;

    ind = ((ind >> 1) & 0x55555555) | ((ind & 0x55555555) << 1);
    // swap consecutiinde pairs
    ind = ((ind >> 2) & 0x33333333) | ((ind & 0x33333333) << 2);
    // swap nibbles ...
    ind = ((ind >> 4) & 0x0F0F0F0F) | ((ind & 0x0F0F0F0F) << 4);
    // swap bytes
    ind = ((ind >> 8) & 0x00FF00FF) | ((ind & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    ind = (ind >> 16) | (ind << 16);

    Y = ind >> 23;

    if(Y > DEF_IM_WIDTH || Y > DEF_IM_HEIGHT)
    {
        printf("reverse_bits(): index out of range!\n");
        exit(2);
    }

    return Y;
}
