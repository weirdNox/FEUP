#include <stdio.h>

int calPontos(int numGanhoM, int numGanhoJ)
{
    int max = numGanhoJ > numGanhoM ? numGanhoJ : numGanhoM;

    if(max == 5)
    {
        return 5;
    }
    else if(max == 4)
    {
        return 3;
    }
    else if(max == 3)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int joaoWins = 0, mariaWins = 0;
    int currentJoao = 0, currentMaria = 0;
    int count = 0;
    int complete = 0;
    for(;;)
    {
        char letter;
        scanf(" %c", &letter);

        if(letter == 'f')
        {
            break;
        }

        ++count;

        if(letter == 'M')
        {
            ++currentMaria;
        }
        else
        {
            ++currentJoao;
        }

        if(count == 5)
        {
            ++complete;
            if(currentMaria > currentJoao)
            {
                mariaWins += calPontos(currentMaria, currentJoao);
            }
            else if(currentMaria < currentJoao)
            {
                joaoWins += calPontos(currentMaria, currentJoao);
            }

            count = currentJoao = currentMaria = 0;
        }
    }

    printf("%d completos\n", complete);

    if(mariaWins > joaoWins)
    {
        printf("Maria com %d\n", mariaWins);
    }
    else if(joaoWins > mariaWins)
    {
        printf("Joao com %d\n", joaoWins);
    }
    else
    {
        printf("Empate com %d\n", joaoWins);
    }

    return 0;
}
