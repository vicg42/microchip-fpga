#ifndef __RTL_CANNY_H__
#define __RTL_CANNY_H__

#include "hls/streaming.hpp"

void canny(hls::ap_uint< 1 > switch_0, hls::ap_uint< 1 > switch_1, hls::ap_uint< 1 > switch_2,
           hls::ap_uint< 1 > switch_3, hls::FIFO< unsigned char > &input_fifo, hls::FIFO< unsigned char > &output_fifo);

#endif