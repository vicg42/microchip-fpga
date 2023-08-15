#pragma once
#include <toml.hpp>

#include "BlockBase.h"

class ReadConfig {
   public:
    ReadConfig(std::string directoryName, std::vector< BlockBase* >& vector);
    // std::string directoryName_;
    // std::string GetDirName();
};
