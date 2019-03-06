#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arrayCount(Arr) sizeof(Arr)/sizeof(*Arr)

char *Months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int numberOfMonthsBetween(char *Month1, char *Month2) {
    int FirstIs1;
    int FirstIndex = -1;

    for(size_t Index = 0; Index < arrayCount(Months); ++Index) {
        if(strncasecmp(Month1, Months[Index], strlen(Month1)) == 0) {
            FirstIs1 = 1;
            FirstIndex = Index;
            break;
        }
        else if(strncasecmp(Month2, Months[Index], strlen(Month2)) == 0) {
            FirstIs1 = 0;
            FirstIndex = Index;
            break;
        }
    }

    if(FirstIndex != -1) {
        for(size_t Index = FirstIndex; Index < arrayCount(Months); ++Index) {
            if(!FirstIs1 && strncasecmp(Month1, Months[Index], strlen(Month1)) == 0) {
                return Index - FirstIndex;
            }
            else if(FirstIs1 && strncasecmp(Month2, Months[Index], strlen(Month2)) == 0) {
                return Index - FirstIndex;
            }
        }
    }

    return -1;
}

int main(int ArgCount, char *ArgVals[]) {
    char **Month = Months;
    for(size_t Index = 0; Index < arrayCount(Months); ++Index) {
        printf("%s\n", *Month++);
    }

    if(ArgCount >= 3) {
        printf("Difference: %d\n", numberOfMonthsBetween(ArgVals[1], ArgVals[2]));
    }
}
