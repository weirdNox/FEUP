#include <stdio.h>

#define swap(type, a, b) do { type temp = (a); (a)=(b); (b)=temp; } while(0)

void ordena(float notas[][2], int N)
{
    for(int i = 0; i < N; ++i)
    {
        float max = notas[i][1];
        int index = i;
        for(int j = i+1; j < N; ++j)
        {
            if(notas[j][1] > max)
            {
                index = j;
                max = notas[j][1];
            }
        }
        if(index != i)
        {
            swap(float, notas[i][0], notas[index][0]);
            swap(float, notas[i][1], notas[index][1]);
        }
    }
}

int main()
{
    float data[4][2];

    for(int i = 0; i < 4; ++i)
    {
        printf("Dados do aluno %d: ", i+1);
        float mark1, mark2;
        scanf("%f %f %f", data[i], &mark1, &mark2);
        data[i][1] = (mark1 + mark2)/2.0f;
    }

    ordena(data, 4);

    puts("Número\tMédia");
    for(int i = 0; i < 4; ++i)
    {
        printf("%05.f\t%.1f\n", data[i][0], data[i][1]);
    }

    return 0;
}
