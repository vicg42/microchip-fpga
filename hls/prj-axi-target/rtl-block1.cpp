#include "rtl-block1.h"

#include <stdio.h>

extern struct AxiTarget_st axi_target;

void rtl_block1(hls::FIFO< axis_t >& ififo, hls::FIFO< axis_t >& ofifo) {
    axi_target.block1.result = (uint64_t)axi_target.block1.a + (uint64_t)axi_target.block1.b;
    printf("axi_target.block1.a=%x; axi_target.block1.b=%x; axi_target.block1.result=%x\n", axi_target.block1.a,
           axi_target.block1.b, axi_target.block1.result);

    if (ififo.empty()) return;

    axis_t axis = ififo.read();

    ofifo.write(axis);
}
