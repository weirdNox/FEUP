#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *v = 0;
    int vCount = 0;
    int vCapacity = 0;
    for(;;)
    {
        int new;
        if(scanf("%d", &new) < 1)
        {
            break;
        }

        if(vCount == vCapacity)
        {
            vCapacity += 10;
            v = realloc(v, sizeof(int)*vCapacity);
        }

        v[vCount++] = new;
    }

    float *avg = malloc(sizeof(float)*vCount);
    for(int i = 0; i < vCount; ++i)
    {
        if(i == 0)
        {
            avg[i] = (float)(v[0] + v[1])/2.0f;
        }
        else if(i == vCount - 1)
        {
            avg[i] = (float)(v[vCount-2] + v[vCount-1])/2.0f;
        }
        else
        {
            avg[i] = (float)(v[i-1] + v[i] + v[i+1])/3.0f;
        }
    }
    for(int i = 0; i < vCount; ++i)
    {
        printf("%.2f ", avg[i]);
    }
    puts("");

    return 0;
}
