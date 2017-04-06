#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define DEF_ROUNDS 250
#define DEF_MES_LEN 64
#define GET_BIT(N, K) ((N & ((long long int)1 << K)) >> K)

typedef unsigned short int      int16;
typedef unsigned int            int32;
typedef unsigned long long int  int64;

int16 KEYS[DEF_ROUNDS];
char BIN[DEF_MES_LEN];

int16 RotLeft16(int16 n, int32 c);
int16 RotRight16(int16 n, int32 c);
int GetKeys(void);
int16 GetBlock(int64 num, int32 block);
int64 Merge(int16 b0, int16 b1, int16 b2, int16 b3);
int32 EncryptFunction(int16 num0, int16 num1, int16 num2, int16 key);
int64 Encode(int64 num, int keysCount);
int64 Decode(int64 num, int keysCount);
void bits_to_str(int64 N);

int main()
{
    unsigned long long int a = 880035355599669969;

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

int16 RotLeft16(int16 n, int32 c)
{
	const unsigned int mask = (8*sizeof(n) - 1);
	c &= mask;
	return (n << c) | (n >> ((c)&mask));
}

int16 RotRight16(int16 n, int32 c)
{
	const unsigned int mask = (8*sizeof(n) - 1);
	c &= mask;
	return (n >> c) | (n << ((c)&mask));
}

int GetKeys(void)
{
    int i;

	srand(time(0));

	for(i = 0; i < DEF_ROUNDS - 1; i++)
	{
		KEYS[i] = RotRight16((int16)rand(), i * 8);
	}

	return 0;
}

int16 GetBlock(int64 num, int32 block)
{
	return (int16)(num >> block * 16);
}

int64 Merge(int16 b0, int16 b1, int16 b2, int16 b3)
{
	return (int64)b0 << 16 * 0 | (int64)b1 << 16 * 1 | (int64)b2 << 16 * 2 | (int64)b3 << 16 * 3;
}

int32 EncryptFunction(int16 num0, int16 num1, int16 num2, int16 key)
{
	return RotLeft16(num0, 9) ^ RotLeft16(num1, 9) ^ RotLeft16(num2, 9) ^ (~(RotRight16(key, 11) ^ num0 ^ num1 ^ num2));
}

int64 Encode(int64 num, int keysCount)
{
    int i;
    int16 tmp;

	GetKeys();

	int16 b0 = GetBlock(num, 0);
	int16 b1 = GetBlock(num, 1);
	int16 b2 = GetBlock(num, 2);
	int16 b3 = GetBlock(num, 3);

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

	int16 b0 = GetBlock(num, 0);
	int16 b1 = GetBlock(num, 1);
	int16 b2 = GetBlock(num, 2);
	int16 b3 = GetBlock(num, 3);

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
