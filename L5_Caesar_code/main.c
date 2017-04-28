#include "caes.h"

int count_letters(wchar_t x, int up);
void analize(void);
void swap(Letter *x1, Letter *x2);
void hack(void);
int find_in_alph(wchar_t x, int up);

wchar_t TEXT[DEF_STR_LEN] = DEF_STR;
Letter alphabet[DEF_ALPH_LEN];
int T_LEN;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    T_LEN = wcslen(TEXT);

    printf("\n-----------------------------------------Caesar's code-----------------------------------------\n\n");

    //printf("%ls\n\n", TEXT);
    hack();
    printf("%ls\n", TEXT);

    printf("-----------------------------------------------------------------------------------------------\n");

    return 0;
}

int count_letters(wchar_t x, int up)
{
    int Y = 0;
    int i;
    if(up)
    {
        for(i = 0; i < T_LEN; i++)
        {
            if(TEXT[i] == x || TEXT[i] == _UPPERCASE(x))
            {
                Y++;
            }
        }
    }
    else
    {
        for(i = 0; i < T_LEN; i++)
        {
            if(TEXT[i] == x)
            {
                Y++;
            }
        }
    }


    return Y;
}

void analize(void)
{
    int i, j;
    int n_of_c_symb;
    wchar_t letter;
    wchar_t alf_buf[DEF_ALPH_LEN + 1] = DEF_ALPH_PROB;

    n_of_c_symb = 0;
    for(i = 0; i < T_LEN; i++)
    {
        if((TEXT[i] >= _L('А') && TEXT[i] <= _L('я')) || TEXT[i] <= _L('ё'))
        {
            n_of_c_symb++;
        }
    }

    letter = _L('а');
    for(i = 0; i < DEF_ALPH_LEN; i++)
    {
        if(i == 6)
        {
            alphabet[i].c_symb = _L('ё');
            alphabet[i].prob = (float)count_letters(_L('ё'), 0) / n_of_c_symb;
            continue;
        }

        alphabet[i].c_symb = letter;
        alphabet[i].prob = (float)count_letters(letter++, 1) / n_of_c_symb;
    }

    for(i = 0; i < DEF_ALPH_LEN; ++i)
    {
        for(j = DEF_ALPH_LEN - 1; j > i; --j)
        {
            if(alphabet[j].prob > alphabet[j - 1].prob)
                swap(alphabet + j, alphabet + (j - 1));
        }
    }

    for(i = 0; i < DEF_ALPH_LEN; i++)
    {
        alphabet[i].ec_symb = alf_buf[i];
    }

    for(i = 0; i < DEF_ALPH_LEN; i++)
    {
        printf("%lc - %f -> %lc\n", alphabet[i].c_symb, alphabet[i].prob, alphabet[i].ec_symb);
    }

    return;
}

void swap(Letter *x1, Letter *x2)
{
    Letter temp;

    temp.c_symb = x1->c_symb;
    temp.prob = x1->prob;

    x1->c_symb = x2->c_symb;
    x1->prob = x2->prob;

    x2->c_symb = temp.c_symb;
    x2->prob = temp.prob;
}

void hack(void)
{
    int i, ind;

    analize();

    for(i = 0; i < T_LEN; i++)
    {
        if(TEXT[i] == 'ё')
        {
            ind = find_in_alph(TEXT[i], 0);
        }
        else
        {
            ind = find_in_alph(TEXT[i], 1);
        }


        if(ind != -1)
        {
            TEXT[i] = alphabet[ind].ec_symb;
        }
    }

    return;
}

int find_in_alph(wchar_t x, int up)
{
    int Y = -1;
    int i;

    if(up)
    {
        for(i = 0; i < DEF_ALPH_LEN; i++)
        {
            if(x == alphabet[i].c_symb || x == _UPPERCASE(alphabet[i].c_symb))
            {
                Y = i;
                break;
            }
        }
    }
    else
    {
        for(i = 0; i < DEF_ALPH_LEN; i++)
        {
            if(x == alphabet[i].c_symb)
            {
                Y = i;
                break;
            }
        }
    }


    return Y;
}
