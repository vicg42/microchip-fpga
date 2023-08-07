#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <opencv2/opencv.hpp>

#include "vision.hpp"

char app_name[128];
static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
                                             {"input", required_argument, 0, 'i'},
                                             {"output", required_argument, 0, 'o'},
                                             {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];

using namespace hls;
using cv::Mat;
using vision::Img;

// #define SMALL_TEST_FRAME // for faster simulation.
#ifdef SMALL_TEST_FRAME
#define WIDTH 100
#define HEIGHT 56
#define INPUT_IMAGE "toronto_100x56.bmp"
#else
#define WIDTH 1920
#define HEIGHT 1080
#define INPUT_IMAGE "toronto_1080p.bmp"
#endif

#define NumPixels (WIDTH * HEIGHT)
#define NPPC 1
#define NumPixelWords (NumPixels / NPPC)
#define InPixelWordWidth (24 * NPPC)  // Input image is 8UC3
#define InAxiWordWidth 32             // Input AXI memory is 32-bit
#define InNumAxiWords (NumPixelWords * InPixelWordWidth / InAxiWordWidth)
#define OutPixelWordWidth (24 * NPPC)  // Output image is 8UC3
#define OutAxiWordWidth 32             // Output AXI memory is 32-bit
#define OutNumAxiWords (NumPixelWords * OutPixelWordWidth / OutAxiWordWidth)

// This top-level function performs width conversion to both directions:
// - uint32_t *InAxiMM -> TmpImg<8UC3>
// - TmpImg<8UC3> -> uint32_t *OutAxiMM
// Since Img<8UC3> has a pixel width of 24b, this tests both downscale read of
// 32b -> 24b, as well as upscale write of 24b -> 32b.
// Aside from doing the width conversion back and forth, this top-level doesn't
// do anything else. So in the end, we expect the content of InAxiMM and
// OutAxiMM to be exactly the same.
void hlsAxiWidthConversionTop(uint32_t *InAxiMM, uint32_t *OutAxiMM) {
#pragma HLS function top
#pragma HLS function dataflow
#pragma HLS interface argument(InAxiMM) type(axi_initiator) num_elements(InNumAxiWords) max_burst_len(256)
#pragma HLS interface argument(OutAxiMM) type(axi_target) num_elements(OutNumAxiWords)
    Img< vision::PixelType::HLS_8UC3, HEIGHT, WIDTH, vision::StorageType::FIFO, vision::NPPC_1 > TmpImg;

    vision::AxiMM2Img< InAxiWordWidth >(InAxiMM, TmpImg);
    vision::Img2AxiMM< OutAxiWordWidth >(TmpImg, OutAxiMM);
}

int main(int argc, char *argv[]) {
    int next = 0;
    do {
        switch (next = getopt_long(argc, argv, "hi:o:", long_opt_arr, 0)) {
            case 'i':
                strcpy(input_File_name, optarg);
                break;
            case 'o':
                strcpy(output_File_name, optarg);
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

    printf("ver1: -i %s -o %s\n", input_File_name, output_File_name);

    // Load image from file, using OpenCV's imread function.
    Mat InMat = cv::imread(input_File_name, cv::IMREAD_COLOR);

    /**
     * Call the SmartHLS top-level function.
     */
    // Set up the input and output regions of AXI memory.
    // Dynamic allocation since large image size can cause stack overflow.
    uint32_t *InAxiMM = new uint32_t[InNumAxiWords], *OutAxiMM = new uint32_t[OutNumAxiWords];
    // Then write the content of Mat to `InAxiMM`.
    memcpy(InAxiMM, InMat.data, NumPixelWords * InPixelWordWidth / 8);
    // Now, call the SmartHLS top-level function.
    hlsAxiWidthConversionTop(InAxiMM, OutAxiMM);
    // Finally, convert `OutAxiMM` into OpenCV `Mat`.
    Mat OutMat(HEIGHT, WIDTH, CV_8UC3, OutAxiMM);

    printf("input_File_name: %s\n", input_File_name);
    printf("output_File_name: %s\n", output_File_name);
    /**
     * Verification
     */
    // Write the input and output to an image.
    cv::imwrite(output_File_name, OutMat);

    // Check that the output is identical to the input.
    // float ErrPercent = vision::compareMatAndReport<cv::Vec3b>(InMat, OutMat,
    // 0);
    float ErrPercent = vision::compareMat(InMat, OutMat, 0);
    printf("Percentage of over threshold: %0.2lf%\n", ErrPercent);

    // Clean up
    delete[] InAxiMM;
    delete[] OutAxiMM;

    return ErrPercent;
}