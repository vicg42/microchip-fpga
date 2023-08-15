#pragma once
#include "BlockBase.h"

class ReadFileData : public BlockBase {
   public:
    void Init();
    void SetValue(std::string param, const size_t value);
    // void SetValue(std::string param, const bool value);
    // void SetValue(std::string param, const std::string value);
    void ReadRawFile(std::string fileName);

    ReadFileData(std::string name, const std::vector< size_t >& framesNum) : BlockBase(name) {
        framesNum_ = framesNum;
    }

    ~ReadFileData() {
    }

   private:
    int random(int min, int max);
    std::vector< size_t > framesNum_;
    size_t width_;
    size_t height_;
    size_t interLine_ = 0;
    size_t interFrame_;
    size_t interPixEn_ = 0;
    size_t interPixEnRand_ = 0;
    size_t interPixEnRandMax_ = 0;
};
