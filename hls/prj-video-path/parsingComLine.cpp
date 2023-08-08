#include "parsingComLine.h"

using namespace TCLAP;

ParsingComLine::ParsingComLine(int argc, char *argv[]) {
    CmdLine cmd("Parsing command Line", ' ', "1.0", false);
    ValueArg< std::string > inputFileArg("i", "input", "Input file dir & name", true, "../../samples/", "string", cmd);
    ValueArg< std::string > outputFileArg("o", "output", "Output file dir", true, "../build", "string", cmd);
    ValueArg< std::string > goldFileArg("g", "gold", "Gold file dir", true, "../build", "string", cmd);

    cmd.parse(argc, argv);

    dirInFile_ = inputFileArg.getValue();
    dirOutFile_ = outputFileArg.getValue();
    dirGolFile_ = goldFileArg.getValue();
}
