#include <stdio.h>

#define arrayCount(Arr) sizeof(Arr)/sizeof(*Arr)

void fillFibonacci(int *Buffer, int Count) {
    if(Count == 1) {
        Buffer[0] = 0;
    }
    else if(Count == 2) {
        Buffer[0] = 0;
        Buffer[1] = 1;
    }
    else if(Count > 2) {
        Buffer[0] = 0;
        Buffer[1] = 1;
        for(int Index = 2; Index < Count; ++Index) {
            Buffer[Index] = Buffer[Index-1] + Buffer[Index-2];
        }
    }
}

int main() {
    int FibonacciBuffer[10];
    fillFibonacci(FibonacciBuffer, arrayCount(FibonacciBuffer));

    for(size_t Index = 0; Index < arrayCount(FibonacciBuffer); ++Index) {
        printf("%d ", FibonacciBuffer[Index]);
    }

    return 0;
}
