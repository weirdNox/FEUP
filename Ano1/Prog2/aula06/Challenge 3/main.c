#include <stdio.h>
#include <string.h>

#define arrayCount(a) sizeof(a)/sizeof(*(a))
typedef struct
{
    char tower[256];
    int size;
} Tower;

void printTower(Tower *tower)
{
    for(int i = 0; i < tower->size; ++i)
    {
        printf("%c ", tower->tower[i]);
    }
    puts("");
}

void flip(Tower *tower, int n)
{
    printf("flip(%d): ", n);
    for(int i = 0; n > 1; ++i, n -= 2)
    {
        char temp = tower->tower[i];
        tower->tower[i] = tower->tower[i+n-1];
        tower->tower[i+n-1] = temp;
    }

    printTower(tower);
}

int main()
{
    int first = 1;
    Tower tower;
    while(fgets(tower.tower, arrayCount(tower.tower), stdin))
    {
        if(!first)
        {
            puts("======================================================================");
        }
        first = 0;
        tower.size = strlen(tower.tower)-1;
        puts("Original pancake tower");
        printTower(&tower);

        for(int toSort = tower.size; toSort > 1; --toSort)
        {
            int maxIdx = 0;
            for(int i = 1; i < toSort; ++i)
            {
                if(tower.tower[i] > tower.tower[maxIdx])
                {
                    maxIdx = i;
                }
            }

            if(maxIdx != toSort-1)
            {
                if(maxIdx != 0)
                {
                    flip(&tower, maxIdx+1);
                }
                flip(&tower, toSort);
            }
        }

        puts("Sorted pancake tower");
        printTower(&tower);
    }

    return 0;
}
