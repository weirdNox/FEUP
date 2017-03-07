#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TENTATIVAS 6

void imprimeForca(int erros)
{
	if (erros == 0)
	{
		printf ("	+------+\n");
		printf ("	 |   |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	============\n");
	}
	else if (erros == 1)
	{
		printf ("	+------+\n");
		printf ("	 |   |\n");
		printf ("	 o   |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	============\n");
	}
	else if (erros == 2)
	{
		printf ("	+------+\n");
		printf ("	 |   |\n");
		printf ("	 o   |\n");
		printf ("	 |   |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	============\n");
	}
	else if (erros == 3)
	{
		printf ("	+------+\n");
		printf ("	 |   |\n");
		printf ("	 o   |\n");
		printf ("	/|   |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	============\n");
	}
	else if (erros == 4)
	{
		printf ("	+------+\n");
		printf ("	 |   |\n");
		printf ("	 o   |\n");
		printf ("	/|\\  |\n");
		printf ("	     |\n");
		printf ("	     |\n");
		printf ("	============\n");
	}
	else if (erros == 5)
	{
		printf ("	+------+\n");
		printf ("	 |   |\n");
		printf ("	 o   |\n");
		printf ("	/|\\  |\n");
		printf ("	/    |\n");
		printf ("	     |\n");
		printf ("	============\n");
	}
	else if (erros == 6)
	{
		printf ("	+------+\n");
		printf ("	 |   |\n");
		printf ("	 o   |\n");
		printf ("	/|\\  |\n");
		printf ("	/ \\  |\n");
		printf ("	     |\n");
		printf ("	============\n");
	}

}

char** carregaPalavras(char *ficheiro, int *tamanho)
{
#if 0
    // This is the way to allocate dynamically... A bit OP for this
    FILE *file = fopen(ficheiro, "r");
    for(;;)
    {
        int bufferSize = 10;
        char *buffer = malloc(sizeof(*buffer)*bufferSize);
        int length = 0;

        for(;;)
        {
            if(!fgets(buffer+length, bufferSize-length, file))
            {
                // EOF...
                length = -1;
                break;
            }

            length = strlen(buffer);
            if(buffer[length-1] == '\n')
            {
                break;
            }

            bufferSize += 20;
            buffer = realloc(buffer, sizeof(*buffer)*bufferSize);
        }

        if(length == -1)
        {
            free(buffer);
            break;
        }

        for(int i = length-1; i >= 0; --i)
        {
            if(isspace(buffer[i]))
            {
                --length;
                buffer[i] = 0;
            }
            else
            {
                break;
            }
        }

        if(!length)
        {
            free(buffer);
            continue;
        }

        printf("|%s|\n", buffer);
    }
#else
    // Simpler way
    FILE *file = fopen(ficheiro, "r");
    *tamanho = 0;
    char **wordArr = 0;
    for(;;)
    {
        char *word = malloc(sizeof(*word)*50);
        if(fscanf(file, " %s", word) < 1)
        {
            free(word);
            break;
        }
        ++*tamanho;
        wordArr = realloc(wordArr, sizeof(*wordArr)*(*tamanho));
        wordArr[*tamanho-1] = word;
    }
#endif

    return wordArr;
}

char* obfuscaPalavra(char* palavra)
{
	int i = 0;
	char* nova;

	nova = (char*) malloc(sizeof(char)*strlen(palavra));
	strcpy(nova,palavra);
	while ( nova[i] != '\0' )
	{
		nova[i] = '*';
		i++;
	}
	return nova;
}

int letraNaPalavra(char a, char* palavra)
{
	int i = 0;
	while ( palavra[i] != '\0' )
	{
		if ( palavra[i] == a )
			return 1;
		i++;
	}
	return 0;
}

char * revelaLetras(char letra, char *palavra, char *obfuscada)
{
    int length = strlen(palavra);
    char *new = malloc(sizeof(*new)*(length+1));
    for(int i = 0; i < length; ++i)
    {
        if(palavra[i] == letra)
        {
            new[i] = letra;
        }
        else
        {
            new[i] = obfuscada[i];
        }
    }
    new[length] = 0;

	return new;
}

int vencedor(char *p1, char *p2)
{
	if(strcmp(p1,p2)==0)
		return 1;
	else
		return 0;
}

int joga(char *palavra, char *palavra_obfuscada)
{
    int numErros = 0;
    for(;;)
    {
        if(numErros >= TENTATIVAS)
        {
            break;
        }

        imprimeForca(numErros);
        printf("Que letra quer tentar? ");
        char c;
        scanf(" %c", &c);
        if(letraNaPalavra(c, palavra))
        {
            char *novaObfuscada = revelaLetras(c, palavra, palavra_obfuscada);
            free(palavra_obfuscada);
            palavra_obfuscada = novaObfuscada;
            printf("Muito bem! A letra %c está na palavra!\n", c);
            if(vencedor(palavra, palavra_obfuscada))
            {
                return numErros;
            }
        }
        else
        {
            printf("Letra errada!!\n");
            ++numErros;
        }

        printf("%s\n", palavra_obfuscada);
    }

	return numErros;
}


int main()
{
	char *dados = "palavras.txt";
	char **palavras = NULL;
	char *palavra, *palavra_obfuscada;
	int i, tamanho, contador;

	srand(time(NULL));

	palavras = carregaPalavras(dados, &tamanho);
	if(tamanho != 0)
	{
		palavra = palavras[rand()%tamanho];
		palavra_obfuscada = obfuscaPalavra(palavra);

		printf("%s\n", palavra_obfuscada);
		contador = joga(palavra,palavra_obfuscada);
		if(contador < TENTATIVAS)
			printf("Parabens!\n");
		else
			printf("Game over... The word was %s\n",palavra);

		for (i = 0; i < tamanho; i++)
		    free(palavras[i]);
		free(palavras);
	}

	return 0;
}
