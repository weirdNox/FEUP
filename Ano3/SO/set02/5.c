#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>

#define arrayCount(Arr) (sizeof(Arr)/sizeof(*(Arr)))

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        char Message[1024];
        int Length = snprintf(Message, arrayCount(Message), "Usage: %s FileToCat [DestFile]\n", ArgVals[0]);
        write(STDOUT_FILENO, Message, Length);
        return 1;
    }

    int FileDesc = open(ArgVals[1], O_RDONLY);
    if(FileDesc < 0) {
        return 1;
    }

    if(ArgCount >= 3) {
        // NOTE(nox): Output to file
        int OutputDesc = open(ArgVals[2], O_WRONLY | O_CREAT | O_EXCL, 0644);
        if(OutputDesc >= 0) {
            dup2(OutputDesc, STDOUT_FILENO);
            close(OutputDesc);
        }
        else {
            char Message[1024];
            int Length = snprintf(Message, arrayCount(Message), "Could not open output file \"%s\"!\n\n",
                                  ArgVals[2]);
            write(STDOUT_FILENO, Message, Length);
        }
    }

    int FileLength = 0;
    char Buff[64];
    for(int ByteCount; (ByteCount = read(FileDesc, Buff, arrayCount(Buff)));) {
        write(STDOUT_FILENO, Buff, ByteCount);
        FileLength += ByteCount;
    }

    close(FileDesc);

    {
        char Message[1024];
        int Length = snprintf(Message, arrayCount(Message), "File size: %d bytes\n", FileLength);
        write(STDOUT_FILENO, Message, Length);
    }

    return 0;
}
