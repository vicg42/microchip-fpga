#ifndef __RTL_BLOCK2__
#define __RTL_BLOCK2__

#include "axi-target.h"
#include "axis.h"
#include "hls/streaming.hpp"

void rtl_block2(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo, mod2_st* reg);

#endif  //__RTL_BLOCK2__
