#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include "parsingComLine.h"

int main(int argc, char *argv[])
{
    printf("Hello World!\n");

    ParsingComLine comLineArg(argc, argv);

    printf("m_dirInFile: %s\n", comLineArg.m_dirInFile.c_str());
    printf("m_dirOutFile: %s\n", comLineArg.m_dirOutFile.c_str());

    return 0;
}
