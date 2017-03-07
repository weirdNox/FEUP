#include <stdio.h>
#include "datas.h"

int main(void) {
    data d;
    printf("data (dia mes ano)? ");
    scanf("%d %d %d", &d.dia, &d.mes, &d.ano);

    int dias;
    printf("Número de dias? ");
    scanf("%d", &dias);
    d = somaDias(d, dias);
    char buffer[1<<10];
    escreveData(buffer, d);
    printf("%s\n", buffer);

    return 0;
}
