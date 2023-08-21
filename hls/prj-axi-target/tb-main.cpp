#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <toml.hpp>

#include "ParsingComLine.h"
#include "TestBenchConfig.h"
#include "axi-target.h"
#include "axis.h"
#include "hls/ap_int.hpp"
#include "hls/streaming.hpp"
#include "rtl-main.h"

// char app_name[128];
// static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
//                                              {"input", required_argument, 0, 'i'},
//                                              {"output", required_argument, 0, 'o'},
//                                              {"cfg", required_argument, 0, 'g'},
//                                              {0, 0, 0, 0}};
// char input_File_name[100];
// char output_File_name[100];
// char cfg_File_name[100];

struct video_st {
    uint16_t width;
    uint16_t height;
};

struct AxiTarget_st axi_target;

int main(int argc, char *argv[]) {
    // int next = 0;
    // do {
    //     switch (next = getopt_long(argc, argv, "hi:o:c:", long_opt_arr, 0)) {
    //         case 'i':
    //             strcpy(input_File_name, optarg);
    //             break;
    //         case 'o':
    //             strcpy(output_File_name, optarg);
    //             break;
    //         case 'c':
    //             strcpy(cfg_File_name, optarg);
    //             break;
    //         case -1:  // no more options
    //             break;
    //         case 'h':
    //             strncpy(app_name, __FILE__, (strlen(__FILE__) - 2));
    //             printf("Usage: ./%s [option]\n", app_name);
    //             printf("Mandatory option: \n");
    //             printf("    -h  --help              help\n");
    //             printf("    -i          <path>      default: %s\n", input_File_name);
    //             exit(EXIT_SUCCESS);
    //         default:
    //             exit(EINVAL);
    //     };
    // } while (next != -1);

    // printf("getopt: -i %s -c %s -o %s\n", input_File_name, cfg_File_name, output_File_name);

    // std::ifstream inputFile(input_File_name, std::ios::binary | std::ios::in);
    // std::ofstream outputFile(output_File_name, std::ios::binary | std::ios::out | std::ios::trunc);
    // auto frameNum = 0;
    // struct video_st ifr;
    // ifr.height = 56;
    // ifr.width = 100;
    // printf("%d; %d\n", ifr.height, ifr.width);

    ParsingComLine comLineArg(argc, argv);

    printf("cmd: -i %s -c %s -o %s\n", comLineArg.InFile_.c_str(), comLineArg.CfgFile_.c_str(),
           comLineArg.OutFile_.c_str());

    std::ifstream inputFile(comLineArg.InFile_, std::ios::binary | std::ios::in);
    std::ofstream outputFile(comLineArg.OutFile_, std::ios::binary | std::ios::out | std::ios::trunc);
    TestBenchConfig TBConfig = TestBenchConfig(comLineArg.CfgFile_);
    auto frameNum = 0;
    struct video_st ifr;
    ifr.height = TBConfig.video.height;
    ifr.width = TBConfig.video.width;
    printf("%d; %d\n", ifr.height, ifr.width);

    hls::FIFO< axis_t > input_fifo(5);
    hls::FIFO< axis_t > output_fifo(5);

    inputFile.seekg((ifr.height * ifr.width * 2) * frameNum);

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
    axi_target.block1.a = 0x01;
    axi_target.block1.a = 0x02;
    axi_target.block2.a = 0x11;
    axi_target.block2.a = 0x12;

    for (size_t j = 0; j < frameNum + 1; j++) {
        if (inputFile.peek() == EOF) {
            break;
        }
        for (size_t y = 0; y < ifr.height; y++) {
            for (size_t x = 0; x < ifr.width; x++) {
                // read Input Data
                uint16_t RawData;
                inputFile.read((char *)&RawData, sizeof(uint16_t));
                axis_t axis_m;
                axis_m.tdata = RawData;
                axis_m.tuser = 0;
                axis_m.tlast = 0;
                input_fifo.write(axis_m);

                // user processing
                rtl_top(input_fifo, output_fifo);

                // write results
                while (!output_fifo.empty()) {
                    axis_t axis_s = output_fifo.read();
                    outputFile.write((char *)&axis_s.tdata, sizeof(uint16_t));
                }
            }
            printf("line[%d]\n", (int)y);
        }
    }

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