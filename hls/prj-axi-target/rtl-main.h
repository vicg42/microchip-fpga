#include "axi-target.h"
#include "axis.h"
#include "hls/streaming.hpp"

void rtl_top(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo);
