#include "block_2.h"

#include <cstring>
#include <fstream>

void Block2::Init() {
}

void Block2::SetValue(std::string param, const size_t value) {
    if (param == "width") {
        width_i_ = value;
    } else if (param == "height") {
        height_i_ = value;
    }
}

void Block2::main() {
    printf("Block2::%s dbg_level_: %d\n", __func__, (int)dbg_level_);
    printf("Block2::%s frame_i[%d, %d]\n", __func__, (int)width_i_, (int)height_i_);
}
