
#pragma once

#include "axis.h"
#include "hls/streaming.hpp"

void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2);
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo);
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, hls::FIFO< axis_ctrl_t > &ififo_ctrl);
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2,
//               uint16_t &status1);
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2,
//               bool getSatatus, hls::FIFO< axis_status_t > &ofifo_status);
