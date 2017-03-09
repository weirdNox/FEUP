#include <stdio.h>

int main(int argc, char *argv[])
{
    int x, y;
    printf("Insira coordenadas: ");
    scanf("%d %d", &x, &y);

    if(x >= 0 && y >= 0)
    {
        puts("1");
    }
    else if(x < 0 && y >= 0)
    {
        puts("2");
    }
    else if(x < 0 && y < 0)
    {
        puts("3");
    }
    else if(x >= 0 && y < 0)
    {
        puts("4");
    }

    return 0;
}
