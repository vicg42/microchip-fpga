#include "hls-main.h"

#include "axi-regs.h"

// #pragma HLS interface variable(AxiRegs) type(axi_slave) concurrent_access(true)
struct AxiRegs_st AxiRegs;

// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, hls::FIFO< axis_ctrl_t > &ififo_ctrl) {
// void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2,
//               uint16_t &status1) {
void hls_main(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo, bool bypass, uint16_t ctrl1, uint16_t ctrl2,
              bool getSatatus, hls::FIFO< axis_status_t > &ofifo_status) {
#pragma HLS function top
#pragma HLS function pipeline
    // uint16_t ctrl1_ = 0;
    // uint16_t ctrl2_ = 0;
    // bool bypass_ = 0;
    // axis_ctrl_t axis_ctrl;
    axis_status_t axis_status;
    axis_t axis;

    if (ififo.empty()) {
        return;
    }

    axis = ififo.read();

    // if (axis.tuser[0]) {
    //     ctrl1_ = ctrl1;
    //     ctrl2_ = ctrl2;
    //     bypass_ = bypass;
    // }

    if (bypass) {
        ofifo.write(axis);
    } else {
        axis.tdata = (axis.tdata * ctrl1) + ctrl2;
        ofifo.write(axis);
    }

    if (getSatatus) {
        axis_status.tdata = axis.tdata;
        axis_status.tuser = 1;
        axis_status.tlast = 0;
        ofifo_status.write(axis_status);

        axis_status.tdata = axis.tdata;
        axis_status.tuser = 0;
        axis_status.tlast = 0;
        ofifo_status.write(axis_status);

        axis_status.tdata = axis.tdata;
        axis_status.tuser = 0;
        axis_status.tlast = 1;
        ofifo_status.write(axis_status);
    }

    // if (axis.tuser[0]) {
    //     status1 = axis.tdata;
    // } else if (axis.tlast) {
    //     status1 = 0xDEAD;
    // }

    // if (AxiRegs.bypass) {
    //     ofifo.write(axis);
    // } else {
    //     axis.tdata = (axis.tdata * AxiRegs.ctrl1) + AxiRegs.ctrl2;
    //     ofifo.write(axis);
    // }

    // //----- FIFO-CTRL -----
    // if (!ififo_ctrl.empty()) {
    //     axis_ctrl = ififo_ctrl.read();
    // }

    // if (axis_ctrl.tuser[0]) {
    //     ctrl1_ = axis_ctrl.tdata & 0xFFFF;
    //     ctrl2_ = (axis_ctrl.tdata >> 16);
    //     bypass_ = (ctrl2_ & 0x8000) ? true : false;
    // }

    // if (ififo.empty()) {
    //     return;
    // }

    // axis = ififo.read();

    // if (bypass_) {
    //     ofifo.write(axis);
    // } else {
    //     axis.tdata = (axis.tdata * ctrl1_) + ctrl2_;
    //     ofifo.write(axis);
    // }

    return;
}
