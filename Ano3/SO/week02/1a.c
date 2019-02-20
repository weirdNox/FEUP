#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <common.c>

int main(int ArgCount, char *ArgVals[]) {
    if(ArgCount < 2) {
        char *ErrorMsg = "Missing file argument\n";
        write(STDOUT_FILENO, ErrorMsg, stringLength(ErrorMsg));
        return 1;
    }

    int FileDesc = open(ArgVals[1], O_RDONLY);
    if(FileDesc < 0) {
        char *ErrorMsg = "Could not open the specified file\n";
        write(STDOUT_FILENO, ErrorMsg, stringLength(ErrorMsg));
        return 1;
    }

    char Buffer[1<<10];
    int ByteSize = 0;
    for(;;) {
        int BytesRead = read(FileDesc, Buffer, arrayCount(Buffer));
        if(BytesRead <= 0) {
            break;
        }

        write(STDOUT_FILENO, Buffer, BytesRead);
        ByteSize += BytesRead;
    }

    char Message[1<<10];
    midx MessageSize = formatString(Message, arrayCount(Message), "\n---------------------------\nFile size: %d bytes\n", ByteSize);
    write(STDOUT_FILENO, Message, MessageSize);

    return 0;
}
