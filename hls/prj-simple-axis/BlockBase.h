#pragma once
#include <string>
#include <vector>

class BlockBase {
   public:
    virtual void SetValue(std::string param, const std::string value){};
    virtual void SetValue(std::string param, const size_t value){};
    virtual void SetValue(std::string param, const bool value){};
    virtual void SetValue(std::string param, const std::vector< int64_t > &value){};
    virtual void SetValue(std::string param, const std::vector< std::vector< int64_t > > &value){};
    virtual void SetValue(std::string param, const std::vector< float > &value){};
    virtual void SetValue(std::string param, const float value){};
    virtual void Init(){};
    static std::vector< BlockBase * > blockList;
    std::string basename_;

    BlockBase(std::string name) {
        basename_ = name;
        blockList.push_back(this);
    }
};
