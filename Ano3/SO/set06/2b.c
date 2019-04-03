#include <stdio.h>
#include <pthread.h>

enum {
    ReaderThreadCount = 2,
    WriterThreadCount = 2,
};

typedef struct {
    pthread_mutex_t InMutex;
    pthread_mutex_t OutMutex;
    pthread_cond_t WriterWait;
    unsigned int InReaders;
    unsigned int OutReaders;
} lock;

lock Lock;
volatile int M, N;

void aquireReadLock() {
    pthread_mutex_lock(&Lock.InMutex);
    ++Lock.InReaders;
    pthread_mutex_unlock(&Lock.InMutex);
}

void releaseReadLock() {
    pthread_mutex_lock(&Lock.OutMutex);
    if(++Lock.OutReaders == Lock.InReaders) {
        pthread_cond_signal(&Lock.WriterWait);
    }
    pthread_mutex_unlock(&Lock.OutMutex);
}

void aquireWriteLock() {
    pthread_mutex_lock(&Lock.InMutex);
    pthread_mutex_lock(&Lock.OutMutex);
    while(Lock.InReaders != Lock.OutReaders) {
        pthread_cond_wait(&Lock.WriterWait, &Lock.OutMutex);
    }
    pthread_mutex_unlock(&Lock.OutMutex);
}

void releaseWriteLock() {
    pthread_mutex_unlock(&Lock.InMutex);
}

void *readerThread(void *RawArg) {
    (void)(RawArg);
    for(int I = 0; I < 50000000; ++I) {
        aquireReadLock();
        if((I % 1000000) == 0) {
            printf("M: %9d\tN: %9d\n", M, N);
        }
        releaseReadLock();
    }
    return 0;
}

void *writerThread(void *RawArg) {
    (void)(RawArg);
    for(int I = 0; I < 50000000; ++I) {
        aquireWriteLock();
        ++M;
        ++N;
        releaseWriteLock();
    }
    return 0;
}

int main() {
    pthread_mutex_init(&Lock.InMutex, 0);
    pthread_mutex_init(&Lock.OutMutex, 0);
    pthread_cond_init(&Lock.WriterWait, 0);

    pthread_t Readers[ReaderThreadCount];
    for(int I = 0; I < ReaderThreadCount; ++I) {
        pthread_create(Readers + I, 0, readerThread, 0);
    }

    pthread_t Writers[WriterThreadCount];
    for(int I = 0; I < WriterThreadCount; ++I) {
        pthread_create(Writers + I, 0, writerThread, 0);
    }

    for(int I = 0; I < ReaderThreadCount; ++I) {
        pthread_join(Readers[I], 0);
    }
    for(int I = 0; I < WriterThreadCount; ++I) {
        pthread_join(Writers[I], 0);
    }

    printf("END ----------------------------------------\nM: %9d\tN: %9d\n", M, N);

    return 0;
}
