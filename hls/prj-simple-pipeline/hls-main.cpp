#include "hls-main.h"

#include "axi-regs.h"

#pragma HLS interface variable(AxiRegs) type(axi_slave) concurrent_access(true)
// #pragma HLS interface variable(AxiRegs) type(memory) num_elements(2)
struct AxiRegs_st AxiRegs;

// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2) {
void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo) {
#pragma HLS function top
#pragma HLS function pipeline
    // #pragma HLS memory impl argument(regs) pack(byte)
    // #pragma HLS interface argument(regs) type(memory) num_elements(2)
    // #pragma HLS interface argument(regs) type(axi_target) num_elements(4) dma(false) requires_copy_in(false)

    uint16_t regA = 0;
    uint16_t regB = 0;
    bool regC = 0;

    axis_t axis;

    if (ififo.empty()) {
        return;
    }

    axis = ififo.read();

    // regA = ctrl1;
    // regB = ctrl1;
    // regC = bypass;

    // // if (axis.tlast) {
    // //     regA = ctrl1;
    // //     regB = ctrl1;
    // //     regC = bypass;
    // // }

    regA = AxiRegs.ctrl1;
    regB = AxiRegs.ctrl2;
    regC = (AxiRegs.bypass == 1) ? true : false;

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

    return;
}
