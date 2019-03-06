#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <common.c>

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 3) {
        char *ErrorMsg = "This program needs 2 arguments: FileToRead NewFile\n";
        write(STDERR_FILENO, ErrorMsg, stringLength(ErrorMsg));
        return 1;
    }

    int OrigFile = open(ArgVals[1], O_RDONLY);
    if(OrigFile < 0) {
        char *ErrorMsg = "Could not open the specified file\n";
        write(STDERR_FILENO, ErrorMsg, stringLength(ErrorMsg));
        return 1;
    }

    int DestFile = open(ArgVals[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if(DestFile < 0) {
        char *ErrorMsg = "Could not create new file to be written\n";
        write(STDERR_FILENO, ErrorMsg, stringLength(ErrorMsg));
    }

    char Buffer[1<<10];
    for(;;) {
        int BytesRead = read(OrigFile, Buffer, arrayCount(Buffer));
        if(BytesRead <= 0) {
            break;
        }

        write(DestFile, Buffer, BytesRead);
    }

    return 0;
}
