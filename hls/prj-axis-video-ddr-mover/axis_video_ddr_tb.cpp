#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#include "vision.hpp"

char app_name[128];
static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
                                             {"input", required_argument, 0, 'i'},
                                             {"output", required_argument, 0, 'o'},
                                             {"golden", required_argument, 0, 'g'},
                                             {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];
char golden_File_name[100];

// #define SMALL_TEST_FRAME // for faster simulation.
// #define UHD_TEST_FRAME // for 4K simulation.
#ifdef SMALL_TEST_FRAME
#define WIDTH 100
#define HEIGHT 56
#define INPUT_IMAGE "toronto_100x56.bmp"
#else
#ifdef UHD_TEST_FRAME
#define WIDTH 3840
#define HEIGHT 2160
#define INPUT_IMAGE "ddr_4k_golden.png"
#else
#define WIDTH 1920
#define HEIGHT 1080
#define INPUT_IMAGE "toronto_1080p.bmp"
#endif
#endif

#define NumPixels (WIDTH * HEIGHT)
#define PPC 4
#define NumPixelWords (NumPixels / PPC)
#define PixelWordWidth (8 * PPC)  // Image is 8UC1
#define AxiWordWidth 64           // AXI memory is 64-bit
#define NumAxiWords (NumPixelWords * PixelWordWidth / AxiWordWidth)

template < hls::vision::PixelType PIXEL_I_T, hls::vision::NumPixelsPerCycle NPPC = hls::vision::NPPC_1 >
void DDR_Read_Wrapper(uint64_t *Buf, hls::vision::AxisVideoFIFO< PIXEL_I_T, NPPC > &VideoOut, int HRes, int VRes) {
// #pragma HLS function top
#pragma HLS function dataflow
#pragma HLS interface argument(Buf) type(axi_initiator) num_elements(NumAxiWords) max_burst_len(256)

    hls::vision::AxiMM2AxisVideo< AxiWordWidth, uint64_t, HEIGHT, WIDTH >(Buf, VideoOut, HRes, VRes);
}

template < hls::vision::PixelType PIXEL_I_T, hls::vision::NumPixelsPerCycle NPPC = hls::vision::NPPC_1 >
void DDR_Write_Wrapper(hls::vision::AxisVideoFIFO< PIXEL_I_T, NPPC > &VideoIn, uint64_t *Buf, int HRes, int VRes) {
#pragma HLS function top
#pragma HLS function dataflow
#pragma HLS interface argument(Buf) type(axi_initiator) num_elements(NumAxiWords) max_burst_len(256)

    hls::vision::AxisVideo2AxiMM< AxiWordWidth, uint64_t, HEIGHT, WIDTH >(VideoIn, Buf, HRes, VRes);
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

    printf("axis-video-ddr-mover: -i %s -g %s -o %s\n", input_File_name, golden_File_name, output_File_name);

    // Load image from file, using OpenCV's imread function.
    cv::Mat InMat = cv::imread(input_File_name, cv::IMREAD_GRAYSCALE);

    hls::vision::Img< hls::vision::PixelType::HLS_8UC1, HEIGHT, WIDTH, hls::vision::StorageType::FIFO,
                      hls::vision::NPPC_4 >
        InImg, OutImg;
    hls::vision::AxisVideoFIFO< hls::vision::PixelType::HLS_8UC1, hls::vision::NPPC_4 > InAxisVideo(NumPixelWords),
        OutAxisVideo(NumPixelWords);

    // 1. Set up the input.
    // Set up the AXI memory map.
    // Dynamic allocation since large image size can cause stack overflow.
    uint64_t *Buf = new uint64_t[NumAxiWords];
    // Read the input image into `InAxisVideo`
    hls::vision::convertFromCvMat(InMat, InImg);
    hls::vision::Img2AxisVideo(InImg, InAxisVideo);

    // 2. Call the SmartHLS top-level functions.
    // Generate output by doing DDR write and reading the same data back
    // We expect the output data is identical to the input data at the end.
    DDR_Write_Wrapper(InAxisVideo, Buf, WIDTH, HEIGHT);
    DDR_Read_Wrapper(Buf, OutAxisVideo, WIDTH, HEIGHT);

    // 3. Verify the output
    hls::vision::AxisVideo2Img(OutAxisVideo, OutImg);
    // Convert the output image to cv cv::Mat for comparing with the input image.
    cv::Mat OutMat;
    hls::vision::convertToCvMat(OutImg, OutMat);
    // Compare the output with the input, we should read the same data we write
    // to DDR
    float ErrPercent = hls::vision::compareMat(InMat, OutMat, 0);
    printf("Percentage of over threshold: %0.2lf%\n", ErrPercent);
    // Consider the test passes if there is less than 1% of pixels in
    // difference.
    bool Pass = (ErrPercent < 1.f);
    printf("%s\n", Pass ? "PASS" : "FAIL");

    // Clean up
    delete[] Buf;
    return Pass ? 0 : 1;  // Only return 0 on pass.
}
