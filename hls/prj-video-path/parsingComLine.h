#pragma once
#include <tclap/CmdLine.h>

#include <map>
#include <string>
#include <toml.hpp>

class ParsingComLine {
   public:
    ParsingComLine(int argc, char *argv[]);
    ParsingComLine();

    std::string dirInFile_;
    std::string dirOutFile_;
    std::string dirGolFile_;
};