#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    Token_Unknown,
    Token_EOF,

    Token_Identifier,
    Token_Number,
    Token_String,
    Token_Operator,
    Token_Comment,
    Token_MultiLineComment,
} TokenType;

typedef struct
{
    FILE *file;
    int lineCount;
    int charCount;
    int whitespaceCount;
} Tokenizer;

typedef struct
{
    TokenType type;
    char text[1<<10];
} Token;

int readCharFromStream(FILE *file)
{
    int result = getc(file);

    if(result == EOF)
    {
        return result;
    }

    result &= 0xff;

    // NOTE(nox): Two bytes -> 110XXXXX
    if((result & 0xE0) == 0xC0)
    {
        result <<= 8;
        result |= (getc(file) & 0xff);
    }
    // NOTE(nox): Three bytes -> 1110XXXX
    else if((result & 0xF0) == 0xE0)
    {
        result <<= 8;
        result |= (getc(file) & 0xff);
        result <<= 8;
        result |= (getc(file) & 0xff);
    }
    // NOTE(nox): Four bytes -> 11110XXX
    else if((result & 0xF8) == 0xF0)
    {
        result <<= 8;
        result |= (getc(file) & 0xff);
        result <<= 8;
        result |= (getc(file) & 0xff);
        result <<= 8;
        result |= (getc(file) & 0xff);
    }

    return result;
}

char isWhitespace(int c)
{
    return (c == ' ' || c == '\r' || c == '\n' || c == '\t' ||
            c == '\f' || c == '\v');
}

int getChar(Tokenizer *tokenizer)
{
    int result = readCharFromStream(tokenizer->file);

    if(isWhitespace(result))
    {
        ++tokenizer->whitespaceCount;
        if(result == '\n')
        {
            ++tokenizer->lineCount;
        }
    }
    else if(result != EOF)
    {
        ++tokenizer->charCount;
    }

    return result;
}

void undoRead(Tokenizer *tokenizer, int lastResult)
{
    if(lastResult & 0xff000000)
    {
        fseek(tokenizer->file, -4, SEEK_CUR);
    }
    else if(lastResult & 0xffff0000)
    {
        fseek(tokenizer->file, -3, SEEK_CUR);
    }
    else if(lastResult & 0xffffff00)
    {
        fseek(tokenizer->file, -2, SEEK_CUR);
    }
    else
    {
        fseek(tokenizer->file, -1, SEEK_CUR);
    }
}

int lookAhead(Tokenizer *tokenizer)
{
    int result = readCharFromStream(tokenizer->file);
    if(result != EOF)
    {
        undoRead(tokenizer, result);
    }

    return result;
}

void eatWhitespace(Tokenizer *tokenizer)
{
    for(;;)
    {
        int c = lookAhead(tokenizer);
        if(c == EOF || !isWhitespace(c))
        {
            break;
        }
        getChar(tokenizer);
    }
}

Token getToken(Tokenizer *tokenizer)
{
    Token result = {};
    eatWhitespace(tokenizer);
    char c = getChar(tokenizer);
    result.text[0] = c;
    switch(c)
    {
        case EOF:
        {
            result.type = Token_EOF;
        } break;

        case '{':
        case '}':
        case '(':
        case ')':
        case '[':
        case ']':
        case '*':
        case '+':
        case '-':
        case ',':
        case ';':
        {
            result.type = Token_Operator;
            result.text[0] = c;
        } break;

        case '"':
        case '\'':
        {
            result.type = Token_String;
            char starting = c;
            int length = 0;
            result.text[length++] = c;
            for(;;)
            {
                c = getChar(tokenizer);
                if(c == EOF)
                {
                    break;
                }

                result.text[length++] = c;

                if(c == '\\')
                {
                    c = getChar(tokenizer);
                    result.text[length++] = c;
                }
                else if(c == starting)
                {
                    break;
                }
            }
            result.text[length++] = 0;
        } break;

        case '/':
        {
            int length = 0;
            result.text[length++] = c;
            int next = lookAhead(tokenizer);
            if(next == '/')
            {
                result.type = Token_Comment;
                for(;;)
                {
                    c = getChar(tokenizer);
                    if(c == '\n')
                    {
                        break;
                    }
                    result.text[length++] = c;
                }
            }
            else if(next == '*')
            {
                result.type = Token_MultiLineComment;
                for(;;)
                {
                    c = getChar(tokenizer);
                    result.text[length++] = c;
                    if(c == '*')
                    {
                        next = lookAhead(tokenizer);
                        if(next == '/')
                        {
                            c = getChar(tokenizer);
                            result.text[length++] = c;
                            break;
                        }
                    }
                }
            }
            else
            {
                result.type = Token_Operator;
            }
        } break;

        default:
        {
            if(isalpha(c))
            {
                result.type = Token_Identifier;
                int length = 0;
                result.text[length++] = c;
                for(;;)
                {
                    c = getChar(tokenizer);
                    if(isWhitespace(c) || !isalnum(c))
                    {
                        break;
                    }
                    result.text[length++] = c;
                }
            }
            else if(isdigit(c) || c == '.')
            {
                result.type = Token_Number;
                int length = 0;
                result.text[length++] = c;
                for(;;)
                {
                    c = getChar(tokenizer);
                    if(!isdigit(c) || c != '.')
                    {
                        break;
                    }

                    result.text[length++] = c;
                }
            }
        } break;
    }

    return result;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s [fileName]\n", *argv);
        return -1;
    }

    char *fileName = argv[1];
    Tokenizer tokenizer = {};
    tokenizer.lineCount = 1;
    tokenizer.file = fopen(fileName, "r");
    if(!tokenizer.file)
    {
        fprintf(stderr, "Error opening file!\n");
        return -1;
    }

    int printfCount = 0;
    int scanfCount = 0;
    int commentCount = 0;
    for(;;)
    {
        Token token = getToken(&tokenizer);
        if(token.type == Token_EOF)
        {
            break;
        }

        if(token.type == Token_MultiLineComment)
        {
            ++commentCount;
        }
        else if(token.type == Token_Identifier)
        {
            if(strcmp(token.text, "printf") == 0)
            {
                ++printfCount;
            }
            else if(strcmp(token.text, "scanf") == 0)
            {
                ++scanfCount;
            }
        }
    }

    printf("Número de linhas de código: %d\n", tokenizer.lineCount);
    printf("Tamanho médio de linhas de código (com whitespace): %.2f\n",
           (float)(tokenizer.charCount + tokenizer.whitespaceCount) / tokenizer.lineCount);
    printf("Número de carateres (sem whitespace): %d\n", tokenizer.charCount);
    printf("Número de printf: %d\n", printfCount);
    printf("Número de scanf: %d\n", scanfCount);
    printf("Número de comentários: %d\n", commentCount);

    fclose(tokenizer.file);

    return 0;
}
