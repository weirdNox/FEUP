#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *v = 0;
    int vCount = 0;
    for(;;)
    {
        int new;
        if(scanf("%d", &new) < 1)
        {
            break;
        }

        v = realloc(v, sizeof(int)*(vCount+1));
        v[vCount++] = new;
    }

    v = realloc(v, sizeof(*v)*(2*vCount-1));
    for(int i = vCount - 1; i >= 1; --i)
    {
        v[2*i] = v[i];
        v[2*i-1] = (v[i-1] + v[i])/2;
    }

    for(int i = 0; i < vCount*2-1; ++i)
    {
        printf("%d ", v[i]);
    }
    puts("");

    return 0;
}
