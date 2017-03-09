#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct
{
    char tag[3];
    char title[31];
    char artist[31];
    char album[31];
    char year[5];
    char comment[31];
    char number;
    int genre;
} Metadata;

char *genres[] = {
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
};

int main()
{
    FILE *file = fopen("musica.mp3", "rb");
    if(!file)
    {
        fprintf(stderr, "Erro a abrir ficheiro!\n");
        return -1;
    }

    Metadata data = {};
    fseek(file, -128, SEEK_END);
    fread(&data.tag, sizeof(data.tag), 1, file);
    fread(&data.title, sizeof(data.title)-1, 1, file);
    fread(&data.artist, sizeof(data.artist)-1, 1, file);
    fread(&data.album, sizeof(data.album)-1, 1, file);
    fread(&data.year, sizeof(data.year)-1, 1, file);
    fread(&data.comment, sizeof(data.comment)-1, 1, file);
    fread(&data.genre, 1, 1, file);

    if(!data.comment[28])
    {
        data.number = data.comment[29];
    }

    if(strncmp(data.tag, "TAG", 3) == 0)
    {
        printf("Título: %s\n", data.title);
        printf("Artista: %s\n", data.artist);
        printf("Álbum: %s\n", data.album);
        printf("Ano: %s\n", data.year);
        printf("Comentário: %s\n", data.comment);
        printf("Número: %d\n", data.number);
        printf("Género: %s\n", genres[data.genre]);
    }

    return 0;
}
