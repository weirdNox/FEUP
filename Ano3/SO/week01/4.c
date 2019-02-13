#include <stdio.h>
#include <stdlib.h>

#define UseAtoi 0
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

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s SequenceSize\n", ArgVals[0]);
        return 1;
    }

    int SequenceSize;
#if UseAtoi
    SequenceSize = atoi(ArgVals[1]);
#else
    char *EndRead;
    SequenceSize = strtol(ArgVals[1], &EndRead, 10);
    if(EndRead == ArgVals[1]) {
        fprintf(stderr, "Invalid SequenceSize given\n");
        return 1;
    }
#endif

    int *FibonacciBuffer = malloc(sizeof(*FibonacciBuffer)*SequenceSize);
    fillFibonacci(FibonacciBuffer, SequenceSize);

    for(int Index = 0; Index < SequenceSize; ++Index) {
        printf("%d ", FibonacciBuffer[Index]);
    }

    return 0;
}
