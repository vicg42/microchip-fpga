#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include "vision.hpp"
#include <opencv2/opencv.hpp>

char app_name[128];
static const struct option long_opt_arr[] = {
    {"help", no_argument, 0, 'h'},
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},
    {"outcv", required_argument, 0, 'c'},
    {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];
char output_CV_name[100];

using namespace hls;
using cv::Mat;
using vision::Img;

#define WIDTH 100
#define HEIGHT 56
// #define INPUT_IMAGE "toronto_100x56.bmp"

#define NumPixels (WIDTH * HEIGHT)
#define NPPC 1
#define NumPixelWords (NumPixels / NPPC)
#define InPixelWordWidth (8 * NPPC) // Input image is 8UC1
#define InAxiWordWidth 32           // Input AXI memory is 32-bit
#define InNumAxiWords (NumPixelWords * InPixelWordWidth / InAxiWordWidth)
#define OutPixelWordWidth (16 * NPPC) // Output image is 16SC1
#define OutAxiWordWidth 32            // Output AXI memory is 32-bit
#define OutNumAxiWords (NumPixelWords * OutPixelWordWidth / OutAxiWordWidth)

// InAxiMM: AXI-Initiator
// OutAxiMM: AXI-Initiator
template <vision::PixelType PIXEL_T_IN, vision::PixelType PIXEL_T_OUT,
          unsigned H, unsigned W, vision::StorageType STORAGE_IN,
          vision::StorageType STORAGE_OUT, vision::NumPixelsPerCycle NPPC_IN,
          vision::NumPixelsPerCycle NPPC_OUT>
void hlsSobel(uint32_t *InAxiMM, uint32_t *OutAxiMM)
{
#pragma HLS function top
#pragma HLS function dataflow
#pragma HLS interface argument(InAxiMM) type(axi_initiator) \
    num_elements(InNumAxiWords) max_burst_len(256)
#pragma HLS interface argument(OutAxiMM) type(axi_initiator) \
    num_elements(OutNumAxiWords) max_burst_len(256)

    Img<PIXEL_T_IN, H, W, STORAGE_IN, NPPC_IN> InImg;
    Img<PIXEL_T_OUT, H, W, STORAGE_OUT, NPPC_OUT> OutImg;

    // 1. AXI Memory to Img conversion
    vision::AxiMM2Img<InAxiWordWidth>(InAxiMM, InImg);
    // 2. Call the processing function i.e. vision::Sobel()
    vision::Sobel<3>(InImg, OutImg);
    // 3. Img to AXI Memory conversion
    vision::Img2AxiMM<OutAxiWordWidth>(OutImg, OutAxiMM);
}

//  Use OpenCV's Sobel as reference.
void cvSobel(cv::Mat &InMat, cv::Mat &OutMat)
{
    // Compute x- and y-direction gradiations first.
    Mat CvGx, CvGy;
    cv::Sobel(InMat, CvGx, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_CONSTANT);
    cv::Sobel(InMat, CvGy, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_CONSTANT);

    // Then combine the absolute values of the X/Y gradients.
    Mat CvGxAbs, CvGyAbs;
    CvGxAbs = cv::abs(CvGx);
    CvGyAbs = cv::abs(CvGy);
    cv::add(CvGxAbs, CvGyAbs, OutMat);
}

int main(int argc, char *argv[])
{
    int next = 0;
    do
    {
        switch (next = getopt_long(argc, argv, "hi:o:c:", long_opt_arr, 0))
        {
        case 'i':
            strcpy(input_File_name, optarg);
            break;
        case 'o':
            strcpy(output_File_name, optarg);
            break;
        case 'c':
            strcpy(output_CV_name, optarg);
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

    printf("ver1: -i %s -o %s -c %s\n", input_File_name, output_File_name, output_CV_name);

    // Load image from file, using OpenCV's imread function.
    Mat InMat = cv::imread(input_File_name, cv::IMREAD_GRAYSCALE);

    /*
     * Call the SmartHLS top-level function and the OpenCV reference function,
     * and compare the 2 results.
     */
    // 1. SmartHLS result
    // Set up the input and output regions of AXI memory.
    // Dynamic allocation since large image size can cause stack overflow.
    uint32_t *InAxiMM = new uint32_t[InNumAxiWords],
             *OutAxiMM = new uint32_t[OutNumAxiWords];
    // Then write the content of Mat to `InAxiMM`.
    memcpy(InAxiMM, InMat.data, NumPixelWords * InPixelWordWidth / 8);
    // Now, call the SmartHLS top-level function.
    hlsSobel</*PIXEL_T_IN=*/vision::PixelType::HLS_8UC1,
             /*PIXEL_T_OUT=*/vision::PixelType::HLS_16SC1, /*H=*/HEIGHT,
             /*W=*/WIDTH, /*STORAGE_IN=*/vision::StorageType::FIFO,
             /*STORAGE_OUT=*/vision::StorageType::FIFO,
             /*NPPC_IN=*/vision::NPPC_1, /*NPPC_OUT=*/vision::NPPC_1>(InAxiMM,
                                                                      OutAxiMM);
    // Finally, convert the `OutAxiMM` back to OpenCV `Mat`.
    Mat HlsOutMat_8UC1;
    Mat HlsOutMat_16SC1(HEIGHT, WIDTH, CV_16SC1, OutAxiMM);
    HlsOutMat_16SC1.convertTo(HlsOutMat_8UC1, CV_8UC1);

    // 2. OpenCV result
    Mat CvOutMat;
    cvSobel(InMat, CvOutMat);
    cv::convertScaleAbs(CvOutMat, CvOutMat);

    // 3. Print the HlsOutMat_8UC1 and CvOutMat as pictures for reference.
    cv::imwrite(output_File_name, HlsOutMat_8UC1);
    cv::imwrite(output_CV_name, CvOutMat);

    // 4. Compare the SmartHLS result and the OpenCV result.
    // Use this commented out line to report location of errors.
    // vision::compareMatAndReport<unsigned char>(HlsOutMat_8UC1, CvOutMat, 0);
    float ErrPercent = vision::compareMat(HlsOutMat_8UC1, CvOutMat, 0);
    printf("Percentage of over threshold: %0.2lf%\n", ErrPercent);

    // Clean up
    delete[] InAxiMM;
    delete[] OutAxiMM;

    return ErrPercent;
}
