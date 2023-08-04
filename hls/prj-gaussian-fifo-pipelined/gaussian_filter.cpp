#include "hls/ap_int.hpp"
#include "hls/streaming.hpp"
#include "hls/image_processing.hpp"

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

bool is_filled(unsigned int kernel_size, unsigned int count)
{
    unsigned int center = kernel_size / 2;
    return count > (center * WIDTH + center - 1);
}

bool is_out_of_bounds(unsigned int kernel_size, unsigned int i, unsigned int j)
{
    unsigned int center = kernel_size / 2;
    return (i < center) | (i > (HEIGHT - center - 1)) | (j < center) |
           (j > (WIDTH - center - 1));
}

void update_image_position(int &i, int &j)
{
    if (j < WIDTH - 1)
    {
        // increment column
        j++;
    }
    else if (i == HEIGHT - 1 && j == WIDTH - 1)
    {
        // end of the image frame
        i = 0;
        j = 0;
    }
    else
    {
        // increment row
        i++;
        j = 0;
    }
}

void gaussian_filter_pipelined(hls::ap_uint<1> on_switch,
                               hls::FIFO<unsigned char> &input_fifo,
                               hls::FIFO<unsigned char> &output_fifo)
{
#pragma HLS function top
#pragma HLS function pipeline

    if (input_fifo.empty())
        return;

    unsigned char input_pixel = input_fifo.read();

    static hls::LineBuffer<unsigned char, WIDTH, KERNEL_SIZE> line_buffer;

    line_buffer.ShiftInPixel(input_pixel);

    // keep track of how many pixels we have shifted into the line_buffer to
    // tell when it is filled
    static unsigned int count = 0;
    if (!is_filled(KERNEL_SIZE, count))
    {
        count++;
        return;
    }

    // i, j to track the position we are at while processing each input frame
    static int i = 0, j = 0;

    // calculate if the kernel is currently out of bounds, i.e. the kernel
    // overlaps with pixels outside of the current input frame
    bool outofbounds = is_out_of_bounds(KERNEL_SIZE, i, j);

    // update i, j for next iteration
    update_image_position(i, j);

    if (!on_switch || outofbounds)
    {
        unsigned int center = KERNEL_SIZE / 2;
        unsigned char current_pixel = line_buffer.window[center][center];
        output_fifo.write(current_pixel);
        return;
    }

    unsigned int sum = 0;
    for (unsigned int m = 0; m < KERNEL_SIZE; m++)
    {
        for (unsigned int n = 0; n < KERNEL_SIZE; n++)
        {
            sum += ((unsigned int)line_buffer.window[m][n]) * GAUSSIAN[m][n];
        }
    }

    int output = sum / DIVISOR;

    output_fifo.write(output);
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

    printf("gsussian-fifo: -i %s -g %s -o %s\n", input_File_name, golden_File_name, output_File_name);
    unsigned int i, j;
    unsigned int matching = 0;

    hls::FIFO<unsigned char> input_fifo(/* depth = */ WIDTH * HEIGHT * 2);
    hls::FIFO<unsigned char> output_fifo(/* depth = */ WIDTH * HEIGHT * 2);
    hls::ap_uint<1> on = 1;

    bmp_header_t input_channel_header, golden_output_image_header;
    bmp_pixel_t *input_channel, *golden_output_image,
        *output_image, *output_image_ptr;

    // read inputs from file
    input_channel = read_bmp(input_File_name, &input_channel_header);
    if (!input_channel)
        return 1;

    golden_output_image = read_bmp(golden_File_name, &golden_output_image_header);
    if (!golden_output_image)
        return 1;

    output_image = (bmp_pixel_t *)malloc(SIZE * sizeof(bmp_pixel_t));
    output_image_ptr = output_image;

    // input
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            unsigned char r = input_channel->r;
            unsigned char g = input_channel->g;
            unsigned char b = input_channel->b;
            unsigned grayscale = (r + g + b) / 3;
            input_fifo.write(grayscale);
            // run design
            gaussian_filter_pipelined(on, input_fifo, output_fifo);
            input_channel++;
        }
    }

    // Give more inputs to flush out all pixels.
    for (i = 0; i < KERNEL_SIZE * WIDTH + KERNEL_SIZE; i++)
    {
        input_fifo.write(0);
        gaussian_filter_pipelined(on, input_fifo, output_fifo);
    }

    // output validation
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            unsigned char gold = golden_output_image->r;
            unsigned char hw = output_fifo.read();
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
