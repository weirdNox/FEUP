#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <common.c>

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 3) {
        fprintf(stderr, "Usage: %s File Offset\n", ArgVals[0]);
        return 1;
    }

    int File = open(ArgVals[1], O_RDONLY);
    if(File < 0) {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    int Offset;
    sscanf(ArgVals[2], "%d", &Offset);

    struct stat Stat;
    fstat(File, &Stat);
    int FileSize = Stat.st_size;

    if(Offset >= FileSize) {
        fprintf(stderr, "Offset is greater than file size\n");
        return 1;
    }

    int SampleSize = FileSize/10;
    if(Offset + SampleSize > FileSize) {
        SampleSize = FileSize - Offset;
    }

    char *Sample = malloc(SampleSize + 1);
    lseek(File, Offset, SEEK_SET);
    read(File, Sample, SampleSize);
    Sample[SampleSize] = 0;

    printf("%s\n", Sample);

    return 0;
}
