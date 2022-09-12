#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ASSERT(condition)                                   \
if (!(condition)){                                           \
    fprintf(stderr, "Error in %s:\n"                          \
                    "FILE: %s\n"                               \
                    "LINE: %d\n"                                \
                    "FUNCTION: %s\n",                            \
           #condition, __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
    abort();}

/// A data structure that contains pointer on a begin of a line in a characters array and line's length
struct fileLines
{
    char* lineStart = NULL;///< a pointer on the begin of line
    size_t lineLen = 0;///< length of line
    size_t lineIndex = 0;                   ///
};

/**
 * @brief A function for sorting lines in text in alphabetical order
 * @param [in] processed - pointer on file with sorted text
 * @param [in] source - pointer on file with source text
 * @return Return nothing
 */
void upgradePoem(FILE* const processed, FILE* const source);

/**
 * @brief A function that compares strings in alphabetical order
 * @param [in] str1 - the first string
 * @param [in] str2 - the second string
 * @return 0              - if strings are the same
 *         positive value - if str1 is after str2 in alphabetical order
 *         negative value - if str1 is before str2 in alphabetical order
 */
int leftLineCmp(const void* str1, const void* str2);

/**
 * @brief A function that skips non-letter characters in a string
 * @param [in] str - a pointer on the string
 * @return Pointer to a letter character in the source string
 */
const char* leftEatPunct(const char* str);

/**
 * @brief A function that count how many characters are in the file
 * @param [in] file - a pointer on the file
 * @return Count of characters
 */
size_t fileSize(FILE* const file);


/**
 * @brief A function for sorting array of strings with merge sorting
 * @param [in] lines - array that we need to sort
 * @param [in] left - index of begin of the array
 * @param [in] right - index of end of the array
 * @return Return nothing
 */
void mergeSort(void* const data, void* const supporting, size_t left, size_t right, size_t size, int (* comparator)(const void *, const void *));

int rightLineCmp(const void* str1, const void* str2);

int sourceLineCmp(const void* str1, const void* str2);

void rightEatPunct(const char* str, int* len);

void fillTheFile(FILE* processed, fileLines* data, fileLines* support, size_t nLines, int (* comparator)(const void *, const void *));

void countInText(char* buf, char search, size_t* count);

struct TEXT
{
    char * buf = NULL;
    size_t nChar = 0;
    char filelines * = NULL;
    size_t nLines = 0;
};


