#include "feistel.h"

int64 fl_hide(int64 message)
{
    int i;
    int16 P[DEF_NUM_OF_PARTS], F;

	cr_keys();

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        P[i] = GET_PART(message, i);
    }

	for (i = 0; i < DEF_ROUNDS - 1; i++)
	{
		F = gen_func(P, KEYS[i]) ^ P[1];

        P[1] = P[2];
        P[2] = P[3];
        P[3] = P[0];
        P[0] = F;
	}

    F = gen_func(P, KEYS[DEF_ROUNDS - 1]) ^ P[1];
    P[1] = F;

	return join_parts(P);
}

int64 fl_show(int64 message)
{
    int i;
    int16 P[DEF_NUM_OF_PARTS];
    int16 F;

    for(i = 0; i < DEF_NUM_OF_PARTS; i++)
    {
        P[i] = GET_PART(message, i);
    }

	for (i = DEF_ROUNDS - 1; i > 0; i--)
	{
		F = gen_func(P, KEYS[i]) ^ P[1];

        P[1] = P[0];
        P[0] = P[3];
        P[3] = P[2];
        P[2] = F;
	}

    F = gen_func(P, KEYS[0]) ^ P[1];
    P[1] = F;

	return join_parts(P);
}

void CBCencode(int64 *data, int64 **out)
{
    int i;
    int64 init;

    cr_init_vect();

    for (i = 0; i < DEF_NUM_OF_CBC_PARTS; i++)
	{
		if (i == 0)
		{
			init = INIT_VECT;
		}
		else
		{
			init = (*out)[i - 1];
		}

		(*out)[i] = fl_hide(data[i] ^ init);
	}

	return;
}

void CBCdecode(int64 *data, int64 **out)
{
    int i;
    int64 init;

	for (i = DEF_NUM_OF_CBC_PARTS - 1; i >= 0; i--)
    {
		if (i == 0)
		{
			init = INIT_VECT;
		}
		else
		{
			init = data[i - 1];
		}

		(*out)[i] = fl_show(data[i]) ^ init;
	}

	return;
}


int64 conv_str(char str[DEF_MES_LEN])
{
    int i;
    int64 Y = 0;

    for(i = 0; i < DEF_MES_LEN; i++)
    {
        Y = (Y << 8) | (int64)(str[i]);
    }

    return Y;
}

void conv_int(int64 X, char **str)
{
    int i;

    for(i = 0; i < DEF_MES_LEN; i++)
    {
        (*str)[DEF_MES_LEN - i - 1] = (char)(X >> (i * 8));
    }

    return;
}

void cr_init_vect(void)
{
    srand(time(0));

    INIT_VECT = (int64)rand();

    return;
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

    Y = MOOVE_L_B(part[0], 9) ^ (~(MOOVE_R_B(key, 11) ^ part[0]));

    return Y;
}

void printb(char str[255], int64 *N)
{
    int p, i;
    printf("%s", str);

    for(p = 0; p < DEF_NUM_OF_CBC_PARTS; p++)
    {
        for(i = sizeof(N) * 8 - 1; i >= 0; i--)
        {
            printf("%c", GET_BIT(N[p], i) + '0');
        }
        printf("\n");
    }
    printf("\n");

    return;
}
