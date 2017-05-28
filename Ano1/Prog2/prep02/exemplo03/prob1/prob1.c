#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.c"
#include "tabdispersao.c"
#include "lista.c"

void avlImprimeCrescente(no_avl *no)
{
    if(!no)
    {
        return;
    }
    avlImprimeCrescente(no->esquerda);
    printf("%s ", no->str);
    avlImprimeCrescente(no->direita);
}

void avlImprimeDecrescente(no_avl *no)
{
    if(!no)
    {
        return;
    }
    avlImprimeDecrescente(no->direita);
    printf("%s ", no->str);
    avlImprimeDecrescente(no->esquerda);
}

void avl_imprime_ord(arvore_avl *avl, int ordem)
{
    if(!avl)
    {
        return;
    }

    if(ordem >= 0)
    {
        avlImprimeCrescente(avl->raiz);
    }
    else
    {
        avlImprimeDecrescente(avl->raiz);
    }
    puts("");
}

void valida_passwds(FILE *f, lista *login, lista *passwd)
{
    if(!f || !login || !passwd || login->tamanho != passwd->tamanho)
    {
        return;
    }

    tabela_dispersao *td = tabela_nova(10, hash_djbm);
    if(!td)
    {
        return;
    }

    for(;;)
    {
        char username[30], password[30];
        if(fscanf(f, "%s %s", username, password) < 2)
        {
            break;
        }

        if(tabela_adiciona(td, username, password) != TABDISPERSAO_OK)
        {
            tabela_apaga(td);
            return;
        }
    }


    for(elemento *username = login->inicio, *password = passwd->inicio;
        username && password;
        username = username->proximo, password = password->proximo)
    {
        printf("Login: %s\nPassword: %s\n", username->str, password->str);
        char *teste = (char*)tabela_valor(td, username->str);
        if(!teste)
        {
            break;
        }

        if(strcmp(teste, password->str) == 0)
        {
            puts("Authentication succeeded");
        }
        else
        {
            puts("Authentication failed");
        }
    }

    tabela_apaga(td);
}

/* Aqui começa o código de teste. Não modificar! */

int main() {
    /* teste problema 1.1 */
    {

        arvore_avl *res;
        int i;
        char data[][4] = {"ENG", "BEL", "NED", "GER", "FRA", "RUS", "SUI", "CRO", "BIH", "ITA", "ESP", "POR", "GRE"};

        printf("* Problema 1.1 *\n");

        res = avl_nova();

        for (i = 0; i < 13; i++)
            avl_insere(res, data[i]);

        printf("Arvore original: ");
        avl_imprime(res->raiz);

        printf("Ordem alfabetica crescente: ");
        avl_imprime_ord(res, 1);
        printf("\n\n");

        avl_apaga(res);
    }

    /* teste problema 1.2 */
    {
        FILE *f;
        lista *lg, *psswd;
        int i;
        char login[][TAMANHO_VALOR] = {"maria", "tiago", "ricardo"};
        char password[][TAMANHO_CHAVE] = {"contrary", "contrary", "sheeplost"};

        printf("* Problema 1.2 *\n");

        f = fopen("passwords.txt", "r");
        if (!f) {
            printf("Nao foi possivel abrir ficheiro!\n");
            return -1;
        }

        lg = lista_nova();
        for (i = 0; i < 3; i++)
            lista_insere(lg, login[i], NULL);

        psswd = lista_nova();
        for (i = 0; i < 3; i++)
            lista_insere(psswd, password[i], NULL);

        valida_passwds(f, lg, psswd);

        lista_apaga(lg);
        lista_apaga(psswd);
        fclose(f);
    }

    return 0;
}
