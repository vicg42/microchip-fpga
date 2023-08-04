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
    // printf("m_dirOutTuserFile: %s\n", comLineArg.m_dirOutTuserFile.c_str());
    // printf("m_dataDescriptionFile: %s\n", comLineArg.m_dataDescriptionFile.c_str());
    // printf("m_pipelineSettingsFile: %s\n", comLineArg.m_pipelineSettingsFile.c_str());
    // printf("m_DbgLevel: %d\n", comLineArg.m_DbgLevel);

    return 0;
}
