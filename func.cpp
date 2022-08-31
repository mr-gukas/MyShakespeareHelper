#include "poem.h"

int lineCmp(const void* str1, const void* str2)
{
    ASSERT(str1 != NULL)
    ASSERT(str2 != NULL)

    const char* line1 = ((const fileLines*) str1)->lineStart;
    const char* line2 = ((const fileLines*) str2)->lineStart;

    while (*line1 && *line2)
    {
        line1 = eatPunct(line1);
        line2 = eatPunct(line2);

        if (*line1 && *line2 && toupper(*line1) != toupper(*line2))
        {
            return (toupper(*line1) - toupper(*line2));
        }
        else if (*line2 && *line2)
        {
            ++line1;
            ++line2;
        }
    }

    if (!(*line1 || *line2))
    {
        return 0;
    }
    else if (!(*line1))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

const char* eatPunct(const char* str)
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

    fileLines* lines = (fileLines*) calloc(nLines, sizeof(fileLines));

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

    mergeSort(lines, 0, nLines - 1);

    for (long index = 0; index < nLines; ++index)
    {
        fputs(lines[index].lineStart, processed);
    }

    free(chars);
    free(lines);
}


void linesSort(fileLines* const lines, const long arrLen)
{
    ASSERT(lines != NULL)

    for (long i = 0; i < arrLen; i++)
    {
        for (long j = i + 1; j < arrLen; j++)
        {
            if (lineCmp(&lines[i], &lines[j]) > 0)
            {
                fileLines temp = lines[i];
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

void mergeSort(fileLines* const lines, size_t left, size_t right)
{
    ASSERT(lines != NULL)

    if (left == right) return;

    size_t middle = (left + right) / 2;

    mergeSort(lines, left, middle);
    mergeSort(lines, middle + 1, right);

    size_t subarray1  = left;
    size_t subarray2 = middle + 1;

    fileLines* temp = (fileLines*) calloc(right + 1, sizeof(fileLines));

    for (size_t index = 0; index < right - left + 1; ++index)
    {

        if ((subarray2 > right) ||
           ((subarray1 <= middle) &&
             lineCmp((const fileLines*) &lines[subarray1], (const fileLines*) &lines[subarray2]) < 0))
        {
            temp[index] = lines[subarray1];
            ++subarray1;
        }
        else
        {
            temp[index] = lines[subarray2];
            ++subarray2;
        }
    }

    for (size_t index = 0; index < right - left + 1; ++index)
    {
        lines[left + index] = temp[index];
        free(temp);
    }
}


