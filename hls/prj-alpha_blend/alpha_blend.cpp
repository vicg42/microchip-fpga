#include "hls/ap_int.hpp"
#include "hls/ap_fixpt.hpp"
#include "hls/streaming.hpp"
#include <iostream>
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
    {"blend", required_argument, 0, 'b'},
    {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];
char golden_File_name[100];
char blend_File_name[100];

using namespace hls;

// bit width of a pixel
const int W = 8;

// 24-bit RGB
typedef ap_uint<3 * W> rgb_t;

// 7:0 blue
const int B2 = 0;
const int B1 = B2 + W - 1;

// 15:8 green
const int G2 = W;
const int G1 = G2 + W - 1;

// 23:16 red
const int R2 = 2 * W;
const int R1 = R2 + W - 1;

struct input_t
{
    rgb_t channel1;
    rgb_t channel2;
    ap_uint<8> alpha;
};

// uncomment this line to test on a smaller image for faster co-simulation
// #define FAST_COSIM

#ifdef FAST_COSIM
#define WIDTH 100
#define HEIGHT 56
// #define INPUT_IMAGE1 "toronto_100x56.bmp"
// #define INPUT_IMAGE2 "polarfire_100x56.bmp"
// #define GOLDEN_OUTPUT "golden_output_100x56.bmp"
#else
#define WIDTH 1920
#define HEIGHT 1080
// #define INPUT_IMAGE1 "toronto.bmp"
// #define INPUT_IMAGE2 "polarfire.bmp"
// #define GOLDEN_OUTPUT "golden_output.bmp"
#endif
#define SIZE (WIDTH * HEIGHT)

struct bmp_pixel_t
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

// Total: 54 bytes
struct bmp_header_t
{
    uint16_t type;             // Magic identifier: 0x4d42
    uint32_t size;             // File size in bytes
    uint32_t reserved;         // Not used
    uint32_t offset;           // Offset to image data in bytes from beginning of file (54 bytes)
    uint32_t dib_header_size;  // DIB Header size in bytes (40 bytes)
    int32_t width;             // Width of the image
    int32_t height;            // Height of image
    uint16_t num_planes;       // Number of color planes
    uint16_t bits_per_pixel;   // Bits per pixel
    uint32_t compression;      // Compression type
    uint32_t image_size;       // Image size in bytes
    int32_t x_resolution_ppm;  // Pixels per meter
    int32_t y_resolution_ppm;  // Pixels per meter
    uint32_t num_colors;       // Number of colors
    uint32_t important_colors; // Important colors
} __attribute__((__packed__));

bmp_pixel_t *read_bmp(const char *filename, bmp_header_t *header)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
        return NULL;

    // read BMP header and verify width/height
    if (fread(header, sizeof(bmp_header_t), 1, file) != 1)
        return NULL;
    if (header->offset != sizeof(bmp_header_t) ||
        header->width != WIDTH || header->height != HEIGHT)
        return NULL;

    // allocate image buffer
    bmp_pixel_t *image = (bmp_pixel_t *)malloc(SIZE * sizeof(bmp_pixel_t));

    // read BMP image
    if (fread(image, sizeof(bmp_pixel_t), SIZE, file) != SIZE)
        return NULL;

    fclose(file);
    return image;
}

void write_bmp(const char *filename, const bmp_header_t *header, const bmp_pixel_t *image)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
        return;
    fwrite(header, sizeof(bmp_header_t), 1, file);
    fwrite(image, sizeof(bmp_pixel_t), SIZE, file);
    fclose(file);
}

void alpha_blend_smarthls(hls::FIFO<input_t> &input_fifo,
                          hls::FIFO<rgb_t> &output_fifo)
{

#pragma HLS function top
#pragma HLS function pipeline

    input_t in = input_fifo.read();

    // alpha ranges from 0 to 255
    ap_uint<16> alpha = 1 + in.alpha;
    rgb_t out;

    // red
    out(R1, R2) = (in.channel1(R1, R2) * (256 - alpha) + in.channel2(R1, R2) * alpha) >> 8;
    // green
    out(G1, G2) = (in.channel1(G1, G2) * (256 - alpha) + in.channel2(G1, G2) * alpha) >> 8;
    // blue
    out(B1, B2) = (in.channel1(B1, B2) * (256 - alpha) + in.channel2(B1, B2) * alpha) >> 8;

    output_fifo.write(out);
}

int main(int argc, char *argv[])
{
    int next = 0;
    do
    {
        switch (next = getopt_long(argc, argv, "hi:o:g:b:", long_opt_arr, 0))
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
        case 'b':
            strcpy(blend_File_name, optarg);
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

    printf("alpha_blend: -i %s -b %s -g %s -o %s\n", input_File_name, blend_File_name, golden_File_name, output_File_name);

    bmp_header_t input_channel1_header, input_channel2_header,
        golden_output_image_header;
    bmp_pixel_t *input_channel1, *input_channel2, *golden_output_image,
        *output_image, *output_image_ptr;
    input_t in;

    hls::FIFO<input_t> input_fifo(1);
    hls::FIFO<rgb_t> output_fifo(1);

    // read inputs from file
    input_channel1 = read_bmp(input_File_name, &input_channel1_header);
    if (!input_channel1)
    {
        printf("Error: read %s\n", input_File_name);
        return 1;
    }

    input_channel2 = read_bmp(blend_File_name, &input_channel2_header);
    if (!input_channel2)
    {
        printf("Error: read %s\n", blend_File_name);
        return 1;
    }

    golden_output_image = read_bmp(golden_File_name, &golden_output_image_header);
    if (!golden_output_image)
    {
        printf("Error: read %s\n", golden_File_name);
        return 1;
    }

    output_image = (bmp_pixel_t *)malloc(SIZE * sizeof(bmp_pixel_t));
    output_image_ptr = output_image;

    // test 1: sanity check from alpha blend IP core documentation
    in.channel1 = ap_uint<24>("0x456712");
    in.channel2 = ap_uint<24>("0x547698");
    in.alpha = ap_uint<8>("0x84");
    input_fifo.write(in);
    alpha_blend_smarthls(input_fifo, output_fifo);
    rgb_t out = output_fifo.read();
    if (out != ap_uint<24>("4C6E57"))
    {
        std::cout << "out = " << out.to_string() << std::endl;
        std::cout << "FAIL!" << std::endl;
        return 1;
    }

    // test 2: input image
    // in.alpha = (int)(255 * 0);
    // in.alpha = (int)(255 * 0.25);
    in.alpha = (int)(255 * 0.5);
    // in.alpha = (int)(255 * 0.75);
    // in.alpha = (int)(255 * 1);
    std::cout << "Alpha = " << in.alpha.to_string(10) << std::endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {

            // concatenation operator
            in.channel1 = (ap_uint<8>(input_channel1->r),
                           ap_uint<8>(input_channel1->g),
                           ap_uint<8>(input_channel1->b));
            in.channel2 = (ap_uint<8>(input_channel2->r),
                           ap_uint<8>(input_channel2->g),
                           ap_uint<8>(input_channel2->b));

            input_fifo.write(in);

            // run design
            alpha_blend_smarthls(input_fifo, output_fifo);

            rgb_t rgb = output_fifo.read();
            output_image_ptr->r = rgb(R1, R2);
            output_image_ptr->g = rgb(G1, G2);
            output_image_ptr->b = rgb(B1, B2);
            if (output_image_ptr->r != golden_output_image->r ||
                output_image_ptr->g != golden_output_image->g ||
                output_image_ptr->b != golden_output_image->b)
            {
                printf("FAIL!\n");
                return 1;
            }

            input_channel1++;
            input_channel2++;
            output_image_ptr++;
            golden_output_image++;
        }
    }

    write_bmp(output_File_name, &input_channel1_header, output_image);

    printf("PASS!\n");
    return 0;
}
