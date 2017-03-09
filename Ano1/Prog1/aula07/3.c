#include <stdio.h>

int horasMin(int *hours, int *minutes)
{
    *hours = *minutes / 60;
    *minutes %= 60;

    if(*hours >= 24)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int hours, minutes, minStart;
    scanf("%d", &minStart);
    minutes = minStart;

    int above24 = horasMin(&hours, &minutes);
    printf("%d minutos correspondem a %02dh:%02dm e ", minStart, hours, minutes);

    if(above24)
    {
        puts("é superior a 1 dia");
    }
    else
    {
        puts("não é superior a 1 dia");
    }

    return 0;
}
