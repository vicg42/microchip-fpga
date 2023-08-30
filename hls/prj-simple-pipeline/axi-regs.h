#pragma once

#include <cstdint>

struct AxiRegs_st {
    uint16_t ctrl1;
    uint16_t ctrl2;
    uint16_t bypass;
    uint16_t status;
};
