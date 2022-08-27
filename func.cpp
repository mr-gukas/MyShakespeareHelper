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

void upgradePoem(FILE* processed, FILE* source)
{
    ASSERT(processed != NULL)
    ASSERT(source    != NULL)

    char** lines = (char**) malloc(sizeof(char*));;
    size_t index = 0;

    while (!feof(source))
    {
        lines[index] = (char*) malloc(sizeof(char)* 256);
        fgets(lines[index], 254, source);
        ++index;
        lines = (char**) realloc(lines, sizeof(char*)*(index + 1));
    }

    linesSort(lines, index);

    for (size_t i = 0; i < index; i++)
    {
        fputs(lines[i], processed);
        free(lines[i]);
    }

    free(lines);
}


void linesSort(char** lines, size_t arrLen)
{
    ASSERT(lines != NULL)

    for (size_t i = 0; i < arrLen; i++)
    {
        for (size_t j = i + 1; j < arrLen; j++)
        {
            if (lineCmp(lines[i], lines[j]) > 0)
            {
                char *temp = lines[i];
                lines[i]   = lines[j];
                lines[j]   = temp;
            }

        }
    }
}

