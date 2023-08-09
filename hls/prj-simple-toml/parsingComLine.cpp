#include "parsingComLine.h"

using namespace TCLAP;

ParsingComLine::ParsingComLine(int argc, char *argv[]) {
    CmdLine cmd("Parsing command Line", ' ', "1.0", false);
    ValueArg< std::string > inFileArg("i", "input", "Input file dir & name", true, "../../samples/", "string", cmd);
    ValueArg< std::string > outFileArg("o", "output", "Output file dir", true, "../build", "string", cmd);
    ValueArg< std::string > cgfFileArg("c", "cfg", "Gold file dir", true, "../build", "string", cmd);

    cmd.parse(argc, argv);

    InFile_ = inFileArg.getValue();
    OutFile_ = outFileArg.getValue();
    CfgFile_ = cgfFileArg.getValue();
}
