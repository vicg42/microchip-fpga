#include "rtl-main.h"

#include "axi-target.h"
#include "rtl-block1.h"
#include "rtl-block2.h"
#include "utils.h"

#pragma HLS interface variable(axi_reg) type(axi_slave) concurrent_access(true)
struct AxiTargetReg_st axi_reg;

void rtl_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo) {
#pragma HLS function top

    axi_reg.sum_result = (uint64_t)axi_reg.a + (uint64_t)axi_reg.b + axi_reg.arr[0] + axi_reg.arr[1] + axi_reg.arr[2] +
                         axi_reg.arr[3] + axi_reg.arr[4] + axi_reg.arr[5] + axi_reg.arr[6] + axi_reg.arr[7];
    axi_reg.xor_result = axi_reg.a ^ axi_reg.b ^ axi_reg.arr[0] ^ axi_reg.arr[1] ^ axi_reg.arr[2] ^ axi_reg.arr[3] ^
                         axi_reg.arr[4] ^ axi_reg.arr[5] ^ axi_reg.arr[6] ^ axi_reg.arr[7];
    axi_reg.or_result = axi_reg.a | axi_reg.b | axi_reg.arr[0] | axi_reg.arr[1] | axi_reg.arr[2] | axi_reg.arr[3] |
                        axi_reg.arr[4] | axi_reg.arr[5] | axi_reg.arr[6] | axi_reg.arr[7];

    hls::FIFO< axis_t > block1_ofifo(AXIS_FIFO_DEPTH);

    rtl_block1(ififo, block1_ofifo /*, &axi_reg.mod1*/);
    rtl_block2(block1_ofifo, ofifo /*, &axi_reg.mod2*/);

    axi_reg.glob.status = axi_reg.mod1.status || axi_reg.mod2.status;
}
