#include <stdio.h>

int main()
{
    float height;
    char sex;
    scanf("%f %c", &height, &sex);

    printf("%f", sex == 'M' ? 72.7f*height-58 : 62.1f*height - 44.7);

    return 0;
}
