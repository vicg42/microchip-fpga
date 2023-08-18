#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <toml.hpp>
#include <vector>

#include "ParsingComLine.h"
#include "TestBenchConfig.h"
// #include "hls/ap_fixpt.hpp"
#include "hls/ap_int.hpp"
#include "hls/streaming.hpp"
#include "rtl-main.h"

int main(int argc, char* argv[]) {
    ParsingComLine comLineArg(argc, argv);

    printf("cmd: -i %s -c %s -o %s\n", comLineArg.InFile_.c_str(), comLineArg.CfgFile_.c_str(),
           comLineArg.OutFile_.c_str());

    TestBenchConfig TBConfig = TestBenchConfig(comLineArg.CfgFile_);

    printf("%d; %d\n", TBConfig.video.height, TBConfig.video.width);

    hls::FIFO< axis_t > input_fifo(5);
    hls::FIFO< axis_t > output_fifo(5);

    std::ifstream inputFile(comLineArg.InFile_, std::ios::binary | std::ios::in);
    std::ofstream outputFile(comLineArg.OutFile_, std::ios::binary | std::ios::out | std::ios::trunc);

    auto frameNum = 0;
    inputFile.seekg((TBConfig.video.height * TBConfig.video.width * 2) * frameNum);

    for (size_t j = 0; j < frameNum + 1; j++) {
        if (inputFile.peek() == EOF) {
            break;
        }
        for (size_t y = 0; y < TBConfig.video.height; y++) {
            for (size_t x = 0; x < TBConfig.video.width; x++) {
                // read Input Data
                uint16_t RawData;
                inputFile.read((char*)&RawData, sizeof(uint16_t));
                axis_t axis_m;
                axis_m.tdata = RawData;
                axis_m.tuser = 0;
                axis_m.tlast = 0;
                input_fifo.write(axis_m);

                // user processing
                RTL_top(input_fifo, output_fifo);

                // write results
                while (!output_fifo.empty()) {
                    axis_t axis_s = output_fifo.read();
                    outputFile.write((char*)&axis_s.tdata, sizeof(uint16_t));
                }
            }
            printf("line[%d]\n", (int)y);
        }
    }

    printf("PASS\n");
    return 0;
}
