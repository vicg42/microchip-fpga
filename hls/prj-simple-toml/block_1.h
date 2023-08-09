#pragma once
#include <toml.hpp>

#include "BlockBase.h"

class Block1 : public BlockBase {
   public:
    void Init();
    void main();
    void SetValue(std::string param, const size_t value);

    Block1(std::string name, uint8_t DbgLevel) : BlockBase(name) {
        dbg_level_ = DbgLevel;
    }

    ~Block1() {
    }

   private:
    size_t width_i_ = 0;
    size_t height_i_ = 0;

    int dbg_level_ = 0;
};
