#include "rtl-main.h"

#pragma HLS interface variable(axi_target) type(axi_slave)
extern struct AxiTarget_st axi_target;

void rtl_top() {
#pragma HLS function top
    axi_target.sum_result = (uint64_t)axi_target.a + (uint64_t)axi_target.b + axi_target.arr[0] + axi_target.arr[1] +
                            axi_target.arr[2] + axi_target.arr[3] + axi_target.arr[4] + axi_target.arr[5] +
                            axi_target.arr[6] + axi_target.arr[7];
    axi_target.xor_result = axi_target.a ^ axi_target.b ^ axi_target.arr[0] ^ axi_target.arr[1] ^ axi_target.arr[2] ^
                            axi_target.arr[3] ^ axi_target.arr[4] ^ axi_target.arr[5] ^ axi_target.arr[6] ^
                            axi_target.arr[7];
    axi_target.or_result = axi_target.a | axi_target.b | axi_target.arr[0] | axi_target.arr[1] | axi_target.arr[2] |
                           axi_target.arr[3] | axi_target.arr[4] | axi_target.arr[5] | axi_target.arr[6] |
                           axi_target.arr[7];
}
