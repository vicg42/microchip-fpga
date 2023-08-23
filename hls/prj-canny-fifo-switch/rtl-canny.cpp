#include "axi-target.h"
#include "define.hpp"

// #pragma HLS interface variable(axi_reg) type(axi_slave) concurrent_access(true)
struct AxiTargetReg_st axi_reg;

void canny(hls::ap_uint< 1 > switch_0, hls::ap_uint< 1 > switch_1, hls::ap_uint< 1 > switch_2,
           hls::ap_uint< 1 > switch_3, hls::FIFO< unsigned char > &input_fifo,
           hls::FIFO< unsigned char > &output_fifo) {
#pragma HLS function top
#pragma HLS function dataflow

    hls::FIFO< unsigned char > output_fifo_gf(/* depth = */ 2);
    hls::FIFO< unsigned short > output_fifo_sf(/* depth = */ 2);
    hls::FIFO< unsigned char > output_fifo_nm(/* depth = */ 2);

    // axi_reg.status++;
    // hls::ap_uint< 1 > switch_0 = 1;  // axi_reg.ctrl & 0x01;
    // hls::ap_uint< 1 > switch_1 = 1;  // axi_reg.ctrl & 0x02;
    // hls::ap_uint< 1 > switch_2 = 1;  // axi_reg.ctrl & 0x04;
    // hls::ap_uint< 1 > switch_3 = 1;  // axi_reg.ctrl & 0x08;

    gaussian_filter(switch_0, /*axi_reg.ctrl & 0x01,*/ input_fifo, output_fifo_gf);
    sobel_filter(switch_1, /*axi_reg.ctrl & 0x02,*/ output_fifo_gf, output_fifo_sf);
    nonmaximum_suppression(switch_2, /*axi_reg.ctrl & 0x04,*/ output_fifo_sf, output_fifo_nm);
    hysteresis_filter(switch_3, /*axi_reg.ctrl & 0x08,*/ output_fifo_nm, output_fifo);
}
