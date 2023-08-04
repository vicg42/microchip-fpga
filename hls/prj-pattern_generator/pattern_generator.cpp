#include "vision.hpp"
#include "define.hpp"
#include <assert.h>
#include <iostream>
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

using namespace hls;
using cv::Mat;
using vision::Img;
using vision::PixelType;
using vision::StorageType;

// RGB image type with 4 Pixels Per Clock (PPC)
using RgbImgT4PPC =
    Img<PixelType::HLS_8UC3, HEIGHT, WIDTH, StorageType::FIFO, vision::NPPC_4>;

// Pattern generator top function wrapper
template <int format, PixelType PIXEL_T, unsigned H, unsigned W,
          StorageType STORAGE, vision::NumPixelsPerCycle NPPC>
void PatternGeneratorWrapper(vision::Img<PIXEL_T, H, W, STORAGE, NPPC> &ImgOut)
{
#pragma HLS function top
    vision::PatternGenerator<format>(ImgOut);
}

// Testbench generates uses pattern generator to create an image and
// then compares it with a golden image file.
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

    printf("pattern-gen: -i %s -g %s -o %s\n", input_File_name, golden_File_name, output_File_name);

    RgbImgT4PPC ImgOut, GoldImg;
    // Pattern generator format (the generated image changes based on the
    // format)
    const int format = 0;
    // Generate output
    PatternGeneratorWrapper<format>(ImgOut);
    // Convert the output to cv::Mat for comparison with the golden output
    Mat OutMat;
    vision::convertToCvMat(ImgOut, OutMat);
    // Read golden image file
    Mat BGRGoldenMat = cv::imread(golden_File_name, cv::IMREAD_COLOR);
    Mat RGBGoldenMat;
    // Since cv::imread reads the image in BGR format, we convert to RGB
    cv::cvtColor(BGRGoldenMat, RGBGoldenMat, cv::COLOR_BGR2RGB);
    vision::convertFromCvMat(RGBGoldenMat, GoldImg);
    // Compare the output image with the golden image
    float ErrPercent = vision::compareMat(RGBGoldenMat, OutMat, 0);
    printf("Percentage of over threshold: %0.2lf%\n", ErrPercent);
    if (ErrPercent < 0.1f)
    {
        printf("PASS");
        return 0;
    }
    printf("FAIL");
    return 1;
}
