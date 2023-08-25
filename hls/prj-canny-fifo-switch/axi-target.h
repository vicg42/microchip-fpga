#ifndef __AXI_TARGET_H__
#define __AXI_TARGET_H__

#include <cstdint>

// #define USR_CTRL_HLS_FUNCTION_DATAFLOW
#define USR_CTRL_HLS_FUNCTION_PIPELINE

// struct gaussian_filter_st {
//     uint32_t status;
//     uint32_t ctrl;
// };

struct AxiTargetReg_st {
    uint32_t ctrl;
    uint32_t status;
    // gaussian_filter_st gf;
};

#endif  // __AXI_TARGET_H__