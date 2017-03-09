#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char tag[2];
    unsigned int size;
    char reserved[4];
    unsigned int pointer;
} Header;

typedef struct
{
    unsigned int size;
    int width;
    int height;
    short numPlanes;
    short bitsPerPixel;
    int compression;
    unsigned int arraySize;
} Dib;

void readAtPos(char *buffer, int x, int y, int width, int height, int bytesPerPixel)
{
    int realY = height - y - 1;
    unsigned char *pixel = (unsigned char *)(buffer + realY*width*bytesPerPixel + x*bytesPerPixel);
    printf("Na pos (%d,%d) temos RGB: %d %d %d\n", x, y, *(pixel+2), *(pixel+1), *pixel);
}

int main()
{
    FILE *file = fopen("imagem.bmp", "rb");

    Header header = {};
    fread(&header.tag, 2, 1, file);
    fread(&header.size, 4, 1, file);
    fread(&header.reserved, 4, 1, file);
    fread(&header.pointer, 4, 1, file);

    Dib dib = {};
    fread(&dib.size, 4, 1, file);
    fread(&dib.width, 4, 1, file);
    fread(&dib.height, 4, 1, file);
    fread(&dib.numPlanes, 2, 1, file);
    fread(&dib.bitsPerPixel, 2, 1, file);
    fread(&dib.compression, 4, 1, file);
    fread(&dib.arraySize, 4, 1, file);

    printf("Tamanho do ficheiro: %d\n", header.size);
    printf("Largura da imagem: %d\n", dib.width);
    printf("Altura da imagem: %d\n", dib.height);
    printf("Bits por pixel: %d\n", dib.bitsPerPixel);

    fseek(file, header.pointer, SEEK_SET);
    int size = dib.bitsPerPixel/8 * dib.arraySize;
    void *buffer = malloc(size);
    fread(buffer, size, 1, file);
    readAtPos(buffer, 0, 0, dib.width, dib.height, dib.bitsPerPixel/8);
    readAtPos(buffer, 0, 532, dib.width, dib.height, dib.bitsPerPixel/8);
    readAtPos(buffer, 443, 408, dib.width, dib.height, dib.bitsPerPixel/8);

    return 0;
}
