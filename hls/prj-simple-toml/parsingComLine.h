#pragma once
#include <tclap/CmdLine.h>

#include <map>
#include <string>
#include <toml.hpp>

class ParsingComLine
{
public:
    ParsingComLine(int argc, char *argv[]);
    ParsingComLine();

    std::string m_dirInFile;
    std::string m_dirOutFile;
    //     std::string m_dirOutTuserFile;
    //     std::string m_dataDescriptionFile;
    //     std::string m_pipelineSettingsFile;
    //     std::vector<size_t> m_framesNum = {0, 2048};
    //     int m_DbgLevel = 0; // 0 - without debug messages
    //     std::map<std::string, int> m_blockDbgLevel;
};