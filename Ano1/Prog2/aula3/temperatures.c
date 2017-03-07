#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n; // the number of temperatures to analyse
    scanf("%d", &n); fgetc(stdin);
    char temps[257]; // the n temperatures expressed as integers ranging from -273 to 5526
    fgets(temps, 257, stdin); // the n temperatures expressed as integers ranging from -273 to 5526

    int found = 0;
    int result = 0x7fffffff;
    int numBytes = 0;
    for(int i = 0; i < n; ++i)
    {
        int num, bytes;
        sscanf(temps+numBytes, "%d %n", &num, &bytes);
        numBytes += bytes;
        if(num > 0 && num == -result)
        {
            found = 1;
            result = num;
        }
        else if(abs(num) < abs(result))
        {
            found = 1;
            result = num;
        }
    }

    if(found)
        printf("%d\n", result);
    else
        printf("0\n");

    return 0;
}
