
#pragma once

#include "axis.h"
#include "hls/streaming.hpp"

// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2);
void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo);
