#include "4lib.c"

int main()
{
    Artigo armazem[10];
    int tamanhoArmazem = 0;
    for(int i = 0; i < 5; ++i)
    {
        leArtigo(armazem+tamanhoArmazem++);
    }

    printf("%d\n", totalArtigos(armazem, tamanhoArmazem, "test", "telele"));
    alertaArtigos(armazem, tamanhoArmazem);
    ordenaArtigos(armazem, tamanhoArmazem);
    escreveArtigos(armazem, tamanhoArmazem);

    return 0;
}
