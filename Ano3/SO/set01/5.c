#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arrayCount(Arr) sizeof(Arr)/sizeof(*Arr)

size_t stringLength(char *String) {
    size_t Result = 0;
    for(; *String; ++String, ++Result) {}
    return Result;
}

int main(int ArgCount, char *ArgVals[]) {
    char *TestString = "Hello, World!\n";
    printf("Original: %lu\tCustom: %lu\n", strlen(TestString), stringLength(TestString));

    if(ArgCount >= 2) {
        printf("Original: %lu\tCustom: %lu\n", strlen(ArgVals[1]), stringLength(ArgVals[1]));
    }

    return 0;
}
