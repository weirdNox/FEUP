#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pilha/pilha.c"

float calcula_total(char *expressao_rpn)
{
    pilha *rpn = pilha_nova();
    char *next = strtok(expressao_rpn, " ");
    while(next)
    {
        char first = next[0];
        if(strlen(next) == 1 && (first == '+' || first == '-' || first == '/' || first == '*'))
        {
            if(pilha_tamanho(rpn) < 2)
            {
                fprintf(stderr, "Operador sem elementos suficientes!\n");
                break;
            }
            char *n1Text, *n2Text;
            float n1, n2;
            n2Text = pilha_top(rpn);
            sscanf(n2Text, "%f", &n2);
            pilha_pop(rpn);

            n1Text = pilha_top(rpn);
            sscanf(n1Text, "%f", &n1);
            pilha_pop(rpn);

            switch(first)
            {
                case '+':
                {
                    n1 += n2;
                } break;
                case '-':
                {
                    n1 -= n2;
                } break;
                case '/':
                {
                    n1 /= n2;
                } break;
                case '*':
                {
                    n1 *= n2;
                } break;
            }

            char buff[50];
            sprintf(buff, "%f", n1);
            pilha_push(rpn, buff);
        }
        else if(isdigit(first) || first == '-')
        {
            pilha_push(rpn, next);
        }
        next = strtok(0, " ");
    }

    char *resultText = pilha_top(rpn);
    float result;
    sscanf(resultText, "%f", &result);
    pilha_apaga(rpn);
    return result;
}

int main()
{
    char buffer[1<<11];
    printf("Expressão: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = 0;
    float result = calcula_total(buffer);

    printf("Resultado: %f\n", result);

    return 0;
}
