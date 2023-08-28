#include "utils.h"

int readImage(const char *filename, uint8_t *buf, struct video_st *param) {
    printf("filename: %s\n", filename);
    FILE *file =
        fopen("/home/v.halavachenka/work/vicg42-github/microchip-fpga/hls/image/toronto_100x56_16b_gray.raw", "rb");
    // FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error1: readImage\n");
        return -1;
    }

    if (fread(buf, sizeof(uint8_t), (param->size * param->bpp), file) != (param->size * param->bpp)) {
        printf("Error2: readImage\n");
        return -1;
    }
    for (int i = 0; i < 32; i++) {
        printf("buf[%d]:%d\n", i, buf[i]);
    }

    fclose(file);
    return 0;
}

void writeImage(const char *filename, uint8_t *buf, struct video_st *param) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error1: writeImage\n");
        return;
    }

    fwrite(buf, sizeof(uint8_t), (param->size * param->bpp), file);
    fclose(file);
}
