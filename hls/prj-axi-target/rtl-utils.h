#ifndef __RTL_UTILS__
#define __RTL_UTILS__

#include <inttypes.h>
#include <stdio.h>

#define WIDTH 1000
#define HEIGHT 56

bool is_filled(unsigned int kernel_size, unsigned int count);
bool is_out_of_bounds(unsigned int kernel_size, unsigned int i, unsigned int j);
void update_image_position(unsigned int &i, unsigned int &j);

#endif  //__RTL_UTILS__