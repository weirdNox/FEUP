#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int ArgCount, char *ArgVals[], char *EnvVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s FileToCompile\n", ArgVals[0]);
        exit(1);
    }

    char *Arguments[] = {
        "gcc",
        ArgVals[1],
        0
    };
    execve("/usr/bin/gcc", Arguments, EnvVals);

    return 0;
}
