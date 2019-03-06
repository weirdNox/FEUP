#include <stdio.h>
#include <string.h>

extern char **environ;

int main(int ArgCount, char *ArgVals[]) {
    puts("COMMAND-LINE ARGUMENTS\n----------------------");
    for(int Idx = 0; Idx < ArgCount; ++Idx) {
        printf("%s\n", ArgVals[Idx]);
    }

    puts("\n");
    puts("ENVIRONMENT VARIABLES\n---------------------");
    for(char **EnvPtr = environ; *EnvPtr; ++EnvPtr) {
        char *Env = *EnvPtr;
        printf("%s\n", Env);
    }

    return 0;
}
