#ifndef __RTL_CANNY_H__
#define __RTL_CANNY_H__

#include "hls/streaming.hpp"

void canny(bool switch_0, bool switch_1, bool switch_2, bool switch_3, hls::FIFO< unsigned char > &input_fifo,
           hls::FIFO< unsigned char > &output_fifo);

#endif