#include "parsingComLine.h"

using namespace TCLAP;

ParsingComLine::ParsingComLine(int argc, char *argv[])
{
    CmdLine cmd("Parsing command Line", ' ', "1.0", false);
    ValueArg<std::string> inputFileArg("i", "input", "Input file dir & name", true, "generated_data/", "string", cmd);
    ValueArg<std::string> outputFileArg("o", "output", "Output file dir", true, "../build/results/", "string", cmd);
    // ValueArg<std::string> outputTuserFileArg("u", "output_tuser", "Output file dir Tuser", false, "../build/results/",
    //                                          "string", cmd);
    // ValueArg<std::string> dataDescription("m", "datadescrp", "File dir & name for metainfo", true, "../samples/dev/",
    //                                       "string", cmd);
    // ValueArg<std::string> pipelineSettings("p", "pipeline", "File dir & name for pipeline settings", true,
    //                                        "../samples/dev/", "string", cmd);

    // MultiArg<std::size_t> framesNumber("f", "frames", "Number of frames to read", false, "string", cmd);

    // MultiArg<std::string> blockDbgEn("d", "blockdbgen", "Enable debug messages for block", false, "string", cmd);
    // ValueArg<int> DbgLevel("v", "verbose", "Debug message level. 0 - min level(without debug message)", false, 0,
    //                        "int", cmd);

    cmd.parse(argc, argv);

    m_dirInFile = inputFileArg.getValue();
    m_dirOutFile = outputFileArg.getValue();
    // m_dirOutTuserFile = outputTuserFileArg.getValue();
    // m_dataDescriptionFile = dataDescription.getValue();
    // m_pipelineSettingsFile = pipelineSettings.getValue();
    // auto framesNum = framesNumber.getValue();

    // for (const auto &value : framesNum)
    // {
    //     auto i = &value - &framesNum[0];
    //     m_framesNum[i] = value;
    // }

    // m_DbgLevel = DbgLevel.getValue();
    // auto DebugBlocks = blockDbgEn.getValue();
    // for (const auto &block : DebugBlocks)
    // {
    //     m_blockDbgLevel[block] = m_DbgLevel;
    // }
}
