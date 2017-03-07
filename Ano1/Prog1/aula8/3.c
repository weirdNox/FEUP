#include <stdio.h>

void preencher_vetor(float v[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        scanf("%f", v+i);
    }
}

float somatorio_vetor(float v[], int n)
{
    float sum = 0;
    for(int i = 0; i < n; ++i)
    {
        sum += v[i];
    }
    return sum;
}

void imprimir_vetor(float v[], int n)
{
    printf("{");
    for(int i = 0; i < n; ++i)
    {
        printf("%f", v[i]);
        if(i < n-1)
        {
            printf(", ");
        }
    }
    puts("}");
}

int main()
{
    float v[15];
    int n;
    do
    {
        scanf("%d", &n);
    } while(n <= 0 || n > 15);

    preencher_vetor(v, n);
    imprimir_vetor(v, n);
    printf("%f\n", somatorio_vetor(v, n));

    return 0;
}
