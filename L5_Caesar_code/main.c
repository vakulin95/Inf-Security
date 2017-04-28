#include "caes.h"

int count_letters(wchar_t x);
void analize(void);
void swap(Letter *x1, Letter *x2);

wchar_t TEXT[DEF_STR_LEN] = DEF_STR;
Letter alphabet[DEF_ALPH_LEN];
int T_LEN;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    T_LEN = wcslen(TEXT);

    printf("\n-----------------------------------------Caesar's code-----------------------------------------\n\n");

    //printf("String Entered:\n\n%ls\n\nlength: %d\n", TEXT, wcslen(TEXT));
    analize();

    printf("-----------------------------------------------------------------------------------------------\n");

    return 0;
}

int count_letters(wchar_t x)
{
    int Y = 0;
    int i;

    for(i = 0; i < T_LEN; i++)
    {
        if(TEXT[i] == x || TEXT[i] == x - 32)
        {
            Y++;
        }
    }

    return Y;
}

void analize(void)
{
    int i, j;
    int n_of_symb;
    wchar_t letter;

    n_of_symb = 0;
    for(i = 0; i < T_LEN; i++)
    {
        if(TEXT[i] >= _L('А') && TEXT[i] <= _L('я'))
        {
            n_of_symb++;
        }
    }

    letter = _L('а');
    for(i = 0; i < DEF_ALPH_LEN; i++)
    {
        alphabet[i].symb = letter;
        alphabet[i].frec = (float)count_letters(letter++) / n_of_symb;
    }

    for(i = 0; i < DEF_ALPH_LEN; ++i)
    {
        for(j = DEF_ALPH_LEN - 1; j > i; --j)
        {
            if(alphabet[j].frec > alphabet[j - 1].frec)
                swap(alphabet + j, alphabet + (j - 1));
        }
    }

    for(i = 0; i < DEF_ALPH_LEN; i++)
    {
        printf("%lc - %f\n", alphabet[i].symb, alphabet[i].frec);
    }

    return;
}

void swap(Letter *x1, Letter *x2)
{
    Letter temp;

    temp.symb = x1->symb;
    temp.frec = x1->frec;

    x1->symb = x2->symb;
    x1->frec = x2->frec;

    x2->symb = temp.symb;
    x2->frec = temp.frec;
}
