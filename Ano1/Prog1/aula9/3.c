#include <stdio.h>

int main()
{
    int data[4][3];

    for(int i = 0; i < 4; ++i)
    {
        printf("Dados do aluno %d: ", i+1);
        scanf("%d %d %d", data[i], data[i]+1, data[i]+2);
    }

    puts("Número\tNota 1\tNota 2\tMédia");
    for(int i = 0; i < 4; ++i)
    {
        printf("%05d\t%d\t%d\t%.1f\n", data[i][0], data[i][1], data[i][2],
               (data[i][1] + data[i][2])/2.0f);
    }

    return 0;
}
