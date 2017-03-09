#include <stdio.h>

int main()
{
    char wall;
    int width, height;
    scanf("%c %d %d", &wall, &height, &width);

    for(int x = 0; x < width; ++x)
    {
        printf("%c", wall);
    }
    puts("");
    for(int y = 0; y < height - 2; ++y)
    {
        printf("%c", wall);
        for(int x = 0; x < width - 2; ++x)
        {
            printf(" ");
        }
        printf("%c\n", wall);
    }
    for(int x = 0; x < width; ++x)
    {
        printf("%c", wall);
    }
    puts("");

    return 0;
}
