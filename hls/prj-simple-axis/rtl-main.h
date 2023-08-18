#include <stdio.h>

#include "hls/ap_fixpt.hpp"
#include "hls/ap_int.hpp"
#include "hls/streaming.hpp"
#include "rtl-common.h"

void RTL_top(hls::FIFO< axis_t >& tb_ififo, hls::FIFO< axis_t >& tb_ofifo);