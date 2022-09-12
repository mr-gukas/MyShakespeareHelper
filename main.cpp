#include "poem.h"

int main(int argc, char* argv[])
{
    ASSERT(argc == 3)

    FILE* source    = fopen(argv[1], "r");
    FILE* processed = fopen(argv[2], "w+");

    ASSERT(source != NULL && processed != NULL)

    upgradePoem(processed, source);

    fclose(source);
    fclose(processed);

    return 0;
}
