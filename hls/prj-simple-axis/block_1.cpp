#include "block_1.h"

#include <cstring>
#include <fstream>

void Block1::Init() {
}

void Block1::SetValue(std::string param, const size_t value) {
    if (param == "width") {
        width_i_ = value;
    } else if (param == "height") {
        height_i_ = value;
    }
}

void Block1::main() {
    printf("Block1::%s dbg_level_: %d\n", __func__, (int)dbg_level_);
    printf("Block1::%s frame_i[%d, %d]\n", __func__, (int)width_i_, (int)height_i_);
}
