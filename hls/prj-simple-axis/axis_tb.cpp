#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <toml.hpp>
#include <vector>

#include "BlockBase.h"
#include "ParsingComLine.h"
#include "ReadConfig.h"
#include "ReadFileData.h"
#include "block_1.h"
#include "block_2.h"
#include "hls/ap_fixpt.hpp"
#include "hls/ap_int.hpp"
#include "hls/streaming.hpp"

std::vector< BlockBase* > BlockBase::blockList;

const int RGB_BITWIDTH = 8;
struct RGB {
    hls::ap_uint< RGB_BITWIDTH > R;
    hls::ap_uint< RGB_BITWIDTH > G;
    hls::ap_uint< RGB_BITWIDTH > B;
};

const int YCBCR_BITWIDTH = 8;

struct YCbCr {
    hls::ap_uint< YCBCR_BITWIDTH > Y;
    hls::ap_uint< YCBCR_BITWIDTH > Cb;
    hls::ap_uint< YCBCR_BITWIDTH > Cr;
};

// Fixed point type: Q10.8
// 10 integer bits and 8 fractional bits
typedef hls::ap_fixpt< 18, 10 > fixpt_t;

void RGB2YCbCr_smarthls(hls::FIFO< RGB >& input_fifo, hls::FIFO< YCbCr >& output_fifo) {
#pragma HLS function top
#pragma HLS function pipeline

    RGB in = input_fifo.read();

    YCbCr ycbcr;

    // change divide by 256 to right shift by 8, add 0.5 for rounding
    ycbcr.Y =
        fixpt_t(16) + ((fixpt_t(65.738) * in.R + fixpt_t(129.057) * in.G + fixpt_t(25.064) * in.B) >> 8) + fixpt_t(0.5);
    ycbcr.Cb = fixpt_t(128) - ((fixpt_t(37.945) * in.R + fixpt_t(74.494) * in.G - fixpt_t(112.439) * in.B) >> 8) +
               fixpt_t(0.5);
    ycbcr.Cr = fixpt_t(128) + ((fixpt_t(112.439) * in.R - fixpt_t(94.154) * in.G - fixpt_t(18.285) * in.B) >> 8) +
               fixpt_t(0.5);

    output_fifo.write(ycbcr);
}

int main(int argc, char* argv[]) {
    ParsingComLine comLineArg(argc, argv);

    printf("cmd: -i %s -c %s -o %s\n", comLineArg.InFile_.c_str(), comLineArg.CfgFile_.c_str(),
           comLineArg.OutFile_.c_str());

    //create Raw file from image
    std::string inputFileRaw = "./_inputData.raw";
    char command[1024] = {0};
    memset(command, 0, sizeof(command));
    snprintf(command, sizeof(command), "python3 ../scripts/img2raw.py -i %s -o %s -n 10",
             comLineArg.InFile_.c_str(), inputFileRaw.c_str());
    system(command);

    Block1* module1 = new Block1("modA", 1);
    Block2* module2 = new Block2("modB", 2);
    ReadFileData* inputData = new ReadFileData("inputData", comLineArg.m_framesNum);
    ReadConfig* ConfigPipeline = new ReadConfig(comLineArg.CfgFile_, BlockBase::blockList);
    std::string dir = ConfigPipeline->GetDirName();
    printf("%s\n", dir.c_str());

    for (const auto& module : BlockBase::blockList) {
        module->Init();
    }
    inputData->ReadRawFile(inputFileRaw);
    module1->main();
    module2->main();

    hls::FIFO< RGB > input_fifo(5);
    hls::FIFO< YCbCr > output_fifo(5);
    hls::FIFO< YCbCr > expected_fifo(5);

    RGB in;
    YCbCr out, expected;

    // Use an online RGB to YCbCr color converter:
    //     http://www.picturetopeople.org/color_converter.html
    //
    // test 1
    in.R = 0;
    in.G = 0;
    in.B = 0;
    input_fifo.write(in);
    expected.Y = 16;
    expected.Cb = 128;
    expected.Cr = 128;
    expected_fifo.write(expected);

    // test 2
    in.R = 6;
    in.G = 9;
    in.B = 12;
    input_fifo.write(in);
    expected.Y = 23;
    expected.Cb = 130;
    expected.Cr = 126;
    expected_fifo.write(expected);

    // test 3
    in.R = 23;
    in.G = 42;
    in.B = 59;
    input_fifo.write(in);
    expected.Y = 49;
    expected.Cb = 138;
    expected.Cr = 118;
    expected_fifo.write(expected);

    // test 4
    in.R = 77;
    in.G = 83;
    in.B = 168;
    input_fifo.write(in);
    expected.Y = 94;
    expected.Cb = 166;
    expected.Cr = 119;
    expected_fifo.write(expected);

    // test 5
    in.R = 119;
    in.G = 138;
    in.B = 152;
    input_fifo.write(in);
    expected.Y = 131;
    expected.Cb = 137;
    expected.Cr = 119;
    expected_fifo.write(expected);

    while (!input_fifo.empty()) {
        RGB2YCbCr_smarthls(input_fifo, output_fifo);
        out = output_fifo.read();
        expected = expected_fifo.read();

        std::cout << "Expected: Y=" << expected.Y.to_string(10) << " Cb=" << expected.Cb.to_string(10)
                  << " Cr=" << expected.Cr.to_string(10) << std::endl;
        std::cout << "Actual: Y=" << out.Y.to_string(10) << " Cb=" << out.Cb.to_string(10)
                  << " Cr=" << out.Cr.to_string(10) << std::endl;

        if (out.Y != expected.Y || out.Cb != expected.Cb || out.Cr != expected.Cr) {
            printf("FAIL\n");
            return 1;
        }
    }

    printf("PASS\n");
    return 0;
}
