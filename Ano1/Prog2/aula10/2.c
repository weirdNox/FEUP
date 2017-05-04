#include "tabdispersao.c"
#include <stdio.h>

int main()
{
    FILE *f = fopen("passwords.txt", "r");
    tabela_dispersao *h = tabela_nova(256, hash_djbm);

    char linha[1<<10];
    while(fgets(linha, 1<<10, f))
    {
        char *nome = strtok(linha, "\r\n ");
        char *pass = strtok(0, "\r\n ");
        tabela_adiciona(h, nome, pass);
    }
    fclose(f);

    char nome[100], pass[100];
    printf("Login: ");
    scanf("%s", nome);
    printf("Password: ");
    scanf("%s", pass);
    char *teste = (char*)tabela_valor(h, nome);
    if(teste && strcmp(teste, pass) == 0)
    {
        puts("Succeeded");
    }
    else
    {
        puts("Failed");
    }

    mostraTabela(h);
    tabela_alterahash(h, hash_krm);
    mostraTabela(h);
    tabela_alterahash(h, hash_djbm);
    mostraTabela(h);

    tabela_apaga(h);

    return 0;
}
