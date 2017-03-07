#include <stdio.h>

int ler_acessos(int *id, int *tempo)
{
    int numAcessos;
    for(numAcessos = 0; numAcessos < 100; ++numAcessos)
    {
        int entrada, saida;
        if(scanf("%d %d %d", id+numAcessos, &entrada, &saida) < 3)
        {
            break;
        }
        tempo[numAcessos] = saida - entrada;
    }
    return numAcessos;
}

int mais_tempo(int *tempo, int n)
{
    int index = 0;
    for(int i = 1; i < n; ++i)
    {
        if(tempo[i] > tempo[index])
        {
            index = i;
        }
    }
    return index;
}

int main()
{
    int id[100], tempo[100];
    int numAcessos = ler_acessos(id, tempo);
    int iMaior = mais_tempo(tempo, numAcessos);

    printf("Total de acessos: %d\n", numAcessos);
    printf("Carro que permaneceu mais tempo: %d (%d minutos)\n", id[iMaior], tempo[iMaior]);

    return 0;
}
