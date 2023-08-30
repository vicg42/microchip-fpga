#include "hls-main.h"

#include "axi-regs.h"

#pragma HLS interface variable(AxiRegs) type(axi_slave) concurrent_access(true)
// #pragma HLS interface variable(AxiRegs) type(axi_target)
struct AxiRegs_st AxiRegs;

// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2) {
void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, hls::FIFO< axis_ctrl_t > &ififo_ctrl) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2,
//               uint16_t &status1) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2,
//               bool getSatatus, hls::FIFO< axis_status_t > &ofifo_status) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, AxiRegs_st *Regs) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, uint16_t *Regs) {
#pragma HLS function top
#pragma HLS function pipeline
    // #pragma HLS interface argument(Regs) type(memory) num_elements(2)
    // #pragma HLS interface argument(Regs) type(axi_target) num_elements(1)
    // #pragma HLS interface argument(Regs) type(axi_target) num_elements(8) dma(true) requires_copy_in(true)
    uint16_t regA = 0;
    uint16_t regB = 0;
    bool bypass_ = false;
    // axis_ctrl_t axis_ctrl;
    axis_status_t axis_status;
    axis_t axis;
    // struct AxiRegs_st regs;

    // memset((char *)&regs, 0, sizeof(struct AxiRegs_st));

    if (ififo.empty()) {
        return;
    }

    axis = ififo.read();

    // if (axis.tuser[0]) {
    //     regA = ctrl1;
    //     regB = ctrl2;
    //     bypass_ = bypass;
    // }

    regA = AxiRegs.ctrl1;
    regB = AxiRegs.ctrl2;
    bypass_ = (AxiRegs.bypass == 1) ? true : false;

    // if (axis.tlast) {
    //     // regs = AxiRegs;
    //     regA = AxiRegs.ctrl1;
    //     regB = AxiRegs.ctrl2;
    //     bypass_ = (AxiRegs.bypass == 1) ? true : false;
    // }

    // if (bypass) {
    //     ofifo.write(axis);
    // } else {
    //     axis.tdata = (axis.tdata * ctrl1) + ctrl2;
    //     ofifo.write(axis);
    // }

    // if (getSatatus) {
    //     axis_status.tdata = axis.tdata;
    //     axis_status.tuser = 1;
    //     axis_status.tlast = 0;
    //     ofifo_status.write(axis_status);

    //     axis_status.tdata = axis.tdata;
    //     axis_status.tuser = 0;
    //     axis_status.tlast = 0;
    //     ofifo_status.write(axis_status);

    //     axis_status.tdata = axis.tdata;
    //     axis_status.tuser = 0;
    //     axis_status.tlast = 1;
    //     ofifo_status.write(axis_status);
    // }

    // if (axis.tuser[0]) {
    //     status1 = axis.tdata;
    // } else if (axis.tlast) {
    //     status1 = 0xDEAD;
    // }

    // if (Regs[0] == 1) {
    //     ofifo.write(axis);
    // } else {
    //     axis.tdata = (axis.tdata * Regs[1]) + Regs[2];
    //     ofifo.write(axis);
    // }
    // Regs[3] += 1;

    if (axis.tlast) {
        AxiRegs.status++;
    }

    if (bypass_) {
        ofifo.write(axis);
    } else {
        axis.tdata = (axis.tdata * regA) + regB;
        ofifo.write(axis);
    }

    // //----- FIFO-CTRL -----
    // if (!ififo_ctrl.empty()) {
    //     axis_ctrl = ififo_ctrl.read();
    // }

    // if (axis_ctrl.tuser[0]) {
    //     regA = axis_ctrl.tdata & 0xFFFF;
    //     regB = (axis_ctrl.tdata >> 16);
    //     bypass_ = (regB & 0x8000) ? true : false;
    // }

    // if (ififo.empty()) {
    //     return;
    // }

    // axis = ififo.read();

    // if (bypass_) {
    //     ofifo.write(axis);
    // } else {
    //     axis.tdata = (axis.tdata * regA) + regB;
    //     ofifo.write(axis);
    // }

    return;
}
