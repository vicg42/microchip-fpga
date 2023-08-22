#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// // #include <fstream>
// #include <toml.hpp>

// #include "ParsingComLine.h"
// #include "TestBenchConfig.h"
#include "axi-target.h"
#include "axis.h"
#include "config-InputData.h"
#include "config-OutputData.h"
#include "config-TPL.h"
#include "hls/streaming.hpp"
#include "rtl-block1.h"
#include "rtl-block2.h"
#include "rtl-main.h"
#include "utils.h"

char app_name[128];
static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
                                             {"input", required_argument, 0, 'i'},
                                             {"output", required_argument, 0, 'o'},
                                             {"cfg", required_argument, 0, 'c'},
                                             {0, 0, 0, 0}};
char InputFilePath[100];
char OutputFilePath[100];
char ConfigFilePath[100];

extern struct AxiTargetReg_st axi_reg;

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
    ifr.size = VIDEO_IN_HEIGHT * VIDEO_IN_WIDTH;
    printf("VideoIn: %dx%d\n", VIDEO_IN_HEIGHT, VIDEO_IN_WIDTH);

    uint8_t *InputFileData = (uint8_t *)malloc(ifr.size * ifr.bpp);
    uint8_t *OutputFileData = (uint8_t *)malloc(ifr.size * ifr.bpp);
    uint16_t *InputFileData_ptr = (uint16_t *)InputFileData;
    uint16_t *OutputFileData_ptr = (uint16_t *)OutputFileData;

    int result = 0;
    result = readImage(InputFilePath, InputFileData, &ifr);
    if (result < 0) {
        printf("Error: read FileData1\n");
        return -1;
    }

    // ParsingComLine comLineArg(argc, argv);

    // printf("cmd: -i %s -c %s -o %s\n", comLineArg.InFile_.c_str(), comLineArg.CfgFile_.c_str(),
    //        comLineArg.OutFile_.c_str());

    // TestBenchConfig TBConfig = TestBenchConfig(comLineArg.CfgFile_);
    // struct video_st ifr;
    // VIDEO_IN_NFRAME = 1;
    // VIDEO_IN_HEIGHT = TBConfig.video.height;
    // VIDEO_IN_WIDTH = TBConfig.video.width;
    // VIDEO_IN_BPP = 2;
    // ifr.size = VIDEO_IN_HEIGHT * VIDEO_IN_WIDTH;
    // printf("%d; %d\n", VIDEO_IN_HEIGHT, VIDEO_IN_WIDTH);

    // uint8_t *InputFileData = (uint8_t *)malloc((VIDEO_IN_HEIGHT * VIDEO_IN_WIDTH) * VIDEO_IN_BPP);
    // uint8_t *OutputFileData = (uint8_t *)malloc((VIDEO_IN_HEIGHT * VIDEO_IN_WIDTH) * VIDEO_IN_BPP);
    // uint16_t *InputFileData_ptr = (uint16_t *)InputFileData;
    // uint16_t *OutputFileData_ptr = (uint16_t *)OutputFileData;

    // int result = 0;
    // result = readImage(comLineArg.InFile_.c_str(), InputFileData, &ifr);
    // if (result < 0) {
    //     printf("Error: read FileData1\n");
    //     return -1;
    // }

    axi_reg.a = 0xffffffff;
    axi_reg.b = 0x01010101;
    axi_reg.arr[0] = 0x1f;
    axi_reg.arr[1] = 0x1f;
    axi_reg.arr[2] = 0x17;
    axi_reg.arr[3] = 0x27;
    axi_reg.arr[4] = 0x21;
    axi_reg.arr[5] = 0xe2;
    axi_reg.arr[6] = 0xe3;
    axi_reg.arr[7] = 0x04;
    axi_reg.mod1.ctrl = REG_CTRL;
    axi_reg.mod2.ctrl = 0x03;
    axi_reg.glob.ctrl = 0x0a;
    axi_reg.glob.width = 0x0a;
    axi_reg.glob.height = 0x0a;

    // rtl_main();

    hls::FIFO< axis_t > input_fifo(AXIS_FIFO_DEPTH);
    hls::FIFO< axis_t > output_fifo(AXIS_FIFO_DEPTH);
    axis_t axis_m;
    axis_t axis_s;
    for (uint16_t j = 0; j < ifr.nframe; j++) {
        for (uint16_t y = 0; y < ifr.height; y++) {
            for (uint16_t x = 0; x < ifr.width; x++) {
                // read Input Data
                axis_m.tdata = *InputFileData_ptr;
                axis_m.tuser = ((x == 0) & (y == 0)) ? 1 : 0;
                axis_m.tlast = (x == (ifr.width - 1)) ? 1 : 0;
                input_fifo.write(axis_m);
                InputFileData_ptr++;

                // user processing
                rtl_main(input_fifo, output_fifo);

                // write results
                while (!output_fifo.empty()) {
                    axis_s = output_fifo.read();
                    *OutputFileData_ptr = axis_s.tdata;
                    OutputFileData_ptr++;
                }
            }
            printf("line[%d]\n", (int)y);
        }
    }

    printf("sum_result = %" PRIx64 "\n", axi_reg.sum_result);
    printf("xor_result = %x\n", axi_reg.xor_result);
    printf("or_result = %x\n", axi_reg.or_result);

    if (axi_reg.sum_result == 0x101010366 && axi_reg.xor_result == 0xfefefeea && axi_reg.or_result == 0xffffffff) {
        printf("PASS\n");
        return 0;
    } else {
        printf("FAIL\n");
        return 1;
    }
    printf("DONE\n");
}