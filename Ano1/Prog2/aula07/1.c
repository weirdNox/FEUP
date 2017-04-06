#include <stdio.h>
#include "bst.c"
#include "avl.c"

#define arrayCount(arr) sizeof(arr)/sizeof(arr[0])

int main()
{
    arvore_bst *bst = bst_nova();
    if(!bst)
    {
        fprintf(stderr, "Erro ao criar BST\n");
        return -1;
    }

    char *input[] = {"G", "C", "A", "F", "L", "J",
                     "V", "M", "N", "O"};
    for(int i = 0; i < arrayCount(input); ++i)
    {
        bst_insere(bst, input[i]);
    }

    int bstAltura = bst_altura(bst->raiz);
    if(bstAltura != 5)
    {
        fprintf(stderr, "Altura da BST errada\n");
        return -1;
    }
    bst_imprime(bst);


    arvore_avl *avl = avl_nova();
    if(!avl)
    {
        fprintf(stderr, "Erro ao criar AVL\n");
        return -1;
    }

    for(int i = 0; i < arrayCount(input); ++i)
    {
        avl_insere(avl, input[i]);
    }

    int avlAltura = avl_altura(avl->raiz);
    if(avlAltura != 3)
    {
        fprintf(stderr, "Altura da AVL errada\n");
        return -1;
    }
    avl_imprime(avl);

    if(avl_remove(avl, "N") == -1)
    {
        fprintf(stderr, "Erro ao remover 'N' da AVL\n");
        return -1;
    }

    // Há 1 rotação para a direita da sub-árvore com raiz "O", pois ficou com um balanço de -2
    // depois de remover o seu filho da direita "V"
    if(avl_remove(avl, "V") == -1)
    {
        fprintf(stderr, "Erro ao remover 'V' da AVL\n");
        return -1;
    }

    return 0;
}
