#include <stdio.h>

int main()
{
    int joaoWins = 0, mariaWins = 0;
    int currentJoao = 0, currentMaria = 0;
    int count = 0;
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
            count = 0;
            if(currentMaria > currentJoao)
            {
                ++mariaWins;
            }
            else
            {
                ++joaoWins;
            }

            currentJoao = currentMaria = 0;
        }
    }

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
