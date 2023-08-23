#include <stdio.h>

#include "rtl-block1.h"

extern struct AxiTargetReg_st axi_reg;

void rtl_block2(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo /*, mod2_st* reg*/) {
    if (ififo.empty()) return;

    axis_t axis = ififo.read();

    if (axis.tuser[0] == 1) {
        axi_reg.mod2.status = 0;  // reg->status = 0;
    } else if (axis.tlast) {
        axi_reg.mod2.status++;  // reg->status++;
    }

    axis.tdata = axis.tdata * axi_reg.mod2.ctrl;  // reg->ctrl;
    ofifo.write(axis);
}
