#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ASSERT(condition)                      \
if (!(condition)){                              \
    printf("Error in %s:\n", #condition);        \
    printf("FILE: %s\n", __FILE__);               \
    printf("LINE: %d\n", __LINE__);                \
    printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);  \
}

/**
 * @brief A function for sorting array of strings
 * @param [in] lines - array that we need to sort
 * @param [in] arrLen - length of the lines
 * @return Return nothing
 */
void linesSort(char** lines, size_t arrLen);

/**
 * @brief A function for sorting lines in text in alphabetical order
 * @param [in] processed - pointer on file with sorted text
 * @param [in] source - pointer on file with source text
 * @return Return nothing
 */
void upgradePoem(FILE* processed, FILE* source);

/**
 * @brief A function that compares strings in alphabetical order
 * @param [in] str1 - the first string
 * @param [in] str2 - the second string
 * @return 0              - if strings are the same
 *         positive value - if str1 is after str2 in alphabetical order
 *         negative value - if str1 is before str2 in alphabetical order
 */
int lineCmp(char* str1, char* str2);

/**
 * @brief A function that skips non-letter characters in a string
 * @param [in] str - a pointer on the string
 * @return [in] Pointer to a letter character in the source string
 */
char* eatPunct(char* str);


