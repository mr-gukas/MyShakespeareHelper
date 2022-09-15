#include "poem.h"

int main(int argc, char* argv[])
{
    ASSERT(argc == 3)

    FILE* source    = fopen(argv[1], "r");
    FILE* processed = fopen(argv[2], "w+");

    ASSERT(source != NULL && processed != NULL)

    TEXT text = {};

    upgradePoem(&text, source);
    
    fileLines* supporting = (fileLines*) calloc(text.nLines + 1, sizeof(fileLines));

    fillTheFile(processed, text.lines, supporting, text.nLines, leftLineCmp);
    fillTheFile(processed, text.lines, supporting, text.nLines, rightLineCmp);
    fillTheFile(processed, text.lines, supporting, text.nLines, sourceLineCmp);

    free(supporting);
    free(text.buf);
    free(text.lines);

    fclose(source);
    fclose(processed);

    return 0;
}
