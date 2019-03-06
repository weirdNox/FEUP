#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

static void printPids() {
    pid_t Pid = getpid();
    pid_t ParentPid = getppid();
    printf("PID: %d\n└ Parent PID: %d\n\n", Pid, ParentPid);
}

int main() {
    printPids();

    pid_t ChildPid = fork();
    if(ChildPid) {
        // NOTE(nox): This is the original process
        int ExitStatus;
        wait(&ExitStatus);
        printf("Child exit status: %d\n", WEXITSTATUS(ExitStatus));
    }
    else {
        // NOTE(nox): This is the child process
        printPids();

        pid_t GrandChildPid = fork();
        if(GrandChildPid) {
            // NOTE(nox): This is the child process
            int ExitStatus;
            wait(&ExitStatus);
            printf("Grand-child exit status: %d\n", WEXITSTATUS(ExitStatus));
        }
        else {
            // NOTE(nox): This is the grand-child process
            printPids();
            return 3;
        }

        return 2;
    }

    return 0;
}
