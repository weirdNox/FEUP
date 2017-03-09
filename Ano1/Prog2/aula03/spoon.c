#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int width; // the number of cells on the X axis
    scanf("%d", &width);
    int height; // the number of cells on the Y axis
    scanf("%d", &height); fgetc(stdin);
    char map[32][32];
    for (int i = 0; i < height; i++) {
        char line[32]; // width characters, each either 0 or .
        fgets(line, 32, stdin); // width characters, each either 0 or .
        strcpy(map[i], line);
    }

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            if(map[y][x] == '0')
            {
                int closeRight = -1, closeBottom = -1;
                for(int i = x+1; i < width; ++i)
                {
                    if(map[y][i] == '0')
                    {
                        closeRight = i;
                        break;
                    }
                }
                for(int i = y+1; i < height; ++i)
                {
                    if(map[i][x] == '0')
                    {
                        closeBottom = i;
                        break;
                    }
                }
                printf("%d %d %d %d %d %d\n", x, y, closeRight, closeRight!=-1?y:-1,
                closeBottom!=-1?x:-1, closeBottom);
            }
        }
    }

    return 0;
}
