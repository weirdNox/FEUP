#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int match_line(int fd, char *str);

typedef struct {
  pthread_t Thread;
  char *FileName;
  int MatchCount;
  int *MatchLines;
  sem_t WaitSem;
} thread_info;

char *SearchStr;

void *threadRoutine(void *RawArg) {
    thread_info *Arg = (thread_info *)RawArg;
    int FileDesc = open(Arg->FileName, O_RDONLY);
    if(FileDesc < 0) {
        return 0;
    }

    int Capacity = 1;
    Arg->MatchLines = malloc(sizeof(*Arg->MatchLines)*Capacity);

    int LineNumber;
    while((LineNumber = match_line(FileDesc, SearchStr)) != 0) {
        if(Arg->MatchCount == Capacity) {
            Capacity *= 2;
            Arg->MatchLines = realloc(Arg->MatchLines, sizeof(*Arg->MatchLines)*Capacity);
        }

        Arg->MatchLines[Arg->MatchCount++] = LineNumber;
    }

    close(FileDesc);
    sem_post(&Arg->WaitSem);

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

    pthread_attr_t Attributes;
    pthread_attr_init(&Attributes);
    pthread_attr_setdetachstate(&Attributes, PTHREAD_CREATE_DETACHED);

    for(int Idx = 0; Idx < NumberOfThreads; ++Idx) {
        thread_info *Thread = Threads + Idx;
        Thread->FileName = ArgVals[2 + Idx];
        Thread->MatchCount = 0;
        sem_init(&Thread->WaitSem, 0, 0);
        pthread_create(&Thread->Thread, &Attributes, threadRoutine, Thread);
    }

    pthread_attr_destroy(&Attributes);

    for(int Idx = 0; Idx < NumberOfThreads; ++Idx) {
        thread_info *Thread = Threads + Idx;
        sem_wait(&Thread->WaitSem);
        for(int MatchIdx = 0; MatchIdx < Thread->MatchCount; ++MatchIdx) {
            printf("%s:\t%d\n", Thread->FileName, Thread->MatchLines[MatchIdx]);
        }
        free(Thread->MatchLines);
    }

    free(Threads);

    return 0;
}
