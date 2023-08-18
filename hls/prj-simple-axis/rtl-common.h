#ifndef __USR_COMMON__
#define __USR_COMMON__

#include "hls/ap_int.hpp"

const int AXIS_TDATA_WIDTH = 16;
const int AXIS_TUSER_WIDTH = 2;

typedef struct {
    hls::ap_uint< AXIS_TDATA_WIDTH > tdata;
    hls::ap_uint< 1 > tlast;
    hls::ap_uint< AXIS_TUSER_WIDTH > tuser;
} axis_t;

#endif  //__USR_COMMON__
