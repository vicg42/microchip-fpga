#include "axi-target.h"
#include "define.hpp"

#pragma HLS interface variable(axi_reg) type(axi_slave) concurrent_access(true)
struct AxiTargetReg_st axi_reg;

void canny(hls::ap_uint< 1 > switch_0, hls::ap_uint< 1 > switch_1, hls::ap_uint< 1 > switch_2,
           hls::ap_uint< 1 > switch_3, hls::FIFO< unsigned char > &input_fifo,
           hls::FIFO< unsigned char > &output_fifo) {
#pragma HLS function top
#ifdef USR_CTRL_HLS_FUNCTION_DATAFLOW
#pragma HLS function dataflow
#endif

    hls::FIFO< unsigned char > output_fifo_gf(/* depth = */ 2);
    hls::FIFO< unsigned short > output_fifo_sf(/* depth = */ 2);
    hls::FIFO< unsigned char > output_fifo_nm(/* depth = */ 2);

    // axi_reg.status++;
    bool switch_i0 = (axi_reg.ctrl & 0x01) ? true : false;  //
    bool switch_i1 = (axi_reg.ctrl & 0x02) ? true : false;  //
    bool switch_i2 = (axi_reg.ctrl & 0x04) ? true : false;  //
    bool switch_i3 = (axi_reg.ctrl & 0x08) ? true : false;  //

    gaussian_filter(switch_i0, /*axi_reg.ctrl & 0x01,*/ input_fifo, output_fifo_gf);
    sobel_filter(switch_i1, /*axi_reg.ctrl & 0x02,*/ output_fifo_gf, output_fifo_sf);
    nonmaximum_suppression(switch_i2, /*axi_reg.ctrl & 0x04,*/ output_fifo_sf, output_fifo_nm);
    hysteresis_filter(switch_i3, /*axi_reg.ctrl & 0x08,*/ output_fifo_nm, output_fifo);
}
