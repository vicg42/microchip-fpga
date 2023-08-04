#include "parsingComLine.h"

using namespace TCLAP;

ParsingComLine::ParsingComLine(int argc, char *argv[])
{
    CmdLine cmd("Parsing command Line", ' ', "1.0", false);
    ValueArg<std::string> inputFileArg("i", "input", "Input file dir & name", true, "generated_data/", "string", cmd);
    ValueArg<std::string> outputFileArg("o", "output", "Output file dir", true, "../build/results/", "string", cmd);

    cmd.parse(argc, argv);

    m_dirInFile = inputFileArg.getValue();
    m_dirOutFile = outputFileArg.getValue();
}
