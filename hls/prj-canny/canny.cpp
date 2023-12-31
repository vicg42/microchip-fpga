#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.hpp"
#include "define.hpp"

char app_name[128];
static const struct option long_opt_arr[] = {{"help", no_argument, 0, 'h'},
                                             {"input", required_argument, 0, 'i'},
                                             {"output", required_argument, 0, 'o'},
                                             {"golden", required_argument, 0, 'g'},
                                             {0, 0, 0, 0}};
char input_File_name[100];
char output_File_name[100];
char golden_File_name[100];

void canny(hls::FIFO< unsigned char > &input_fifo, hls::FIFO< unsigned char > &output_fifo) {
#pragma HLS function top
#pragma HLS function dataflow

    hls::FIFO< unsigned char > output_fifo_gf(/* depth = */ 2);
    hls::FIFO< unsigned short > output_fifo_sf(/* depth = */ 2);
    hls::FIFO< unsigned char > output_fifo_nm(/* depth = */ 2);

    gaussian_filter(input_fifo, output_fifo_gf);
    sobel_filter(output_fifo_gf, output_fifo_sf);
    nonmaximum_suppression(output_fifo_sf, output_fifo_nm);
    hysteresis_filter(output_fifo_nm, output_fifo);
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

    printf("canny: -i %s -g %s -o %s\n", input_File_name, golden_File_name, output_File_name);

    unsigned int i, j;

    hls::FIFO< unsigned char > input_fifo(/* depth = */ WIDTH * HEIGHT * 2);
    hls::FIFO< unsigned char > output_fifo(/* depth = */ WIDTH * HEIGHT * 2);

    bmp_header_t input_channel_header, golden_output_image_header;
    bmp_pixel_t *input_channel_sw, *input_channel, *golden_output_image, *output_image, *output_image_ptr;

    unsigned int matching = 0;

    // read inputs from file
    input_channel = read_bmp(input_File_name, &input_channel_header);
    if (!input_channel) {
        printf("Error: read %s\n", input_File_name);
        return -1;
    }
    input_channel_sw = input_channel;

    golden_output_image = read_bmp(golden_File_name, &golden_output_image_header);
    if (!golden_output_image) {
        printf("Error: read %s\n", golden_File_name);
        return -1;
    }

    output_image = (bmp_pixel_t *)malloc(SIZE * sizeof(bmp_pixel_t));
    output_image_ptr = output_image;

    // convert image to grayscale and write to input array
    unsigned char(*input_image)[WIDTH] = new unsigned char[HEIGHT][WIDTH];
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            unsigned char r = input_channel_sw->r;
            unsigned char g = input_channel_sw->g;
            unsigned char b = input_channel_sw->b;
            unsigned grayscale = (r + g + b) / 3;
            input_image[i][j] = grayscale;
            input_channel_sw++;
        }
    }

    // run software model
    unsigned char(*gaussian_output)[WIDTH] = new unsigned char[HEIGHT][WIDTH];
    hls::ap_uint< 10 >(*sobel_output)[WIDTH] = new hls::ap_uint< 10 >[HEIGHT][WIDTH];
    unsigned char(*nonmaximum_suppression_output)[WIDTH] = new unsigned char[HEIGHT][WIDTH];
    unsigned char(*hysteresis_output_golden)[WIDTH] = new unsigned char[HEIGHT][WIDTH];
    gf_sw(input_image, gaussian_output);
    sf_sw(gaussian_output, sobel_output);
    nm_sw(sobel_output, nonmaximum_suppression_output);
    hf_sw(nonmaximum_suppression_output, hysteresis_output_golden);

    // Write input pixels.
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            unsigned char r = input_channel->r;
            unsigned char g = input_channel->g;
            unsigned char b = input_channel->b;
            unsigned grayscale = (r + g + b) / 3;
            input_fifo.write(grayscale);
            canny(input_fifo, output_fifo);
            input_channel++;
        }
    }

    // Give more inputs to flush out all pixels.
    for (i = 0; i < GF_KERNEL_SIZE * WIDTH + GF_KERNEL_SIZE; i++) {
        input_fifo.write(0);
        canny(input_fifo, output_fifo);
    }

    // output validation
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            unsigned char sw = hysteresis_output_golden[i][j];
            unsigned char gold = golden_output_image->r;
            assert(sw == gold);

            unsigned char hw = output_fifo.read();
            output_image_ptr->r = hw;
            output_image_ptr->g = hw;
            output_image_ptr->b = hw;

            if (sw != hw) {
                printf("ERROR: ");
                printf("i = %d j = %d sw = %d hw = %d\n", i, j, sw, hw);
            } else {
                matching++;
            }

            output_image_ptr++;
            golden_output_image++;
        }
    }

    printf("Result: %d\n", matching);
    bool result_incorrect = 0;
    if (matching == SIZE) {
        printf("RESULT: PASS\n");
    } else {
        printf("RESULT: FAIL\n");
        result_incorrect = 1;
    }

    write_bmp(output_File_name, &input_channel_header, output_image);
    return result_incorrect;
}
