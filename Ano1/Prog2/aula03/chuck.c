#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char MESSAGE[101];
    fgets(MESSAGE, 101, stdin);

    int len = strlen(MESSAGE)-1;
    char seriesOf = -1;
    for(int i = 0; i < len; ++i)
    {
        for(int j = 6; j >= 0; --j)
        {
            int bit = (MESSAGE[i] & 1<<j)>>j;
            if(bit != seriesOf)
            {
                if(seriesOf != -1)
                {
                    printf(" ");
                }
                seriesOf = bit;
                if(bit)
                {
                    printf("0 ");
                }
                else
                {
                    printf("00 ");
                }
            }

            printf("0");
        }
    }

    return 0;
}
