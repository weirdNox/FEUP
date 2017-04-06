#include <stdio.h>
#include <time.h>
#include "avl.c"
#include "bst.c"

#define arrayCount(arr) sizeof(arr)/sizeof(arr[0])

int main()
{
    FILE *ficheiro = fopen("cidades.txt", "r");
    if(!ficheiro)
    {
        fprintf(stderr, "Erro ao abrir ficheiro\n");
        return -1;
    }

    arvore_avl *avl = avl_nova();
    { // NOTE(nox): Teste inserção AVL
        clock_t inicio = clock();

        char linha[1<<13];
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            for(int i = strlen(linha)-1; i >= 0 && (linha[i] == '\n' || linha[i] == '\r'); --i)
            {
                linha[i] = 0;
            }

            if(avl_insere(avl, linha) == -1)
            {
                fprintf(stderr, "Erro ao inserir %s na AVL\n", linha);
            }
        }

        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de inserção na AVL: %lfs\n", tempo);
    }

    rewind(ficheiro);

    arvore_bst *bst = bst_nova();
    { // NOTE(nox): Teste inserção BST
        clock_t inicio = clock();

        char linha[1<<13];
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            for(int i = strlen(linha)-1; i >= 0 && (linha[i] == '\n' || linha[i] == '\r'); --i)
            {
                linha[i] = 0;
            }

            if(bst_insere(bst, linha) == -1)
            {
                fprintf(stderr, "Erro ao inserir %s na BST\n", linha);
            }
        }

        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de inserção na BST: %lfs\n", tempo);
    }

    char *searchText = "Zywiec,Poland";
    { // NOTE(nox): Teste pesquisa AVL
        clock_t inicio = clock();
        no_avl *no = avl_pesquisa(avl, searchText);
        if(!no)
        {
            fprintf(stderr, "Erro ao pesquisar %s na AVL\n", searchText);
        }
        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de pesquisa na AVL: %lfs\n", tempo);
    }
    { // NOTE(nox): Teste pesquisa BST
        clock_t inicio = clock();
        no_bst *no = bst_pesquisa(bst, searchText);
        if(!no)
        {
            fprintf(stderr, "Erro ao pesquisar %s na BST\n", searchText);
        }
        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de pesquisa na BST: %lfs\n", tempo);
    }

    fclose(ficheiro);
    ficheiro = fopen("cidades_sorted.txt", "r");
    if(!ficheiro)
    {
        fprintf(stderr, "Erro ao abrir ficheiro\n");
        return -1;
    }

    avl_apaga(avl);
    bst_apaga(bst);

    avl = avl_nova();
    { // NOTE(nox): Teste inserção sorteada AVL
        clock_t inicio = clock();

        char linha[1<<13];
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            for(int i = strlen(linha)-1; i >= 0 && (linha[i] == '\n' || linha[i] == '\r'); --i)
            {
                linha[i] = 0;
            }

            if(avl_insere(avl, linha) == -1)
            {
                fprintf(stderr, "Erro ao inserir %s na AVL\n", linha);
            }
        }

        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de inserção sorteada na AVL: %lfs\n", tempo);
    }

    rewind(ficheiro);

#if 0
    bst = bst_nova();
    { // NOTE(nox): Teste inserção sorteada BST
        clock_t inicio = clock();

        char linha[1<<13];
        int count = 0;
        double tempoAnterior;
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            if(!(count % (1000)))
            {
                double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
                printf("String #%d, passaram %lfs desde o anterior\n",
                       count+1, tempo - tempoAnterior);
                tempoAnterior = tempo;
            }
            for(int i = strlen(linha)-1; i >= 0 && (linha[i] == '\n' || linha[i] == '\r'); --i)
            {
                linha[i] = 0;
            }

            if(bst_insere(bst, linha) == -1)
            {
                fprintf(stderr, "Erro ao inserir %s na BST\n", linha);
            }
            ++count;
        }

        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de inserção sorteada na BST: %lfs\n", tempo);
    }
#endif

    { // NOTE(nox): Teste pesquisa sorteada AVL
        clock_t inicio = clock();
        no_avl *no = avl_pesquisa(avl, searchText);
        if(!no)
        {
            fprintf(stderr, "Erro ao pesquisar %s na AVL\n", searchText);
        }
        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de pesquisa sorteada na AVL: %lfs\n", tempo);
    }

#if 0
    { // NOTE(nox): Teste pesquisa sorteada BST
        clock_t inicio = clock();
        no_bst *no = bst_pesquisa(bst, searchText);
        if(!no)
        {
            fprintf(stderr, "Erro ao pesquisar %s na BST\n", searchText);
        }
        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de pesquisa sorteada na BST: %lfs\n", tempo);
    }
#endif

    return 0;
}
