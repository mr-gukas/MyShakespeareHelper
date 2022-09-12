#include "poem.h"

int leftLineCmp(const void* str1, const void* str2)
{
    ASSERT(str1 != NULL)
    ASSERT(str2 != NULL)

    const char* line1 = ((const fileLines*) str1)->lineStart;
    const char* line2 = ((const fileLines*) str2)->lineStart;

    while (*line1 && *line2)
    {
        line1 = leftEatPunct(line1);
        line2 = leftEatPunct(line2);

        if (*line1 && *line2 && toupper(*line1) != toupper(*line2))
        {
            return (toupper(*line1) - toupper(*line2));
        }
        else if (*line1 && *line2)
        {
            ++line1;
            ++line2;
        }
    }

    return *line1 - *line2; 
}

const char* leftEatPunct(const char* str)
{
    ASSERT(str!= NULL)

    while (*str && !isalpha(*str))
    {
        ++str;
    }

    return str;
}

int rightLineCmp(const void* str1, const void* str2)
{    
    ASSERT(str1 != NULL)
    ASSERT(str2 != NULL)
    

    const  fileLines* line1 = (const fileLines*) str1;
    const  fileLines* line2 = (const fileLines*) str2;
    
    int index1 = (int) line1->lineLen - 1;
    int index2 = (int) line2->lineLen - 1;
    
    while (index1 != -1 && index2 != -1)
    {
        rightEatPunct(line1->lineStart, &index1);
        rightEatPunct(line2->lineStart, &index2);

        if (index1 >= 0 && index2 >= 0 && toupper(*(line1->lineStart + index1)) != toupper(*(line2->lineStart + index2)))
        {
            return toupper(*(line1->lineStart + index1)) - toupper(*(line2->lineStart + index2));
        }
        else if (index1 >= 0 && index2 >= 0)
        {
            --index1;
            --index2;
        }
    }

    return (index1 - index2); 
}
    
void rightEatPunct(const char* str, int* index)
{
    ASSERT(str != NULL)

    while (*index != -1  && !isalpha(*(str+(*index))))
    {
        --(*index);
    }
}

int sourceLineCmp(const void* str1, const void* str2)
{
    ASSERT(str1 != NULL)
    ASSERT(str2 != NULL)

    const  fileLines* line1 = (const fileLines*) str1;
    const  fileLines* line2 = (const fileLines*) str2;

    return (int) line1->lineIndex - (int) line2->lineIndex;
}

void upgradePoem(FILE* const processed, FILE* const source)
{
    ASSERT(processed != NULL)
    ASSERT(source    != NULL)

    size_t nChar    = fileSize(source);
    size_t nLines   = 0;
    char   *chars   = (char *) calloc(nChar + 2, sizeof(char));
    
    fread(chars, sizeof(char), nChar, source);

    for (size_t index = 0; index < nChar; ++index)
    {
        if (chars[index] == '\n')
        {
            ++nLines;
        }
    }

    fileLines* lines = (fileLines*) calloc(nLines + 1, sizeof(fileLines));

    size_t   line        = 0;
    size_t   lineStart   = 0;

    for (size_t  index = 1; index < nChar; index++)
    {
        if (chars[index] == '\n')
        {
            chars[index] = '\0';

            lines[line].lineStart = chars + lineStart;
            lines[line].lineLen   = index - lineStart;
            lines[line].lineIndex = line;
            lineStart             = index + 1;
            ++line;
        }

        if (lineStart > nChar)
        {
            break;
        }
    }
    
    fileLines* supporting = (fileLines*) calloc(nLines + 1, sizeof(fileLines));
    
    fillTheFile(processed, lines, supporting, nLines, leftLineCmp);
    fillTheFile(processed, lines, supporting, nLines, rightLineCmp);
    fillTheFile(processed, lines, supporting, nLines, sourceLineCmp);

    free(supporting);
    free(chars);
    free(lines);
}

size_t fileSize(FILE* const file)
{
    ASSERT(file != NULL)

    fseek(file, 0, SEEK_END);
    size_t pos = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return pos;
}

void mergeSort(void* const data, void* const supporting, size_t left, size_t right, size_t size, int (* comparator)(const void *, const void *))
{
    ASSERT(data       != NULL)
    ASSERT(supporting != NULL)
    
    char* dt = (char *) data;
    char* sp = (char *) supporting;

    if (right <= left)
    {
        return;     
    }

    size_t mid = (left + right) / 2;
          
    mergeSort(data, supporting, left,    mid  , size, comparator);
    mergeSort(data, supporting, mid + 1, right, size, comparator);

    size_t pointer_left  = left;
    size_t pointer_right = mid + 1;
    size_t k             = 0;

    for (k = left; k <= right; k++)
    {
        if (pointer_left == mid + 1)
        {      
            memcpy(sp + k * size, dt + pointer_right * size, size);
            pointer_right++ ;
        }
        else if (pointer_right == right + 1)
        {
            memcpy(sp + k * size, dt + pointer_left * size, size);
            pointer_left++;
        }
        else if (comparator((const void*) (dt + pointer_left * size), (const void*) (dt + pointer_right * size)) < 0)
        {
            memcpy(sp + k * size, dt + pointer_left * size, size);
            pointer_left++;
        }
        else
        {
            memcpy(sp + k * size, dt + pointer_right * size, size);
            pointer_right++;
        }
    }

    for (k = left; k <= right; k++)
    {
        memcpy(dt + k * size, sp + k * size, size);
    }
}

void fillTheFile(FILE* processed, fileLines* data, fileLines* support, size_t nLines, int (* comparator)(const void *, const void *))
{
    mergeSort(data, support, 0, nLines - 1, sizeof(fileLines), comparator);
    for (size_t index = 0; index < nLines; ++index)
    {
        fputs(data[index].lineStart, processed);
        fputc('\n', processed);
    }
    fputs("\n*********************************************************\n", processed);
}
    
void countInText(char* text, char search, size_t* count)
{
    size_t index = 0;

    while (*(text + index))
    {
        if (*(text + index) == search)
        {
            ++(*count);
        }
    }

}
