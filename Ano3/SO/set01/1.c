#include <stdio.h>

int main() {
    int Num1, Num2;
    Num1 = 0;
    printf("%d ", Num1);
    Num2 = 1;
    printf("%d ", Num2);
    for(int Index = 2; Index < 10; ++Index) {
        int NewNum = Num1+Num2;
        Num1 = Num2;
        Num2 = NewNum;
        printf("%d ", NewNum);
    }

    return 0;
}
