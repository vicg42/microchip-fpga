#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "axi-regs.h"
#include "axis.h"
#include "config-InputData.h"
#include "config-OutputData.h"
#include "config-REG.h"
#include "hls-main.h"
#include "hls/streaming.hpp"
#include "utils.h"

char app_name[128];
static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
                                             {"input", required_argument, 0, 'i'},
                                             {"output", required_argument, 0, 'o'},
                                             {"cfg", required_argument, 0, 'c'},
                                             {0, 0, 0, 0}};
char InputFilePath[1024];
char OutputFilePath[1024];
char ConfigFilePath[1024];

extern struct AxiRegs_st AxiRegs;

int main(int argc, char *argv[]) {
    int next = 0;
    do {
        switch (next = getopt_long(argc, argv, "hi:o:c:", long_opt_arr, 0)) {
            case 'i':
                strcpy(InputFilePath, optarg);
                break;
            case 'o':
                strcpy(OutputFilePath, optarg);
                break;
            case 'c':
                strcpy(ConfigFilePath, optarg);
                break;
            case -1:  // no more options
                break;
            case 'h':
                strncpy(app_name, __FILE__, (strlen(__FILE__) - 2));
                printf("Usage: ./%s [option]\n", app_name);
                printf("Mandatory option: \n");
                printf("    -h  --help              help\n");
                printf("    -i          <path>      default: %s\n", InputFilePath);
                exit(EXIT_SUCCESS);
            default:
                exit(EINVAL);
        };
    } while (next != -1);

    printf("getopt: -i %s -c %s -o %s\n", InputFilePath, ConfigFilePath, OutputFilePath);

    // /* Create HDL code only */
    // hls::FIFO< axis_t > input_fifo(AXIS_FIFO_DEPTH);
    // hls::FIFO< axis_t > output_fifo(AXIS_FIFO_DEPTH);
    // rtl_main(input_fifo, output_fifo);
    // return 0;

    struct video_st ifr;
    ifr.nframe = VIDEO_IN_NFRAME;
    ifr.height = VIDEO_IN_HEIGHT;
    ifr.width = VIDEO_IN_WIDTH;
    ifr.bpp = VIDEO_IN_BPP;
    ifr.size = ifr.height * ifr.width;  // * ifr.nframe;
    printf("VideoIn: %dx%d@%d\n", ifr.height, ifr.width, ifr.nframe);

    uint8_t *InputFileData[10];  // = (uint8_t *)malloc(ifr.size * ifr.bpp);
    uint8_t *OutputFileData = (uint8_t *)malloc(ifr.size * ifr.bpp * ifr.nframe);
    uint16_t *InputFileData_ptr;  // = (uint16_t *)InputFileData;
    uint16_t *OutputFileData_ptr = (uint16_t *)OutputFileData;

    // memset((uint8_t *)InputFileData, 0, (ifr.size * ifr.bpp * ifr.nframe));
    int result = 0;
    for (uint16_t j = 0; j < ifr.nframe; j++) {
        InputFileData[j] = (uint8_t *)malloc(ifr.size * ifr.bpp);
        printf("InputFileData:%p\n", InputFileData);
        result = readImage(InputFilePath, InputFileData[j], &ifr);
        if (result < 0) {
            printf("Error: read FileData1\n");
            return -1;
        };
    }

    AxiRegs.ctrl1 = REG_CTRL1;
    AxiRegs.ctrl2 = REG_CTRL2;
    AxiRegs.bypass = REG_BYPASS;

    axis_ctrl_t ctrl;
    hls::FIFO< axis_ctrl_t > input_fifo_ctrl(5);

    // ctrl.tdata = REG_CTRL1 | (REG_CTRL2 << 16) | (REG_BYPASS << 31);
    // ctrl.tuser = 1;
    // ctrl.tlast = 0;
    // input_fifo_ctrl.write(ctrl);

    // // ctrl.tdata = REG_CTRL1 | (REG_CTRL2 << 16);
    // ctrl.tuser = 0;
    // ctrl.tlast = 0;
    // input_fifo_ctrl.write(ctrl);

    printf("AxiRegs.bypass = %d(x%x)\n", (int)AxiRegs.bypass, (int)AxiRegs.bypass);
    printf("AxiRegs.ctrl1 = %d(x%x)\n", (int)AxiRegs.ctrl1, (int)AxiRegs.ctrl1);
    printf("AxiRegs.ctrl2 = %d(x%x)\n", (int)AxiRegs.ctrl2, (int)AxiRegs.ctrl2);

    hls::FIFO< axis_t > input_fifo(AXIS_FIFO_DEPTH);
    hls::FIFO< axis_t > output_fifo(AXIS_FIFO_DEPTH);
    axis_t axis_m;
    axis_t axis_s;
    for (uint16_t j = 0; j < ifr.nframe; j++) {
        printf("VideoIn: %dx%d@%d; frn[%d]\n", ifr.height, ifr.width, ifr.nframe, j);
        InputFileData_ptr = (uint16_t *)InputFileData[j];

        AxiRegs.ctrl1 = REG_CTRL1;
        AxiRegs.ctrl2 = REG_CTRL2;
        AxiRegs.bypass = (j & 0x1) ? true : false;

        ctrl.tdata = REG_CTRL1 | (REG_CTRL2 << 16) | (j << 31);
        ctrl.tuser = 1;
        ctrl.tlast = 0;
        // input_fifo_ctrl.write(ctrl);

        // ctrl.tuser = 0;
        // ctrl.tlast = 0;
        // input_fifo_ctrl.write(ctrl);

        for (uint16_t y = 0; y < ifr.height; y++) {
            for (uint16_t x = 0; x < ifr.width; x++) {
                // read Input Data
                // if (y == 0) {
                //     printf("frn[%d]y[%d]x[%d] - %d\n", j, y, x,  *InputFileData_ptr);
                // }
                axis_m.tdata = *InputFileData_ptr;
                axis_m.tuser = ((x == 0) & (y == 0)) ? 1 : 0;
                axis_m.tlast = (x == (ifr.width - 1)) ? 1 : 0;
                input_fifo.write(axis_m);
                InputFileData_ptr++;

                // user processing
                hls_main(input_fifo, output_fifo, (AxiRegs.bypass == 1) ? true : false, AxiRegs.ctrl1, AxiRegs.ctrl2);
                // hls_main(input_fifo, output_fifo);
                // hls_main(input_fifo, output_fifo, input_fifo_ctrl);

                // write results
                while (!output_fifo.empty()) {
                    axis_s = output_fifo.read();
                    *OutputFileData_ptr = axis_s.tdata;
                    OutputFileData_ptr++;
                }
            }
            // printf("line[%d]\n", (int)y);
        }
    }

    printf("DONE\n");
}