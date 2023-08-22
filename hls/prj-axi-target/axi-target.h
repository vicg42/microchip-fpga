#ifndef __AXI_TARGET_H__
#define __AXI_TARGET_H__

#include <cstdint>

struct AxiTarget_st {
    uint8_t arr[8];
    uint32_t a;
    uint32_t b;
    uint64_t sum_result;
    uint32_t xor_result;
    uint32_t or_result;
    // struct {
    //     uint32_t a;
    //     uint32_t b;
    //     uint32_t result;
    // } block1;

    // struct {
    //     uint32_t a;
    //     uint32_t b;
    //     uint32_t result;
    // } block2;
};

#endif  // __AXI_TARGET_H__