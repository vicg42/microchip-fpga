#pragma once

#include "hls/ap_int.hpp"

const int AXIS_TDATA_WIDTH = 16;
const int AXIS_TUSER_WIDTH = 2;
const int AXIS_FIFO_DEPTH = 1;

typedef struct {
    hls::ap_uint< AXIS_TDATA_WIDTH > tdata;
    // uint16_t tdata;
    hls::ap_uint< 1 > tlast;
    hls::ap_uint< AXIS_TUSER_WIDTH > tuser;
} axis_t;

typedef struct {
    uint32_t tdata;
    hls::ap_uint< 1 > tlast;
    hls::ap_uint< 1 > tuser;
} axis_ctrl_t;

typedef struct {
    uint32_t tdata;
    hls::ap_uint< 1 > tlast;
    hls::ap_uint< 1 > tuser;
} axis_status_t;