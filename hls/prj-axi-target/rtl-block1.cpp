#include "rtl-block1.h"

#include <stdio.h>

extern struct AxiTargetReg_st axi_reg;

void rtl_block1(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo /*, mod1_st* reg*/) {
    if (ififo.empty()) return;

    axis_t axis = ififo.read();

    if (axis.tuser[0] == 1) {
        axi_reg.mod1.status = 0;  // reg->status = 0;
    } else if (axis.tlast) {
        axi_reg.mod1.status++;  // reg->status++;
    }

    axis.tdata = axis.tdata * axi_reg.mod1.ctrl;  // reg->ctrl;
    ofifo.write(axis);
}
