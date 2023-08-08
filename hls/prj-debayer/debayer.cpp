#include "vision.hpp"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

char app_name[128];
static const struct option long_opt_arr[] = {
    {"help", no_argument, 0, 'h'},
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},
    {"golden", required_argument, 0, 'g'},
    {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];
char golden_File_name[100];

// This line tests on a smaller image for faster co-simulation.
// #define FAST_COSIM

#ifdef FAST_COSIM
#define WIDTH 100
#define HEIGHT 56
#define INPUT_IMAGE "toronto_100x56.bmp"
#define GOLDEN_OUTPUT "toronto_100x56.bmp"

#else
#define WIDTH 1920
#define HEIGHT 1080
#define INPUT_IMAGE "toronto_1080p.bmp"
#define GOLDEN_OUTPUT "toronto_1080p.bmp"
#endif

#define SIZE (WIDTH * HEIGHT)

// RGB and Bayer image types with 4 Pixels Per Clock (4PPC)
// Using 4 pixels per clock would enable using lower clock frequencies in
// hardware. This is particularly useful when dealing with 4K data, but can help
// lower the required Fmax in other resolutions as well, making hardware
// implementation easier.
using RgbImgT4PPC =
    hls::vision::Img<hls::vision::PixelType::HLS_8UC3, HEIGHT, WIDTH, hls::vision::StorageType::FIFO, hls::vision::NPPC_4>;
using BayerImgT4PPC =
    hls::vision::Img<hls::vision::PixelType::HLS_8UC1, HEIGHT, WIDTH, hls::vision::StorageType::FIFO, hls::vision::NPPC_4>;

template <hls::vision::PixelType PIXEL_T_IN, hls::vision::PixelType PIXEL_T_OUT, unsigned H, unsigned W,
          hls::vision::StorageType STORAGE_IN, hls::vision::StorageType STORAGE_OUT,
          hls::vision::NumPixelsPerCycle NPPC = hls::vision::NPPC_1>
void DeBayerWrapper(hls::vision::Img<PIXEL_T_IN, H, W, STORAGE_IN, NPPC> &ImgIn,
                    hls::vision::Img<PIXEL_T_OUT, H, W, STORAGE_OUT, NPPC> &ImgOut,
                    hls::ap_uint<2> BayerFormat = 0)
{
#pragma HLS function top
    hls::vision::DeBayer(ImgIn, ImgOut, BayerFormat);
}

template <hls::vision::PixelType PIXEL_T_IN, hls::vision::PixelType PIXEL_T_OUT, unsigned H, unsigned W,
          hls::vision::StorageType STORAGE = hls::vision::FIFO,
          hls::vision::NumPixelsPerCycle NPPC = hls::vision::NPPC_1>
void RGB2BayerWrapper(hls::vision::Img<PIXEL_T_IN, H, W, STORAGE, NPPC> &ImgIn,
                      hls::vision::Img<PIXEL_T_OUT, H, W, STORAGE, NPPC> &ImgOut)
{
#pragma HLS function top
    hls::vision::RGB2Bayer(ImgIn, ImgOut);
}

int main(int argc, char *argv[])
{
    int next = 0;
    do
    {
        switch (next = getopt_long(argc, argv, "hi:o:g:", long_opt_arr, 0))
        {
        case 'i':
            strcpy(input_File_name, optarg);
            break;
        case 'o':
            strcpy(output_File_name, optarg);
            break;
        case 'g':
            strcpy(golden_File_name, optarg);
            break;
        case -1: // no more options
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

    printf("debayer: -i %s -g %s -o %s\n", input_File_name, golden_File_name, output_File_name);

    RgbImgT4PPC InImg, OutImg, DeBayerGoldImg;
    BayerImgT4PPC BayerImg;

    // Read input image into a cv Mat and convert it to RGB format since cv
    // reads images in BGR format
    cv::Mat BGRInMat = cv::imread(input_File_name, cv::IMREAD_COLOR);
    cv::Mat RGBInMat;
    cv::cvtColor(BGRInMat, RGBInMat, cv::COLOR_BGR2RGB);

    // Convert the cv Mat into Img class
    convertFromCvMat(RGBInMat, InImg);
    // Process the input, converting RGB to bayer and bayer back to RGB
    RGB2BayerWrapper(InImg, BayerImg);
    DeBayerWrapper(BayerImg, OutImg, 0);

    // Convert the output image to cv Mat for comparing with the input image.
    // As we convert the RGB input image to bayer format and convert back to
    // RGB, the input and output images should be similar
    cv::Mat OutMat;
    hls::vision::convertToCvMat(OutImg, OutMat);

    cv::imwrite(output_File_name, OutMat);

    // Compare the output image with the input image
    // Converting RGB to bayer format results in 3x reduction in data size, and
    // converting back from bayer to RGB (using debayer function) will result in
    // mismatch.
    // So we will say pass as long as less than 5% of pixels (each channel) have
    // mismatch greater than 32 (in range of 0-255).
    float ErrPercent = hls::vision::compareMat(RGBInMat, OutMat, 32);
    printf("Percentage of over threshold: %0.2lf%\n", ErrPercent);
    if (ErrPercent < 5)
    {
        printf("PASS");
        return 0;
    }
    printf("FAIL");
    return 1;
}
