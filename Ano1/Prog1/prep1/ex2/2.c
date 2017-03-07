#include <stdio.h>

char movimento(int x0, int y0, int x1, int y1)
{
    if(x1-x0 > 0)
    {
        return 'D';
    }
    else if(x1-x0 < 0)
    {
        return 'E';
    }
    else if(y1-y0 > 0)
    {
        return 'C';
    }
    else if(y1-y0 < 0)
    {
        return 'B';
    }

    return 'X';
}

int main()
{
    int prevX, prevY;
    scanf("%d %d", &prevX, &prevY);

    int x, y;
    while(scanf("%d %d", &x, &y) != EOF)
    {
        printf("%c", movimento(prevX, prevY, x, y));
        prevX = x;
        prevY = y;
    }
    puts("");

    return 0;
}
