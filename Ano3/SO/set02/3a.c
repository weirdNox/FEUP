#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <common.c>

typedef struct {
	char StudentName[30];
	int Grades[3];
} test;

void writeTestToFile(int File, test Test) {
    u32 Offset = 0;
    u8 Buffer[sizeof(Test.StudentName) + sizeof(Test.Grades)];

    for(u32 I = 0; I < sizeof(Test.StudentName); ++I) {
        Buffer[Offset+I] = Test.StudentName[I];
    }
    Offset += sizeof(Test.StudentName);

    for(u32 I = 0; I < sizeof(Test.Grades); ++I) {
        Buffer[Offset+I] = *(((u8 *)Test.Grades) + I);
    }
    Offset += sizeof(Test.Grades);

    write(File, Buffer, arrayCount(Buffer));
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 6) {
        fprintf(stderr, "Usage: %s File StudentName Grade1 Grade2 Grade3\n", ArgVals[0]);
        return 1;
    }

    test Test;
    strncpy(Test.StudentName, ArgVals[2], arrayCount(Test.StudentName));
    Test.StudentName[arrayCount(Test.StudentName) - 1] = 0;
    sscanf(ArgVals[3], "%d", &Test.Grades[0]);
    sscanf(ArgVals[4], "%d", &Test.Grades[1]);
    sscanf(ArgVals[5], "%d", &Test.Grades[2]);

    int DestFile = open(ArgVals[1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if(DestFile < 0) {
        fprintf(stderr, "Could not open destination file :(\n");
        return 1;
    }
    writeTestToFile(DestFile, Test);

    return 0;
}
