#pragma once

#include <cstdint>

#define BUF_COUNT_MAX 1024

// #define BPP 16  // Byte per pixel
// #define NumPixels 512
// #define AxiInitiatorWordWidth 64  // AXI memory is 64-bit
// #define BUF_COUNT ((NumPixels * BPP) / AxiInitiatorWordWidth)

#define BPP 16  // Byte per pixel
#define NumPixels (256)
#define PPC 1
#define NumPixelWords (NumPixels / PPC)
#define PixelWordWidth (BPP * PPC)  // Image is 8UC1
#define AxiWordWidth 64             // AXI memory is 64-bit
#define BUF_COUNT (NumPixelWords * PixelWordWidth / AxiWordWidth)

struct AxiRegs_st {
    uint16_t ctrl1;
    uint16_t ctrl2;
    uint16_t bypass;
    uint16_t status;
};
