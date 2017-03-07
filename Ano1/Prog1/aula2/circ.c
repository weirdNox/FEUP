#include <stdio.h>

#define PI32 3.1416f

int main(int argc, char *argv[])
{
    float radius;
    printf("Raio? ");
    scanf("%f", &radius);

    printf("\nPerímetro - %f", 2.0f*PI32*radius);
    printf("\n\nArea - %f", PI32*radius*radius);
}
