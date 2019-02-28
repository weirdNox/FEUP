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

void printTestsFromFile(int File) {
    for(;;) {
        test Test;

        u32 Offset = 0;
        u8 Buffer[sizeof(Test.StudentName) + sizeof(Test.Grades)];
        int BytesRead = read(File, Buffer, arrayCount(Buffer));
        if(BytesRead != sizeof(Buffer)) {
            return;
        }

        for(u32 I = 0; I < sizeof(Test.StudentName); ++I) {
            Test.StudentName[I] = Buffer[Offset+I];
        }
        Offset += sizeof(Test.StudentName);

        for(u32 I = 0; I < sizeof(Test.Grades); ++I) {
            *(((u8 *)Test.Grades) + I) = Buffer[Offset+I];
        }
        Offset += sizeof(Test.Grades);

        printf("Student %s: %d %d %d\n", Test.StudentName, Test.Grades[0], Test.Grades[1], Test.Grades[2]);
    }
}

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        fprintf(stderr, "Usage: %s File\n", ArgVals[0]);
        return 1;
    }

    int File = open(ArgVals[1], O_RDONLY);
    if(File < 0) {
        fprintf(stderr, "Could not open destination file :(\n");
        return 1;
    }
    printTestsFromFile(File);

    return 0;
}
