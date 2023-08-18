#ifndef __USR_RTL_MAIN__
#define __USR_RTL_MAIN__

#include "rtl-main.h"

void RTL_top(hls::FIFO< axis_t >& tb_ififo, hls::FIFO< axis_t >& tb_ofifo) {
#pragma HLS function top
#pragma HLS function pipeline

    if (tb_ififo.empty()) return;

    axis_t axis = tb_ififo.read();

    tb_ofifo.write(axis);
}

#endif  //__USR_RTL_MAIN__
