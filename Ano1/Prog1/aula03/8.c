#include <stdio.h>

int main()
{
    int number;
    printf("Insira um número: ");
    scanf("%d", &number);

    if(number < 1 || number > 999)
    {
        return -1;
    }

    int units = number % 10;
    number /= 10;
    int tens = number % 10;
    number /= 10;
    int hundreds = number;

    switch(hundreds)
    {
        case 1: {printf("C");} break;
        case 2: {printf("CC");} break;
        case 3: {printf("CCC");} break;
        case 4: {printf("CD");} break;
        case 5: {printf("D");} break;
        case 6: {printf("DC");} break;
        case 7: {printf("DCC");} break;
        case 8: {printf("DCCC");} break;
        case 9: {printf("CM");} break;
        default: {} break;
    }

    switch(tens)
    {
        case 1: {printf("X");} break;
        case 2: {printf("XX");} break;
        case 3: {printf("XXX");} break;
        case 4: {printf("XL");} break;
        case 5: {printf("L");} break;
        case 6: {printf("LX");} break;
        case 7: {printf("LXX");} break;
        case 8: {printf("LXXX");} break;
        case 9: {printf("XC");} break;
        default: {} break;
    }

    switch(units)
    {
        case 1: {printf("I");} break;
        case 2: {printf("II");} break;
        case 3: {printf("III");} break;
        case 4: {printf("IX");} break;
        case 5: {printf("V");} break;
        case 6: {printf("VI");} break;
        case 7: {printf("VII");} break;
        case 8: {printf("VIII");} break;
        case 9: {printf("IX");} break;
        default: {} break;
    }

    puts("");

    return 0;
}
