#include <stdio.h>

#define arrayCount(a) sizeof(a)/sizeof(*a)
#define assert(a) if(!(a)) { *((volatile int *)0) = 0; }

int getPrecedence(char operator)
{
    if(operator == '*' || operator == '/')
    {
        return 2;
    }
    return 1;
}

int main()
{
    int numCases;
    scanf("%d", &numCases);
    for(int i = 0; i < numCases; ++i)
    {
        if(i)
        {
            puts("");
        }

        char operatorStack[256];
        int operatorStackSize = 0;

        char c;
        scanf(" %c", &c); // NOTE(nox): Read first char
        while(c != '\n' && c != EOF)
        {
            if(c >= '0' && c <= '9')
            {
                printf("%c", c);
            }
            else
            {
                switch(c)
                {
                    case '(':
                    {
                        assert(operatorStackSize < arrayCount(operatorStack));
                        operatorStack[operatorStackSize++] = c;
                    } break;

                    case ')':
                    {
                        while(operatorStackSize)
                        {
                            char operator = operatorStack[--operatorStackSize];
                            if(operator == '(')
                            {
                                break;
                            }
                            printf("%c", operator);
                        }
                    } break;

                    default:
                    {
                        int precedence = getPrecedence(c);
                        while(operatorStackSize)
                        {
                            char operator = operatorStack[operatorStackSize-1];
                            char operatorPrecedence = getPrecedence(operator);
                            if(operator != '(' && precedence <= operatorPrecedence)
                            {
                                printf("%c", operator);
                                --operatorStackSize;
                            }
                            else
                            {
                                break;
                            }
                        }

                        assert(operatorStackSize < arrayCount(operatorStack));
                        operatorStack[operatorStackSize++] = c;
                    } break;
                }
            }

            // NOTE(nox): Read '\n' and next
            fgetc(stdin);
            c = fgetc(stdin);
        }

        while(operatorStackSize--)
        {
            char operator = operatorStack[operatorStackSize];
            if(operator == '(')
            {
                fprintf(stderr, "Mismatched parentheses");
            }
            else
            {
                printf("%c", operator);
            }
        }
        puts("");
    }

    return 0;
}
