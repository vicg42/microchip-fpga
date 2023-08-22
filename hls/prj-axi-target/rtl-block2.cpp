#include <stdio.h>

#include "rtl-block1.h"

void rtl_block2(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo, mod2_st* reg) {
    if (ififo.empty()) return;

    axis_t axis = ififo.read();

    if (axis.tuser[0] == 1) {
        reg->status = 0;
    } else if (axis.tlast) {
        reg->status++;
    }

    axis.tdata = axis.tdata * reg->ctrl;
    ofifo.write(axis);
}
