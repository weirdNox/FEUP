#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int match_line(int fd, char *str);

typedef struct {
    pthread_t Thread;
    char *FileName;
} thread_info;

char *SearchStr;

void *threadRoutine(void *RawArg) {
    thread_info *Arg = (thread_info *)RawArg;
    int FileDesc = open(Arg->FileName, O_RDONLY);
    if(FileDesc < 0) {
        return 0;
    }

    int LineNumber;
    while((LineNumber = match_line(FileDesc, SearchStr)) != 0) {
        printf("%s:\t%d\n", Arg->FileName, LineNumber);
    }

    close(FileDesc);

    return 0;
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 3) {
        fprintf(stderr, "Usage: %s [Text to search] [Files to search...]\n", ArgVals[0]);
        exit(1);
    }

    SearchStr = ArgVals[1];

    int NumberOfThreads = ArgCount - 2;
    thread_info *Threads = malloc(sizeof(*Threads)*NumberOfThreads);

    for(int Idx = 0; Idx < NumberOfThreads; ++Idx) {
        thread_info *Thread = Threads + Idx;
        Thread->FileName = ArgVals[2 + Idx];
        pthread_create(&Thread->Thread, 0, threadRoutine, Thread);
    }

    for(int Idx = 0; Idx < NumberOfThreads; ++Idx) {
        thread_info *Thread = Threads + Idx;
        pthread_join(Thread->Thread, 0);
    }

    free(Threads);

    return 0;
}
