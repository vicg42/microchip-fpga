#include "ReadConfig.h"

std::string ReadConfig::GetDirName() {
    return directoryName_;
}

ReadConfig::ReadConfig(std::string directoryName, std::vector< BlockBase* >& vector) : directoryName_(directoryName) {
    auto data = toml::parse(directoryName_);
    for (const auto& module : vector) {
        try {
            const auto& metaInfo = toml::find(data, module->basename_);
            auto value = metaInfo.as_table();
            for (const auto& param : value) {
                std::string paramName = param.first;
                if (param.second.is_string()) {
                    std::string paramValue = param.second.as_string();
                    module->SetValue(paramName, paramValue);
                } else if (param.second.is_integer()) {
                    size_t paramValue = param.second.as_integer();
                    module->SetValue(paramName, paramValue);
                } else if (param.second.is_boolean()) {
                    bool paramValue = param.second.as_boolean();
                    module->SetValue(paramName, paramValue);
                } else if (param.second.is_floating()) {
                    float paramValue = param.second.as_floating();
                    module->SetValue(paramName, paramValue);
                } else if (param.second.is_array()) {
                    if (!toml::get< std::vector< toml::value > >(param.second)[0].is_array()) {
                        if (param.second[0].is_floating()) {
                            module->SetValue(paramName, toml::get< std::vector< float > >(param.second));
                        } else {
                            module->SetValue(paramName, toml::get< std::vector< int64_t > >(param.second));
                        }
                    } else {
                        module->SetValue(paramName, toml::get< std::vector< std::vector< int64_t > > >(param.second));
                    }
                }
            }
        } catch (...) {
            continue;
        }
    }
}
