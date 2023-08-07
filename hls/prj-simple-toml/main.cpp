#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsingComLine.h"

int main(int argc, char *argv[]) {
    printf("Hello World!\n");

    ParsingComLine comLineArg(argc, argv);

    printf("FileI: %s\n", comLineArg.dirInFile_.c_str());
    printf("FileO: %s\n", comLineArg.dirOutFile_.c_str());

    return 0;
}
