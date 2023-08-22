#ifndef __RTL_BLOCK1__
#define __RTL_BLOCK1__

#include "axi-target.h"
#include "axis.h"
#include "hls/streaming.hpp"

void rtl_block1(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo, mod1_st* reg);

#endif  //__RTL_BLOCK1__
