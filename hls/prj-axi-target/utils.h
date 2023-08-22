#ifndef __UTILS__
#define __UTILS__

#include <inttypes.h>
#include <stdio.h>

struct video_st {
    uint16_t width;
    uint16_t height;
    uint8_t bpp;      // byte per pixel
    uint32_t size;    // total image size
    uint16_t nframe;  // number of frame
};

int readImage(const char *filename, uint8_t *buf, struct video_st *param);
void writeImage(const char *filename, uint8_t *buf, struct video_st *param);

#endif  //__UTILS__