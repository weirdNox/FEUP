#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMEQUIPAS 150

typedef struct {
    char nome[50];
    int tempo;
    int ncertas;
} equipa;

int ler_equipas(equipa *resultados, char *nomeFicheiro)
{
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if(!ficheiro)
    {
        return 0;
    }

    int numEquipas;

    int respostasCertas[4];
    fscanf(ficheiro, "%d %d %d %d", respostasCertas+0, respostasCertas+1,
           respostasCertas+2, respostasCertas+3);

    for(numEquipas = 0; numEquipas < NUMEQUIPAS; ++numEquipas)
    {
        equipa *nova = resultados+numEquipas;
        int respostas[4];
        if(fscanf(ficheiro, "%49s %d %d %d %d %d", nova->nome, &nova->tempo,
                  respostas+0, respostas+1, respostas+2, respostas+3) < 6)
        {
            break;
        }

        nova->ncertas = 0;
        for(int j = 0; j < 4; ++j)
        {
            if(respostas[j] == respostasCertas[j])
            {
                ++nova->ncertas;
            }
        }
    }

    fclose(ficheiro);
    ficheiro = 0;

    return numEquipas;
}

equipa* filtra_resultados (equipa *resultados, int N, int nMin, int *Nr)
{
    *Nr = 0;
    equipa *filtrado = 0;

    for(int i = 0; i < N; ++i)
    {
        if(resultados[i].ncertas >= nMin)
        {
            ++*Nr;
            equipa *temp = realloc(filtrado, sizeof(*filtrado)*(*Nr));
            if(!temp)
            {
                fprintf(stderr, "Não foi possível alocar memória suficiente!");
            }
            filtrado = temp;
            filtrado[*Nr-1] = resultados[i];
        }
    }

    return filtrado;
}

void lista_equipas(equipa *resultados, int N)
{
    int i;
    if(resultados == NULL)
        return;

    for(i=0; i<N; i++)
        printf("%s %d %d\n",resultados[i].nome, resultados[i].tempo, resultados[i].ncertas);
}

#define COUNT 10
void threeLargest(equipa *resultados, int n)
{
    equipa *e[COUNT] = {0};
    for(int i = 0; i < n; ++i)
    {
        equipa *test = resultados+i;
        for(int j = 0; j < COUNT; ++j)
        {
            equipa *testTo = e[j];
            if(!testTo || test->ncertas > testTo->ncertas ||
               (test->ncertas == testTo->ncertas && test->tempo < testTo->tempo))
            {
                for(int a = COUNT-1; a > j; --a)
                {
                    e[a] = e[a-1];
                }
                e[j] = test;
                break;
            }
        }
    }

    for(int i = 0; i < COUNT; ++i)
    {
        printf("%s ", e[i]->nome);
    }
    puts("");
}

void sort(equipa *resultados, int n)
{
    for(int i = 0; i < n-1; ++i)
    {
        equipa *best = resultados+i;
        for(int j = i+1; j < n; ++j)
        {
            equipa *test = resultados+j;
            if(test->ncertas > best->ncertas ||
               (test->ncertas == best->ncertas && test->tempo < best->tempo))
            {
                best = test;
            }
        }

        if(best != resultados+i)
        {
            equipa temp = *(resultados+i);
            *(resultados+i) = *best;
            *best = temp;
        }
    }
}

/*
  Para obtermos os 3 melhores classificados, poderiamos sortear por seleção inicialmente a
  lista de submissões e depois retornar os 3 primeiros.

  Para tal, teríamos de ter um loop que iterasse no intervalo i = [0,n-1[ e dentro desse
  loop guardaríamos um apontador "melhor", inicializado para o endereço do elemento i.
  Teríamos depois um loop dentro de j = [i+1, n[, que comparava o elemento j com o
  elemento apontado por "melhor". Se esse elemento j fosse melhor, ou seja, a pontuação
  mais alta, ou, no caso de empate, menor tempo, então modificariamos "melhor" para
  apontar para j. Fora desse loop, se "melhor" não apontasse para i, então trocariamos o
  elemento apontado por "melhor" com o elemento i.

  Depois de termos a lista sorteada, podemos pegar nos primeiros 3 elementos dessa lista e
  finalmente teríamos a resposta correta.
*/

int main()
{
    equipa resultados[NUMEQUIPAS], *lista;
    int numRegistos, n, n_lista = 0;

    numRegistos=ler_equipas(resultados, "submissoes.txt");

    printf("Numero de equipas: %d\n", numRegistos);
    lista_equipas(resultados, numRegistos);

    lista = filtra_resultados(resultados, numRegistos, 2, &n_lista);
    printf("Numero de equipas com pelo menos 2 respostas certas: %d\n", n_lista);
    lista_equipas(lista, n_lista);

    threeLargest(resultados, numRegistos);
    sort(resultados, numRegistos);
    lista_equipas(resultados, numRegistos);

    return 0;
}
