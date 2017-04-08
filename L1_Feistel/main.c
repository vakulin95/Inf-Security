#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define DEF_ROUNDS          10
#define DEF_MES_LEN         64

#define GET_BIT(X, NUM)         (( (X) & ( (int64)(1) << (NUM) )) >> (NUM) )
#define GET_PART(X, NUM)        ((int16)( (X) >> (NUM) * 16))
#define SET_PART(X, PART, NUM)  (((int64)(PART) << 16 * (NUM)) | (int64)(X) )
#define MOOVE_R_B(X, Y)         (( (X) >> (Y) ) | ( (X) << ( (Y) & (int32)(15) )))
#define MOOVE_L_B(X, Y)         (( (X) << (Y) ) | ( (X) >> ( (Y) & (int32)(15) )))

typedef unsigned short int      int16;
typedef unsigned int            int32;
typedef unsigned long long int  int64;

int16 KEYS[DEF_ROUNDS];
char BIN[DEF_MES_LEN];

int GetKeys(void);
int64 Merge(int16 b0, int16 b1, int16 b2, int16 b3);
int32 EncryptFunction(int16 num0, int16 num1, int16 num2, int16 key);
int64 Encode(int64 num, int keysCount);
int64 Decode(int64 num, int keysCount);
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

int64 Merge(int16 b0, int16 b1, int16 b2, int16 b3)
{
    int i;
    int64 Y = 0;

    // for(i = 0; i < 4; i++)
    // {
    //     SET_PART(Y, )
    // }

	return (int64)b0 << 16 * 0 | (int64)b1 << 16 * 1 | (int64)b2 << 16 * 2 | (int64)b3 << 16 * 3;
}

int32 EncryptFunction(int16 num0, int16 num1, int16 num2, int16 key)
{
	return MOOVE_L_B(num0, 9) ^ MOOVE_L_B(num1, 9) ^ MOOVE_L_B(num2, 9) ^ (~(MOOVE_R_B(key, 11) ^ num0 ^ num1 ^ num2));
}

int64 Encode(int64 num, int keysCount)
{
    int i;
    int16 tmp;

	GetKeys();

	int16 b0 = GET_PART(num, 0);
	int16 b1 = GET_PART(num, 1);
	int16 b2 = GET_PART(num, 2);
	int16 b3 = GET_PART(num, 3);

	for (i = 0; i < DEF_ROUNDS; i++)
	{
		tmp = EncryptFunction(b0, b1, b2, KEYS[i]) ^ b3;
		if (i != DEF_ROUNDS - 1)
        {
			b3 = b0;
			b0 = b1;
			b1 = b2;
			b2 = tmp;
		}
		else
        {
			b3 = tmp;
		}

	}

	return Merge(b0, b1, b2, b3);
}

int64 Decode(int64 num, int keysCount)
{
    int i;
    int16 tmp;

	GetKeys();

	int16 b0 = GET_PART(num, 0);
	int16 b1 = GET_PART(num, 1);
	int16 b2 = GET_PART(num, 2);
	int16 b3 = GET_PART(num, 3);

	for (i = DEF_ROUNDS - 1; i >= 0; i--)
	{
		tmp = EncryptFunction(b0, b1, b2, KEYS[i]) ^ b3;

		if (i != 0)
        {
			b3 = b2;
			b2 = b1;
			b1 = b0;
			b0 = tmp;
		}
		else
        {
			b3 = tmp;
		}

	}

	return Merge(b0, b1, b2, b3);
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
