#include <stdio.h>
#include <time.h>
#include "avl.c"
#include "bst.c"

#define arrayCount(arr) sizeof(arr)/sizeof(arr[0])

// NOTE(nox): Este teste demora demasiado tempo, por isso nunca o cheguei a correr até ao
// fim
#define TESTAR_BST_SORTEADO 0

/*
  CONCLUSÕES:
  - Inserir elementos não ordenados numa BST pode ser mais rápido que numa AVL porque a
    AVL tem de ir rebalançando a árvore à medida que insere, enquanto que a BST só tem de
    inserir no local certo. Enquanto a BST mantiver uma estrutura aproximadamente
    balançada, será mais rápido inserir na BST do que na AVL.

  - A pesquisa numa AVL vai ser, no pior caso, O(log(n)) enquanto que numa BST pode ser
    O(n), por isso, está assegurado que a AVL não é mais lenta (no caso geral). Enquanto a
    BST mantiver uma estrutura aproximadamente balançada, então a pesquisa aproxima
    O(log(n)) também. No entanto, procurar por um elemento especificamente pode acabar por
    ser mais rápido na BST, mas isto será por pura sorte - numa AVL, para se encontrar os
    elementos menores e maiores que todos os outros, tem de se percorrer a altura toda
    enquanto que esses mesmos elementos numa BST _por sorte_ podem estar mais perto da
    raiz da árvore e serem logo encontrados.

  - No caso dos elementos a inserir já estarem sorteados, temos um claro vencedor - a
    árvore AVL. Enquanto que a árvore AVL se balança logo ao fim de cada insersão e mantém
    sempre a estrutura balançada (mantendo assim sempre uma complexidade logarítmica), a
    BST torna-se numa estrutura linear, e para inserir o elemento n, vai ter de percorrer
    antes n-1 elementos, fazendo assim com que perca todas as vantagens de ser uma árvore
    binária.
 */

int main()
{
    FILE *ficheiro = fopen("cidades.txt", "r");
    if(!ficheiro)
    {
        fprintf(stderr, "Erro ao abrir ficheiro\n");
        return -1;
    }

    arvore_avl *avl = avl_nova();
    if(!avl)
    {
        fprintf(stderr, "Erro ao criar AVL\n");
        return -1;
    }
    { // NOTE(nox): Teste inserção AVL
        clock_t inicio = clock();

        char linha[1<<13];
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            char *str = strtok(linha, "\r\n");
            avl_insere(avl, str);
        }

        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de inserção na AVL: %lfs\n", tempo);
    }

    rewind(ficheiro);

    arvore_bst *bst = bst_nova();
    if(!bst)
    {
        fprintf(stderr, "Erro ao criar BST\n");
        return -1;
    }
    { // NOTE(nox): Teste inserção BST
        clock_t inicio = clock();

        char linha[1<<13];
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            char *str = strtok(linha, "\r\n");
            bst_insere(bst, str);
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

    avl_apaga(avl);
    bst_apaga(bst);
    fclose(ficheiro);


    ficheiro = fopen("cidades_sorted.txt", "r");
    if(!ficheiro)
    {
        fprintf(stderr, "Erro ao abrir ficheiro\n");
        return -1;
    }

    avl = avl_nova();
    if(!avl)
    {
        fprintf(stderr, "Erro ao criar AVL\n");
        return -1;
    }
    { // NOTE(nox): Teste inserção sorteada AVL
        clock_t inicio = clock();

        char linha[1<<13];
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            char *str = strtok(linha, "\r\n");
            avl_insere(avl, str);
        }

        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de inserção sorteada na AVL: %lfs\n", tempo);
    }

    rewind(ficheiro);

#if TESTAR_BST_SORTEADO
    bst = bst_nova();
    if(!bst)
    {
        fprintf(stderr, "Erro ao criar BST\n");
        return -1;
    }
    { // NOTE(nox): Teste inserção sorteada BST
        clock_t inicio = clock();

        char linha[1<<13];
        int count = 0;
        double tempoAnterior;
        while(fgets(linha, arrayCount(linha), ficheiro))
        {
            if(!(count % (2000)))
            {
                double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
                printf("String #%d, passaram %lfs desde o anterior\n",
                       count+1, tempo - tempoAnterior);
                tempoAnterior = tempo;
            }

            char *str = strtok(linha, "\r\n");
            bst_insere(bst, str);

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

#if TESTAR_BST_SORTEADO
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
