#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define DEF_ROUNDS              10
#define DEF_MES_LEN             64
#define DEF_NUM_OF_PARTS        4

#define GET_BIT(X, NUM)         (( (X) & ( (int64)(1) << (NUM) )) >> (NUM) )
#define GET_PART(X, NUM)        ((int16)( (X) >> (NUM) * 16))
#define SET_PART(X, PART, NUM)  ((int64)(PART) << 16 * (NUM)) | (int64)(X)
#define MOOVE_R_B(X, Y)         (( (X) >> (Y) ) | ( (X) << ( (Y) & (int32)(15) )))
#define MOOVE_L_B(X, Y)         (( (X) << (Y) ) | ( (X) >> ( (Y) & (int32)(15) )))

typedef unsigned short int      int16;
typedef unsigned int            int32;
typedef unsigned long long int  int64;

int16 KEYS[DEF_ROUNDS];
char BIN[DEF_MES_LEN];

int GetKeys(void);
int64 Merge(int16 *part);
int16 EncryptFunction(int16 *part, int16 key);
int64 Encode(int64 message, int keysCount);
int64 Decode(int64 message, int keysCount);
void bits_to_str(int64 N);
void print_b(char str[255], int N);

int main()
{
    int64 a = 880035355599669969;

    bits_to_str(a);
    printf("Input: \t\t%.*s\n", DEF_MES_LEN, BIN);

	a = Encode(a, DEF_ROUNDS);

    bits_to_str(a);
    printf("Encode: \t%.*s\n", DEF_MES_LEN, BIN);

	a = Decode(a, DEF_ROUNDS);

    bits_to_str(a);
    printf("Decode: \t%.*s\n", DEF_MES_LEN, BIN);

    return 0;
}

int GetKeys(void)
{
    int i;

	srand(time(0));

	for(i = 0; i < DEF_ROUNDS - 1; i++)
	{
        KEYS[i] = MOOVE_R_B((int16)rand(), i * 8);
	}

	return 0;
}

int64 Merge(int16 *part)
{
    int i;
    int64 Y = 0;

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        Y = SET_PART(Y, part[i], i);
    }

    return Y;
}

int16 EncryptFunction(int16 *part, int16 key)
{
    int16 Y;

    Y = MOOVE_L_B(part[0], 9) ^ MOOVE_L_B(part[1], 9) ^ MOOVE_L_B(part[2], 9) ^ \
    (~(MOOVE_R_B(key, 11) ^ part[0] ^ part[1] ^ part[2]));

    return Y;
}

int64 Encode(int64 message, int keysCount)
{
    int i;
    int16 P[DEF_NUM_OF_PARTS];
    int16 tmp;

	GetKeys();

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        P[i] = GET_PART(message, i);
    }

	for (i = 0; i < DEF_ROUNDS; i++)
	{
		tmp = EncryptFunction(P, KEYS[i]) ^ P[3];

        if (i != DEF_ROUNDS - 1)
        {
            P[3] = P[0];
            P[0] = P[1];
            P[1] = P[2];
            P[2] = tmp;
		}
		else
        {
            P[3] = tmp;
		}

	}

	return Merge(P);
}

int64 Decode(int64 message, int keysCount)
{
    int i;
    int16 P[DEF_NUM_OF_PARTS];
    int16 tmp;

	GetKeys();

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        P[i] = GET_PART(message, i);
    }

	for (i = DEF_ROUNDS - 1; i >= 0; i--)
	{
		tmp = EncryptFunction(P, KEYS[i]) ^ P[3];

		if (i != 0)
        {
            P[3] = P[2];
            P[2] = P[1];
            P[1] = P[0];
            P[0] = tmp;
		}
		else
        {
            P[3] = tmp;
		}

	}

	return Merge(P);
}

void bits_to_str(int64 N)
{
    int i;

    for(i = 0; i < DEF_MES_LEN; i++)
    {
        BIN[DEF_MES_LEN - i - 1] = GET_BIT(N, i) + '0';
    }

    return;
}

void print_b(char str[255], int N)
{
    int i;
    printf("%s", str);

    for(i = sizeof(N) * 8 - 1; i >= 0; i--)
    {
        printf("%c", GET_BIT(N, i) + '0');
    }
    printf("\n");

    return;
}
