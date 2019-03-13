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
    int Result;
} thread_arg;

char *getOpText(operation Op) {
    char *OpText;

    switch(Op) {
        case Op_Add: {
            OpText = "+";
        } break;

        case Op_Subtract: {
            OpText = "-";
        } break;

        case Op_Multiply: {
            OpText = "*";
        } break;

        case Op_Divide: {
            OpText = "/";
        } break;

        case Op_Count: {
            assert(!"Invalid case!");
        };
    }

    return OpText;
}

void *threadFunc(void *VoidArg) {
    thread_arg *Arg = (thread_arg *)VoidArg;

    switch(Arg->Op) {
        case Op_Add: {
            Arg->Result = Arg->Operand1 + Arg->Operand2;
        } break;

        case Op_Subtract: {
            Arg->Result = Arg->Operand1 - Arg->Operand2;
        } break;

        case Op_Multiply: {
            Arg->Result = Arg->Operand1 * Arg->Operand2;
        } break;

        case Op_Divide: {
            Arg->Result = Arg->Operand1 / Arg->Operand2;
        } break;

        case Op_Count: {
            assert(!"Invalid case!");
        };
    }

    return &Arg->Result;
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
        {Operand1, Operand2, Op_Add, 0},
        {Operand1, Operand2, Op_Subtract, 0},
        {Operand1, Operand2, Op_Multiply, 0},
        {Operand1, Operand2, Op_Divide, 0}
    };

    for(operation Op = 0; Op < Op_Count; ++Op) {
        pthread_create(Threads + Op, 0, threadFunc, ThreadArguments + Op);
    }

    for(operation Op = 0; Op < Op_Count; ++Op) {
        int *Result;
        pthread_join(Threads[Op], (void **)&Result);
        printf("%d %s %d = %d\n", ThreadArguments[Op].Operand1, getOpText(Op), ThreadArguments[Op].Operand2,
               *Result);
    }

    return 0;
}
