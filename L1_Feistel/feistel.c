#include "feistel.h"

int64 fl_hide(int64 message)
{
    int i;
    int16 P[DEF_NUM_OF_PARTS];
    int16 tmp;

	cr_keys();

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        P[i] = GET_PART(message, i);
    }

	for (i = 0; i < DEF_ROUNDS; i++)
	{
		tmp = gen_func(P, KEYS[i]) ^ P[3];

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

	return join_parts(P);
}

int64 fl_show(int64 message)
{
    int i;
    int16 P[DEF_NUM_OF_PARTS];
    int16 tmp;

	cr_keys();

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        P[i] = GET_PART(message, i);
    }

	for (i = DEF_ROUNDS - 1; i >= 0; i--)
	{
		tmp = gen_func(P, KEYS[i]) ^ P[3];

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

	return join_parts(P);
}

int conv_str(char str[DEF_MES_LEN])
{
    int i;
    int Y = 0;

    for(i = 0; i < DEF_MES_LEN; i++)
    {
        //Y = 
    }

    return Y;
}

void cr_keys(void)
{
    int i;

    srand(time(0));

	for(i = 0; i < DEF_ROUNDS - 1; i++)
	{
        KEYS[i] = MOOVE_R_B((int16)rand(), i * 8);
	}

	return;
}

int64 join_parts(int16 *part)
{
    int i;
    int64 Y = 0;

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        Y = SET_PART(Y, part[i], i);
    }

    return Y;
}

int16 gen_func(int16 *part, int16 key)
{
    int16 Y;

    Y = MOOVE_L_B(part[0], 9) ^ MOOVE_L_B(part[1], 9) ^ MOOVE_L_B(part[2], 9) ^ \
    (~(MOOVE_R_B(key, 11) ^ part[0] ^ part[1] ^ part[2]));

    return Y;
}

void printb(char str[255], int64 N)
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
