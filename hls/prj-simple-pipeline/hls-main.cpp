#include "hls-main.h"

#include "axi-regs.h"
#include "hls/ap_int.hpp"

#pragma HLS interface variable(AxiRegs) type(axi_slave) concurrent_access(true)
// #pragma HLS interface variable(AxiRegs) type(memory) num_elements(2)
struct AxiRegs_st AxiRegs;

// uint16_t regA = 1;
// uint16_t regB = 0;
// bool regC = 0;
// uint16_t BufCnt = 0;
// uint8_t PixCnt = 0;
// hls::ap_uint< 64 > AXIMM_tdata = 0;
// hls::FIFO< hls::ap_uint< 64 > > AXIMM_tdata_fifo(AXIS_FIFO_DEPTH);

// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2) {
void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, uint64_t *Buf) {
#pragma HLS function top
#pragma HLS function pipeline

    // #pragma HLS interface argument(Buf) type(axi_initiator) ptr_addr_interface(simple) num_elements(BUF_COUNT) \
//     max_burst_len(8)

    static uint16_t regA = 1;
    static uint16_t regB = 0;
    static bool regC = 0;

    axis_t axis;

    if (ififo.empty()) {
        return;
    }

    axis = ififo.read();

    if (axis.tlast) {
        regA = AxiRegs.ctrl1;
        regB = AxiRegs.ctrl2;
        regC = (AxiRegs.bypass == 1) ? true : false;
    }

    if (axis.tlast) {
        AxiRegs.status++;
    }

    // regA = regs->ctrl1;
    // regB = regs->ctrl2;
    // regC = (regs->bypass == 1) ? true : false;

    // if (axis.tlast) {
    //     regs->status++;
    // }

    if (regC) {
        ofifo.write(axis);
    } else {
        axis.tdata = (axis.tdata * regA) + regB;
        ofifo.write(axis);
    }

    // if (PixCnt == 0) {
    //     AXIMM_tdata = (hls::ap_uint< 64 >)axis.tdata;
    // } else {
    //     AXIMM_tdata |= (hls::ap_uint< 64 >)axis.tdata << (PixCnt * 16);
    // }

    // if (PixCnt == 3) {
    //     PixCnt = 0;
    //     Buf[BufCnt] = AXIMM_tdata;
    //     if (BufCnt == BUF_COUNT) {
    //         BufCnt = 0;
    //     } else {
    //         BufCnt++;
    //     }
    // } else {
    //     PixCnt++;
    // }

    // #ifndef __SYNTHESIS__
    //     std::cout << std::hex << AXIMM_tdata << std::endl;
    // #endif

    return;
}
