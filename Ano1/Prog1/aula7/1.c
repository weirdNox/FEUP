#include <stdio.h>

int *vmaior(int *valor1, int *valor2)
{
    if(*valor1 >= *valor2)
    {
        return valor1;
    }
    else
    {
        return valor2;
    }
}

int main()
{
    int i1, i2;
    scanf("%d %d", &i1, &i2);

    int *maior = vmaior(&i1, &i2);
    printf("Endereço do maior: %p\nConteudo: %d\n", maior, *maior);

    return 0;
}
