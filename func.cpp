#include "poem.h"

int lineCmp(char* str1, char* str2)
{
    ASSERT(str1 != NULL)
    ASSERT(str2 != NULL)

    while (*str1 && *str2)
    {
        str1 = eatPunct(str1);
        str2 = eatPunct(str2);

        if (*str1 && *str2 && toupper(*str1) != toupper(*str2))
        {
            return (toupper(*str1) - toupper(*str2));
        }
        else if (*str1 && *str2)
        {
            ++str1;
            ++str2;
        }
    }

    if (!(*str1 || *str2))
    {
        return 0;
    }
    else if (!(*str1))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

char* eatPunct(char* str)
{
    ASSERT(str!= NULL)

    while (*str && !isalpha(*str))
    {
        ++str;
    }

    return str;
}

void upgradePoem(FILE* const processed, FILE* const source)
{
    ASSERT(processed != NULL)
    ASSERT(source    != NULL)

    long nChar   = fileSize(source);
    long nLines  = 0;
    char *chars  = (char *) calloc(nChar, sizeof(char));

    for (long index = 0; index < nChar; ++index)
    {
        chars[index] = (char) getc(source);
        if (chars[index] == '\n')
        {
            ++nLines;
        }
    }

    struct fileLines* lines = (struct fileLines*) calloc(nLines, sizeof(struct fileLines));

    long   line        = 0;
    long   lineStart   = 0;

    for (long index = 1; index < nChar; index++)
    {
        if (chars[index] == '\n')
        {
            chars[index - 1] = '\n';
            chars[index    ] = '\0';

            lines[line].lineStart = chars + lineStart;
            lines[line].lineLen   = index - lineStart;

            lineStart = index + 1;
            ++line;
        }

        if (lineStart > nChar)
        {
            break;
        }
    }


    linesSort(lines, nLines);

    for (long index = 0; index < nLines; ++index)
    {
        fputs(lines[index].lineStart, processed);
    }

    free(chars);
    free(lines);
}


void linesSort(struct fileLines* const lines, const long arrLen)
{
    ASSERT(lines != NULL)

    for (long i = 0; i < arrLen; i++)
    {
        for (long j = i + 1; j < arrLen; j++)
        {
            if (lineCmp(lines[i].lineStart, lines[j].lineStart) > 0)
            {
                struct fileLines temp = lines[i];
                lines[i]              = lines[j];
                lines[j]              = temp;
            }

        }
    }
}

long fileSize(FILE* const file)
{
    ASSERT(file != NULL)

    fseek(file, 0, SEEK_END);
    long pos = ftell(file);
    fseek(file, 0, SEEK_SET);

    return pos;
}

