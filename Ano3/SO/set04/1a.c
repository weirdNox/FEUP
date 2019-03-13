#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum {
    Op_Add,
    Op_Subtract,
    Op_Multiply,
    Op_Divide,
    Op_Count
} operation;

int Operand1, Operand2;

void *threadFunc(void *Arg) {
    operation Op = *(operation *)Arg;

    int Result;
    char *OpText;

    switch(Op) {
        case Op_Add: {
            OpText = "+";
            Result = Operand1 + Operand2;
        } break;

        case Op_Subtract: {
            OpText = "-";
            Result = Operand1 - Operand2;
        } break;

        case Op_Multiply: {
            OpText = "*";
            Result = Operand1 * Operand2;
        } break;

        case Op_Divide: {
            OpText = "/";
            Result = Operand1 / Operand2;
        } break;

        case Op_Count: {
            assert(!"Invalid case!");
        };
    }

    printf("%d %s %d = %d\n", Operand1, OpText, Operand2, Result);

    return 0;
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 3) {
        fprintf(stderr, "Usage: %s Number1 Number2\n", ArgVals[0]);
        exit(1);
    }

    sscanf(ArgVals[1], "%d", &Operand1);
    sscanf(ArgVals[2], "%d", &Operand2);

    pthread_t Threads[Op_Count];
    operation ThreadArguments[Op_Count] = {
        Op_Add, Op_Subtract, Op_Multiply, Op_Divide
    };

    for(int Idx = 0; Idx < Op_Count; ++Idx) {
        pthread_create(Threads + Idx, 0, threadFunc, ThreadArguments + Idx);
    }

    for(int Idx = 0; Idx < Op_Count; ++Idx) {
        pthread_join(Threads[Idx], 0);
    }

    return 0;
}
