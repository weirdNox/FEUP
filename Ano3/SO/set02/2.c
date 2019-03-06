#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <common.c>

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        char Message[] = "PREFIX should be specified!\n";
        write(STDERR_FILENO, Message, arrayCount(Message)-1);
        return 1;
    }

    char *Prefix = ArgVals[1];
    int PrefixLength = strlen(Prefix);
    char DestExtension[] = ".mrg";
    char *DestName = malloc(PrefixLength + sizeof(DestExtension));
    strcpy(DestName, Prefix);
    strcpy(DestName+PrefixLength, DestExtension);
    int DestFile = open(DestName, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if(DestFile < 0) {
        char Message[] = "Could not open destination file\n";
        write(STDERR_FILENO, Message, arrayCount(Message)-1);
        return 1;
    }

    char *SrcName = malloc(PrefixLength + 3);
    strcpy(SrcName, Prefix);
    SrcName[PrefixLength + 0] = 'a';
    SrcName[PrefixLength + 1] = 'a';
    SrcName[PrefixLength + 2] =  0;

    for(;;) {
        int SrcFile = open(SrcName, O_RDONLY);
        if(SrcFile < 0) {
            break;
        }

        for(;;) {
            char Buffer[1<<10];
            int BytesRead = read(SrcFile, Buffer, arrayCount(Buffer));
            if(BytesRead <= 0) {
                break;
            }
            write(DestFile, Buffer, BytesRead);
        }

        close(SrcFile);

        if(SrcName[PrefixLength + 1] == 'z') {
            SrcName[PrefixLength + 0]++;
            SrcName[PrefixLength + 1] = 'a';
        }
        else {
            SrcName[PrefixLength + 1]++;
        }
    }
}
