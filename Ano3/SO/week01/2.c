#include <stdio.h>

#define printType(Type) printf(#Type " size: %lu\n", sizeof(Type))
int main() {
    printType(char);
    printType(short);
    printType(int);
    printType(long);
    printType(long long);

    int Array[10];
    printf("Array size: %lu\n", sizeof(Array));
    printf("Array element (int) size: %lu\n", sizeof(Array[0]));

    struct complex {
        double Re, Im;
    } Complex;
    printf("Complex number size: %lu\n", sizeof(Complex));

    char *Hello = "Hello, World!";
    printf("Hello World string (char *) size: %lu\n", sizeof(Hello));
    printf("Hello World string character (char) size: %lu\n", sizeof(*Hello));

    return 0;
}
