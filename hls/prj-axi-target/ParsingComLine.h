#pragma once
#include <tclap/CmdLine.h>

#include <map>
#include <string>
#include <toml.hpp>

class ParsingComLine {
   public:
    ParsingComLine(int argc, char *argv[]);
    ParsingComLine();

    std::string InFile_;
    std::string OutFile_;
    std::string CfgFile_;
    std::vector< size_t > m_framesNum = {0, 2048};
};