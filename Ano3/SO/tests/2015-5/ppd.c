#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <semaphore.h>

#define arrayCount(Arr) (sizeof(Arr)/sizeof(*(Arr)))

long long du(int fd);

enum {
    MaxFiles = 10,
    MaxFileNameLength = 1023,
};

typedef struct {
    pthread_t Thread;
    char FileName[MaxFileNameLength+1];
    int FileLength;
    sem_t WaitSem;
} thread_info;

void *threadRoutine(void *RawArg) {
    thread_info *Arg = (thread_info *)RawArg;
    int FileDesc = open(Arg->FileName, O_RDONLY);
    if(FileDesc < 0) {
        sem_post(&Arg->WaitSem);
        return 0;
    }

    Arg->FileLength = du(FileDesc);
    close(FileDesc);

    sem_post(&Arg->WaitSem);

    return 0;
}

int main(int ArgCount, char *ArgVals[]) {
    int FileCount = 0;
    thread_info Threads[MaxFiles];

    for(int Idx = 0; Idx < MaxFiles; ++Idx) {
        thread_info *Thread = Threads + Idx;
        int Length = read(STDIN_FILENO, Thread->FileName, MaxFileNameLength);
        if(Length <= 0) {
            break;
        }

        ++FileCount;
        if(Thread->FileName[Length-1] == '\n') {
            Thread->FileName[Length-1] = 0;
        }
        else {
            Thread->FileName[Length] = 0;
        }

        Thread->FileLength = -1;
        sem_init(&Thread->WaitSem, 0, 0);
    }

    for(int Idx = 0; Idx < FileCount; ++Idx) {
        thread_info *Thread = Threads + Idx;
        pthread_create(&Thread->Thread, 0, threadRoutine, Thread);
        pthread_detach(Thread->Thread);
    }

    for(int Idx = 0; Idx < FileCount; ++Idx) {
        thread_info *Thread = Threads + Idx;
        sem_wait(&Thread->WaitSem);
        if(Thread->FileLength >= 0) {
            printf("%s:\t%d bytes\n", Thread->FileName, Thread->FileLength);
        }
    }

    return 0;
}
