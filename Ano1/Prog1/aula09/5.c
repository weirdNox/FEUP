#include <stdlib.h>
#include <stdio.h>

int pos(int x, int y, int tamanho) { return x + y * tamanho; }

void imprimeMatriz(int *matriz, int m, int n)
{
    printf("\u250c ");
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            printf(" ");
        }
        printf("\t");
    }
    printf(" \u2510\n");

    for(int y = 0; y < m; ++y)
    {
        printf("\u2502 ");
        for(int x = 0; x < n; ++x)
        {
            printf("%-3d\t", matriz[pos(x, y, n)]);
        }
        printf(" \u2502\n");
    }

    printf("\u2514 ");
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            printf(" ");
        }
        printf("\t");
    }
    printf(" \u2518\n");
}

void produtoEscalar(int *matriz, int N, int escalar)
{
    for(int y = 0; y < N; ++y)
    {
        for(int x = 0; x < N; ++x)
        {
            matriz[pos(x, y, N)] *= escalar;
        }
    }
}

void multMatrizes(int *matriz, int *mult, int *resultado, int N)
{
    for(int y = 0; y < N; ++y)
    {
        resultado[y] = 0;
        for(int x = 0; x < N; ++x)
        {
            resultado[y] += matriz[pos(x, y, N)] * mult[x];
        }
    }
}

int main()
{
    int matrix[10*10] = {0};
    int matrixSize;
    do
    {
        printf("Tamanho do lado da matriz: ");
        scanf("%d", &matrixSize);
    } while(matrixSize > 10);

    for(int y = 0; y < matrixSize; ++y)
    {
        for(int x = 0; x < matrixSize; ++x)
        {
            matrix[pos(x, y, matrixSize)] = rand()%40;
        }
    }

    imprimeMatriz(matrix, matrixSize, matrixSize);
    produtoEscalar(matrix, matrixSize, 2);
    imprimeMatriz(matrix, matrixSize, matrixSize);

    int mult[10];
    int resultado[10];
    for(int i = 0; i < matrixSize; ++i)
    {
        mult[i] = rand()%10;
    }
    imprimeMatriz(mult, matrixSize, 1);

    multMatrizes(matrix, mult, resultado, matrixSize);
    imprimeMatriz(resultado, matrixSize, 1);

    return 0;
}
