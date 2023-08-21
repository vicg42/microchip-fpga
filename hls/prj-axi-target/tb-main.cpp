#include <inttypes.h>
#include <stdio.h>

#include "axi-target.h"
#include "rtl-main.h"

struct AxiTarget_st axi_target;

int main(int argc, char *argv[]) {
    axi_target.a = 0xffffffff;
    axi_target.b = 0x01010101;
    axi_target.arr[0] = 0x1f;
    axi_target.arr[1] = 0x1f;
    axi_target.arr[2] = 0x17;
    axi_target.arr[3] = 0x27;
    axi_target.arr[4] = 0x21;
    axi_target.arr[5] = 0xe2;
    axi_target.arr[6] = 0xe3;
    axi_target.arr[7] = 0x04;

    rtl_top();

    printf("sum_result = %" PRIx64 "\n", axi_target.sum_result);
    printf("xor_result = %x\n", axi_target.xor_result);
    printf("or_result = %x\n", axi_target.or_result);

    if (axi_target.sum_result == 0x101010366 && axi_target.xor_result == 0xfefefeea &&
        axi_target.or_result == 0xffffffff) {
        printf("PASS\n");
        return 0;
    } else {
        printf("FAIL\n");
        return 1;
    }
}