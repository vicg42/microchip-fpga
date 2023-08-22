#include "axis.h"
#include "hls/streaming.hpp"

void rtl_main(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo);
