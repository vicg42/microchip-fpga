#include "hls/ap_int.hpp"
#include "hls/streaming.hpp"

#include "define.hpp"
#include "bmp.hpp"
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

const unsigned int KERNEL_SIZE = 5;

// A Simpler Gaussian Filter for hardware (the divisor is a power of 2)
const unsigned int GAUSSIAN[KERNEL_SIZE][KERNEL_SIZE] = {{1, 3, 4, 3, 1},
                                                         {3, 8, 10, 8, 3},
                                                         {4, 10, 12, 10, 4},
                                                         {3, 8, 10, 8, 3},
                                                         {1, 3, 4, 3, 1}};
const unsigned int DIVISOR = 128;

bool is_out_of_bounds(unsigned int kernel_size, unsigned int i,
                      unsigned int j)
{
    unsigned int center = kernel_size / 2;
    return (i < center) | (i > (HEIGHT - center - 1)) | (j < center) |
           (j > (WIDTH - center - 1));
}

// Gaussian Filter.
void gaussian_filter_memory_pipelined(hls::ap_uint<1> on,
                                      unsigned char input_buffer[][WIDTH],
                                      unsigned char output_buffer[][WIDTH])
{
#pragma HLS function top
#pragma HLS interface argument(output_buffer) type(memory) num_elements(SIZE)
#pragma HLS interface argument(input_buffer) type(memory) num_elements(SIZE)

    int center = KERNEL_SIZE / 2;

#pragma HLS loop pipeline
    for (int i = 0; i < (HEIGHT * WIDTH); i++)
    {
        unsigned int pos_i = i / WIDTH;
        unsigned int pos_j = i % WIDTH;
        bool out_of_bounds = is_out_of_bounds(KERNEL_SIZE, pos_i, pos_j);

        if (!on || out_of_bounds)
        {
            output_buffer[pos_i][pos_j] = input_buffer[pos_i][pos_j];
            continue;
        }

        unsigned int sum = 0;
        for (unsigned int m = 0; m < KERNEL_SIZE; m++)
        {
            for (unsigned int n = 0; n < KERNEL_SIZE; n++)
            {
                sum += ((unsigned int)input_buffer[pos_i + m - center]
                                                  [pos_j + n - center]) *
                       GAUSSIAN[m][n];
            }
        }

        sum /= DIVISOR;

        output_buffer[pos_i][pos_j] = (unsigned char)sum;
    }
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

    printf("gaussian-mem-if-pipelined: -i %s -g %s -o %s\n", input_File_name, golden_File_name, output_File_name);

    unsigned int i, j;
    unsigned int matching = 0;

    hls::FIFO<unsigned char> output_fifo(/* depth = */ WIDTH * HEIGHT * 2);
    hls::ap_uint<1> on = 1;

    bmp_header_t input_channel_header, golden_output_image_header;
    bmp_pixel_t *input_channel_sw, *input_channel, *golden_output_image,
        *output_image, *output_image_ptr;

    // read inputs from file
    input_channel = read_bmp(input_File_name, &input_channel_header);
    if (!input_channel)
        return 1;
    input_channel_sw = input_channel;

    golden_output_image = read_bmp(golden_File_name, &golden_output_image_header);
    if (!golden_output_image)
        return 1;

    output_image = (bmp_pixel_t *)malloc(SIZE * sizeof(bmp_pixel_t));
    output_image_ptr = output_image;

    // convert image to grayscale and write to input array
    unsigned char(*input_image)[WIDTH] = new unsigned char[HEIGHT][WIDTH];
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            unsigned char r = input_channel_sw->r;
            unsigned char g = input_channel_sw->g;
            unsigned char b = input_channel_sw->b;
            unsigned grayscale = (r + g + b) / 3;
            input_image[i][j] = grayscale;
            input_channel_sw++;
        }
    }

    // run design
    unsigned char(*output_image_gaussian)[WIDTH] =
        new unsigned char[HEIGHT][WIDTH];
    gaussian_filter_memory_pipelined(on, input_image, output_image_gaussian);

    // output validation
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            unsigned char gold = golden_output_image->r;
            unsigned char hw = output_image_gaussian[i][j];
            output_image_ptr->r = hw;
            output_image_ptr->g = hw;
            output_image_ptr->b = hw;

            if (hw != gold)
            {
                printf("ERROR: ");
                printf("i = %d j = %d gold = %d hw = %d\n", i, j, gold, hw);
            }
            else
            {
                matching++;
            }

            output_image_ptr++;
            golden_output_image++;
        }
    }

    printf("Result: %d\n", matching);
    bool result_incorrect = 0;
    if (matching == SIZE)
    {
        printf("RESULT: PASS\n");
    }
    else
    {
        printf("RESULT: FAIL\n");
        result_incorrect = 1;
    }

    write_bmp(output_File_name, &input_channel_header, output_image);
    return result_incorrect;
}
