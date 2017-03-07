#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *file = fopen("pagina.html", "r");
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    void *buffer = malloc(size);
    fread(buffer, size, 1, file);

    char *save1 = 0, *save2 = 0;
    char *token = strtok_r(buffer, "<>", &save1);
    while(token)
    {
        if(*token == 'a')
        {
            char *link = strtok_r(token, "\"", &save2);
            link = strtok_r(0, "\"", &save2);
            char *title = strtok_r(0, "<>", &save1);
            printf("%s - %s\n", title, link);
        }
        token = strtok_r(0, "<>", &save1);
    }

    return 0;
}
