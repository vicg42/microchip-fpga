#include "ReadFileData.h"

#include <fstream>

void ReadFileData::Init() {
}

void ReadFileData::SetValue(std::string param, const size_t value) {
    if (param == "width") {
        width_ = value;
    } else if (param == "height") {
        height_ = value;
    } else if (param == "interLine") {
        interLine_ = value;
    } else if (param == "interFrame") {
        interFrame_ = value;
    }
}

int ReadFileData::random(int min, int max)  // range : [min, max]
{
    static bool first = true;
    if (first) {
        srand(time(NULL));  // seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void ReadFileData::ReadRawFile(std::string fileName) {
    std::ifstream inputFile(fileName, std::ios::binary | std::ios::in);
    uint8_t bytes_data[2];

    auto frameNum = (framesNum_[1] - framesNum_[0]) + 1;

    inputFile.seekg((height_ * width_ * 2) * framesNum_[0]);

    for (size_t j = 0; j < frameNum; j++) {
        if (inputFile.peek() == EOF) {
            break;
        }
        for (size_t y = 0; y < height_; y++) {
            for (size_t x = 0; x < width_; x++) {
                size_t PixEn = 0;
                if (interPixEnRand_ == 1) {
                    PixEn = random(interPixEn_, interPixEnRandMax_);
                } else {
                    PixEn = interPixEn_;
                }
                for (size_t n = 0; n < PixEn + 1; n++) {
                    if (n == PixEn) {
                        inputFile.read((char*)bytes_data, 2);
                    }
                }
            }
            printf("line[%d]\n", (int)y);
        }
    }

    inputFile.seekg(0);
}