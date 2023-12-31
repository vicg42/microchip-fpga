#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "hls/ap_fixpt.hpp"
#include "hls/ap_int.hpp"
#include "hls/streaming.hpp"

char app_name[128];
static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
                                             {"input", required_argument, 0, 'i'},
                                             {"output", required_argument, 0, 'o'},
                                             {"golden", required_argument, 0, 'g'},
                                             {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];
char golden_File_name[100];

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

// Fixed point type: Q11.7
// 11 integer bits and 7 fractional bits
typedef hls::ap_fixpt< 18, 11 > fixpt_t;

void YCbCr2RGB_smarthls(hls::FIFO< YCbCr > &input_fifo, hls::FIFO< RGB > &output_fifo) {
#pragma HLS function top
#pragma HLS function pipeline

    YCbCr in = input_fifo.read();

    RGB rgb;
    float ttt = -222.921;

    // change divide by 256 to right shift by 8, add 0.5 for rounding
    fixpt_t R = fixpt_t(ttt) + ((fixpt_t(298.082) * in.Y + fixpt_t(408.583) * in.Cr) >> 8) + fixpt_t(0.5);
    fixpt_t G = fixpt_t(135.576) +
                ((fixpt_t(298.082) * in.Y - fixpt_t(100.291) * in.Cb - fixpt_t(208.120) * in.Cr) >> 8) + fixpt_t(0.5);
    fixpt_t B = fixpt_t(-276.836) + ((fixpt_t(298.082) * in.Y + fixpt_t(516.412) * in.Cb) >> 8) + fixpt_t(0.5);

    // saturate values to [0, 255] range
    rgb.R = hls::ap_ufixpt< 8, 8, hls::AP_TRN, hls::AP_SAT >(R);
    rgb.G = hls::ap_ufixpt< 8, 8, hls::AP_TRN, hls::AP_SAT >(G);
    rgb.B = hls::ap_ufixpt< 8, 8, hls::AP_TRN, hls::AP_SAT >(B);

    output_fifo.write(rgb);
}

int main(int argc, char *argv[]) {
    int next = 0;
    do {
        switch (next = getopt_long(argc, argv, "hi:o:g:", long_opt_arr, 0)) {
            case 'i':
                strcpy(input_File_name, optarg);
                break;
            case 'o':
                strcpy(output_File_name, optarg);
                break;
            case 'g':
                strcpy(golden_File_name, optarg);
                break;
            case -1:  // no more options
                break;
            case 'h':
                strncpy(app_name, __FILE__, (strlen(__FILE__) - 2));
                printf("Usage: ./%s [option]\n", app_name);
                printf("Mandatory option: \n");
                printf("    -h  --help              help\n");
                printf("    -i          <path>      default: %s\n", input_File_name);
                exit(EXIT_SUCCESS);
            default:
                exit(EINVAL);
        };
    } while (next != -1);

    printf("ycbcr2rgb: -i %s -g %s -o %s\n", input_File_name, golden_File_name, output_File_name);

    hls::FIFO< YCbCr > input_fifo(10);
    hls::FIFO< RGB > output_fifo(10);
    hls::FIFO< RGB > expected_fifo(10);

    YCbCr in;
    RGB out, expected;

    // Use an online YCbCr to RGB color converter:
    //     http://www.picturetopeople.org/color_converter.html
    // Note: this calculator doesn't handle saturation properly in all cases

    // test 1
    in.Y = 0;
    in.Cb = 0;
    in.Cr = 0;
    input_fifo.write(in);
    expected.R = 0;
    expected.G = 136;
    expected.B = 0;
    expected_fifo.write(expected);

    // test 2
    in.Y = 136;
    in.Cb = 158;
    in.Cr = 102;
    input_fifo.write(in);
    expected.R = 98;
    expected.G = 149;
    expected.B = 200;
    expected_fifo.write(expected);

    // test 3
    in.Y = 146;
    in.Cb = 148;
    in.Cr = 108;
    input_fifo.write(in);
    expected.R = 119;
    expected.G = 160;
    expected.B = 192;
    expected_fifo.write(expected);

    // test 4
    in.Y = 111;
    in.Cb = 143;
    in.Cr = 196;
    input_fifo.write(in);
    expected.R = 219;
    expected.G = 49;
    expected.B = 141;
    expected_fifo.write(expected);

    // test 5
    in.Y = 147;
    in.Cb = 120;
    in.Cr = 110;
    input_fifo.write(in);
    expected.R = 124;
    expected.G = 170;
    expected.B = 136;
    expected_fifo.write(expected);

    // test 6
    in.Y = 255;
    in.Cb = 255;
    in.Cr = 255;
    input_fifo.write(in);
    expected.R = 255;
    expected.G = 125;
    expected.B = 255;
    expected_fifo.write(expected);

    // test 7
    in.Y = 235;
    in.Cb = 128;
    in.Cr = 128;
    input_fifo.write(in);
    expected.R = 255;
    expected.G = 255;
    expected.B = 255;
    expected_fifo.write(expected);

    while (!input_fifo.empty()) {
        YCbCr2RGB_smarthls(input_fifo, output_fifo);
        out = output_fifo.read();
        expected = expected_fifo.read();

        std::cout << "Expected: R=" << expected.R.to_string(10) << " G=" << expected.G.to_string(10)
                  << " B=" << expected.B.to_string(10) << std::endl;
        std::cout << "Actual: R=" << out.R.to_string(10) << " G=" << out.G.to_string(10) << " B=" << out.B.to_string(10)
                  << std::endl;
        if (out.R != expected.R || out.G != expected.G || out.B != expected.B) {
            printf("FAIL\n");
            return 1;
        }
    }

    printf("PASS\n");
    return 0;
}
