#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern char **environ;

void printEnvToFile(char *FileName, char *EnvVals[]) {
    FILE *File = fopen(FileName, "w");

    for(char **EnvPtr = EnvVals;; ++EnvPtr) {
        char *Env = *EnvPtr;
        if(!Env) {
            break;
        }

        fprintf(File, "%s\n", Env);
    }

    fclose(File);
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 3) {
        fprintf(stderr, "Usage: %s ParentEnvFile ChildEnvFile", ArgVals[0]);
        exit(1);
    }

    pid_t Pid = fork();
    if(Pid < 0) {
        fprintf(stderr, "Could not fork! :(");
        exit(1);
    }
    else if(Pid) {
        // NOTE(nox): PID was returned, so this is parent
        printEnvToFile(ArgVals[1], environ);
    }
    else {
        // NOTE(nox): PID was not returned, this is the child process
        printEnvToFile(ArgVals[2], environ);
    }

    return 0;
}
