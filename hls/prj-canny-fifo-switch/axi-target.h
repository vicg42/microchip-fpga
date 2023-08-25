#ifndef __AXI_TARGET_H__
#define __AXI_TARGET_H__

#include <cstdint>

#define USR_CTRL_HLS_FUNCTION_DATAFLOW
#define USR_CTRL_HLS_FUNCTION_PIPELINE

// struct glob_st {
//     uint32_t status;
//     uint32_t ctrl;
// };

struct AxiTargetReg_st {
    uint32_t ctrl;
    uint32_t status;
    // glob_st glob;
    // uint8_t gaussian_filter;
    // uint8_t sobel_filter;
    // uint8_t nonmaximum_suppression;
    // uint8_t hysteresis_filter;
};

#endif  // __AXI_TARGET_H__