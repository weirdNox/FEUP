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

typedef struct {
    int Operand1, Operand2;
    operation Op;
} thread_arg;

void *threadFunc(void *VoidArg) {
    thread_arg Arg = *((thread_arg *)VoidArg);

    int Result;
    char *OpText;

    switch(Arg.Op) {
        case Op_Add: {
            OpText = "+";
            Result = Arg.Operand1 + Arg.Operand2;
        } break;

        case Op_Subtract: {
            OpText = "-";
            Result = Arg.Operand1 - Arg.Operand2;
        } break;

        case Op_Multiply: {
            OpText = "*";
            Result = Arg.Operand1 * Arg.Operand2;
        } break;

        case Op_Divide: {
            OpText = "/";
            Result = Arg.Operand1 / Arg.Operand2;
        } break;

        case Op_Count: {
            assert(!"Invalid case!");
        };
    }

    printf("%d %s %d = %d\n", Arg.Operand1, OpText, Arg.Operand2, Result);

    return 0;
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 3) {
        fprintf(stderr, "Usage: %s Number1 Number2\n", ArgVals[0]);
        exit(1);
    }

    int Operand1, Operand2;
    sscanf(ArgVals[1], "%d", &Operand1);
    sscanf(ArgVals[2], "%d", &Operand2);

    pthread_t Threads[Op_Count];
    thread_arg ThreadArguments[Op_Count] = {
        {Operand1, Operand2, Op_Add},
        {Operand1, Operand2, Op_Subtract},
        {Operand1, Operand2, Op_Multiply},
        {Operand1, Operand2, Op_Divide}
    };

    for(int Idx = 0; Idx < Op_Count; ++Idx) {
        pthread_create(Threads + Idx, 0, threadFunc, ThreadArguments + Idx);
    }

    for(int Idx = 0; Idx < Op_Count; ++Idx) {
        pthread_join(Threads[Idx], 0);
    }

    return 0;
}
