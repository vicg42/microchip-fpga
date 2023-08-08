#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hls/streaming.hpp>

#include "parsingComLine.h"

void write(hls::FIFO< unsigned > *my_fifo, unsigned data) {
    // write to the fifo
    my_fifo->write(data);
}

void read_write(hls::FIFO< unsigned > *my_fifo, hls::FIFO< unsigned > *out_fifo) {
#pragma HLS function top
    // read from the fifo
    unsigned data = my_fifo->read();
    out_fifo->write(data);
}

int main(int argc, char *argv[]) {
    printf("Hello World!\n");

    ParsingComLine comLineArg(argc, argv);

    printf("FileI: %s\n", comLineArg.dirInFile_.c_str());
    printf("FileO: %s\n", comLineArg.dirOutFile_.c_str());

    hls::FIFO< unsigned > my_fifo;
    // set the fifo's depth to 10
    my_fifo.setDepth(10);

    // declare a 32-bit wide fifo with a depth of 10
    hls::FIFO< unsigned > my_fifo_depth_10(10);

    for (u_int8_t i = 0; i < 7; i++) {
        write(&my_fifo, 10 + i);
    }
    for (u_int8_t i = 0; i < 7; i++) {
        read_write(&my_fifo, &my_fifo_depth_10);
    }

    // check if my_fifo is empty - should be empty since we read from it in
    // read_write (is_empty = 1)
    bool is_empty = my_fifo.empty();

    // check if my_fifo_depth_10 is empty - should not be empty since we write
    // to it in read_write (is_empty = 0)
    bool is_second_empty = my_fifo_depth_10.empty();

    // We will use the fail variable to check for any failures. fail will become
    // 1 if is_empty != 1 and is_second_empty != 0
    int fail = (is_empty == 1) ? ((is_second_empty == 0) ? 0 : 1) : 1;
    // If fail is 1, test will fail.

    return fail;
}
