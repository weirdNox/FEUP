#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define arrayCount(Arr) (sizeof(Arr)/sizeof(*(Arr)))
long long du(int fd);

typedef struct {
    pthread_t Thread;
    char FileName[1024];
} thread_info;

void *threadRoutine(void *RawArg) {
    thread_info *Arg = (thread_info *)RawArg;
    int FileDesc = open(Arg->FileName, O_RDONLY);
    if(FileDesc < 0) {
        return 0;
    }

    int FileLength = du(FileDesc);
    printf("%s:\t%d bytes\n", Arg->FileName, FileLength);

    close(FileDesc);

    return 0;
}

int main(int ArgCount, char *ArgVals[]) {
    thread_info Thread;
    int Length = read(STDIN_FILENO, Thread.FileName, arrayCount(Thread.FileName)-1);
    if(Thread.FileName[Length-1] == '\n') {
        Thread.FileName[Length-1] = 0;
    }
    else {
        Thread.FileName[Length] = 0;
    }

    pthread_create(&Thread.Thread, 0, threadRoutine, &Thread);
    pthread_join(Thread.Thread, 0);

    return 0;
}
