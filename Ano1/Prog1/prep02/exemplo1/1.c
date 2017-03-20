#include <stdio.h>

int ler_acessos(int *tempos)
{
    int count = 0;
    int saidaAnterior = -190;
    for(;;)
    {
        int entrada, saida;
        if(scanf("%d %d", &entrada, &saida) < 2)
        {
            break;
        }
        if(entrada - saidaAnterior < 120)
        {
            tempos[count-1] += saida-saidaAnterior;
        }
        else
        {
            tempos[count++] = saida-entrada;
        }
        saidaAnterior = saida;
    }
    return count;
}

void stats(int *tempos, int n, int *min, int *max, float *med)
{
    *min = tempos[0];
    *max = tempos[0];
    *med = tempos[0];

    for(int i = 1; i < n; ++i)
    {
        if(*min > tempos[i])
        {
            *min = tempos[i];
        }
        if(*max < tempos[i])
        {
            *max = tempos[i];
        }
        *med += tempos[i];
    }

    *med /= (float)n;
}

int main()
{
    int tempos[100];
    int numTempos = ler_acessos(tempos);
    int min, max;
    float med;
    stats(tempos, numTempos, &min, &max, &med);

    printf("Numero de acessos: %d\n", numTempos);
    printf("Min: %d | Max: %d | Med: %.2f\n", min, max, med);

    return 0;
}
