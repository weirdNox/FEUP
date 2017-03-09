#include <stdio.h>
#include "lista.c"

lista *readFromFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if(!file)
    {
        fprintf(stderr, "Erro ao abrir ficheiro\n");
        return 0;
    }

    lista *l = lista_nova();

    char buffer[1<<10];
    while(fgets(buffer, 1<<10, file))
    {
        int size = strlen(buffer);
        buffer[size-1] = 0;
        lista_insere(l, buffer, 0);
    }

    fclose(file);

    return l;
}

void printList(lista *l, FILE *stream)
{
    int num = lista_tamanho(l);
    for(int i = 0; i < num; ++i)
    {
        fprintf(stream, "Pos %d -> %s\n", i, lista_elemento(l, i)->str);
    }
}

int main()
{
    lista *games = readFromFile("arquivo.txt");
    printf("Foram carregados %d jogos:\n", lista_tamanho(games));
    printList(games, stdout);

    lista *ps2Games = lista_pesquisa_substring(games, "PS2");
    int ps2Num = lista_tamanho(ps2Games);
    for(int i = 0; i < ps2Num; ++i)
    {
        char *text = lista_elemento(ps2Games, i)->str;
        for(int j = 0; j < lista_tamanho(games); ++j)
        {
            char *textTest = lista_elemento(games, j)->str;
            if(!strcmp(text, textTest))
            {
                lista_remove(games, lista_elemento(games, j));
                break;
            }
        }
    }

    printf("Após a remoção, a lista contém %d jogos.\n", lista_tamanho(games));
    FILE *withoutPs2 = fopen("jogos2.txt", "w");
    printList(games, withoutPs2);
    fclose(withoutPs2);

    lista *oldies = readFromFile("oldies.txt");
    int oldNum = lista_tamanho(oldies);
    printf("Foram carregados %d jogos antigos.\n", oldNum);
    for(int i = 0; i < oldNum; ++i)
    {
        printf("Pos %d -> %s\n", i, lista_elemento(oldies, i)->str);
    }

    games = lista_concatena(games, oldies);
    printf("Após a concatenação, a lista final contém %d jogos.\n", lista_tamanho(games));
    printList(games, stdout);

    lista_ordena(games);
    printf("Lista ordenada:\n");
    printList(games, stdout);

    char *dukeText = "Duke Nukem (PS3)";
    for(int i = 0; i < lista_tamanho(games); ++i)
    {
        if(!strcmp(dukeText, lista_elemento(games, i)->str))
        {
            printf("O jogo %s encontra-se na posiçao %d\n", dukeText, i);
            break;
        }
    }

    int pos = lista_insere_ordenada(games, "Minesweeper (PC)");
    l_elemento *testNew = lista_elemento(games, pos);
    printf("O jogo %s foi inserido na posição %d\n", testNew->str, pos);
    printList(games, stdout);

    lista_apaga(games);
    lista_apaga(ps2Games);
    lista_apaga(oldies);

    return 0;
}
