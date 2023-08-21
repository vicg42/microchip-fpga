#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "axi-target.h"
#include "axis.h"
#include "hls/streaming.hpp"

char app_name[128];
static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
                                             {"input", required_argument, 0, 'i'},
                                             {"output", required_argument, 0, 'o'},
                                             {"cfg", required_argument, 0, 'g'},
                                             {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];
char cfg_File_name[100];

struct video_st {
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
    uint32_t size;
};

int readImage(const char *filename, uint8_t *buf, struct video_st *param) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error1: readImage\n");
        return -1;
    }

    if (fread(buf, sizeof(uint8_t), (param->size * param->bpp), file) != (param->size * param->bpp)) {
        printf("Error2: readImage\n");
        return -1;
    }

    fclose(file);
    return 0;
}

void writeImage(const char *filename, uint8_t *buf, struct video_st *param) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error1: writeImage\n");
        return;
    }

    fwrite(buf, sizeof(uint8_t), (param->size * param->bpp), file);
    fclose(file);
}

#pragma HLS interface variable(axi_target) type(axi_slave)
struct AxiTarget_st axi_target;

void rtl_top(hls::FIFO< axis_t > &ififo, hls::FIFO< axis_t > &ofifo) {
#pragma HLS function top
    axi_target.sum_result = (uint64_t)axi_target.a + (uint64_t)axi_target.b + axi_target.arr[0] + axi_target.arr[1] +
                            axi_target.arr[2] + axi_target.arr[3] + axi_target.arr[4] + axi_target.arr[5] +
                            axi_target.arr[6] + axi_target.arr[7];
    axi_target.xor_result = axi_target.a ^ axi_target.b ^ axi_target.arr[0] ^ axi_target.arr[1] ^ axi_target.arr[2] ^
                            axi_target.arr[3] ^ axi_target.arr[4] ^ axi_target.arr[5] ^ axi_target.arr[6] ^
                            axi_target.arr[7];
    axi_target.or_result = axi_target.a | axi_target.b | axi_target.arr[0] | axi_target.arr[1] | axi_target.arr[2] |
                           axi_target.arr[3] | axi_target.arr[4] | axi_target.arr[5] | axi_target.arr[6] |
                           axi_target.arr[7];

    if (ififo.empty()) return;

    axis_t axis_in = ififo.read();
    axis_t axis_out;

    axis_out.tdata = axis_in.tdata * axi_target.a;
    axis_out.tuser = axis_in.tuser;
    axis_out.tlast = axis_in.tlast;

    ofifo.write(axis_out);
}

int main(int argc, char *argv[]) {
    int next = 0;
    do {
        switch (next = getopt_long(argc, argv, "hi:o:c:", long_opt_arr, 0)) {
            case 'i':
                strcpy(input_File_name, optarg);
                break;
            case 'o':
                strcpy(output_File_name, optarg);
                break;
            case 'c':
                strcpy(cfg_File_name, optarg);
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

    printf("getopt: -i %s -c %s -o %s\n", input_File_name, cfg_File_name, output_File_name);

    hls::FIFO< axis_t > input_fifo(5);
    hls::FIFO< axis_t > output_fifo(5);
    uint8_t frameNum = 0;
    struct video_st ifr;
    ifr.height = 56;
    ifr.width = 100;
    ifr.bpp = 2;
    ifr.size = ifr.height * ifr.width;
    printf("%d; %d\n", ifr.height, ifr.width);

    // uint8_t InputFileData[500];
    // uint8_t OutputFileData[500];
    uint8_t *InputFileData = (uint8_t *)malloc((ifr.height * ifr.width) * ifr.bpp);
    uint8_t *OutputFileData = (uint8_t *)malloc((ifr.height * ifr.width) * ifr.bpp);
    uint16_t *InputFileData_ptr = (uint16_t *)InputFileData;
    uint16_t *OutputFileData_ptr = (uint16_t *)OutputFileData;

    int result = 0;
    result = readImage(input_File_name, InputFileData, &ifr);
    if (result < 0) {
        printf("Error: read FileData1\n");
        return -1;
    }

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

    // rtl_top();

    axis_t axis_m;
    axis_t axis_s;
    for (size_t y = 0; y < ifr.height; y++) {
        for (size_t x = 0; x < ifr.width; x++) {
            // read Input Data
            uint16_t RawData;
            RawData = *InputFileData_ptr;  //
            axis_m.tdata = RawData;
            axis_m.tuser = 0;
            if (x == (ifr.width - 1)) {
                axis_m.tlast = 1;
            } else {
                axis_m.tlast = 0;
            }
            input_fifo.write(axis_m);
            InputFileData_ptr++;

            // user processing
            rtl_top(input_fifo, output_fifo);

            // write results
            while (!output_fifo.empty()) {
                axis_s = output_fifo.read();
                *OutputFileData_ptr = axis_s.tdata;
                OutputFileData_ptr++;
            }
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