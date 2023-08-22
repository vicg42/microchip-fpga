#ifndef __AXI_TARGET_H__
#define __AXI_TARGET_H__

#include <cstdint>

struct glob_st {
    uint32_t ctrl;
    uint32_t status;
    uint32_t width;
    uint32_t height;
};

struct mod1_st {
    uint32_t ctrl;
    uint32_t status;
};

struct mod2_st {
    uint32_t ctrl;
    uint32_t status;
};

struct AxiTargetReg_st {
    uint8_t arr[8];
    uint32_t a;
    uint32_t b;
    uint64_t sum_result;
    uint32_t xor_result;
    uint32_t or_result;
    mod1_st mod1;
    mod2_st mod2;
    glob_st glob;
};

#endif  // __AXI_TARGET_H__