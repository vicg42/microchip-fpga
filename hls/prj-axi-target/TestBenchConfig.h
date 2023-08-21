#pragma once

#include <string>
#include <toml.hpp>

class TestBenchConfig {
   public:
    struct {
        size_t width;
        size_t height;
    } video;

    TestBenchConfig(std::string ConfigFile) {
        Read(ConfigFile);
    }
    ~TestBenchConfig() {
    }

   private:
    void Read(std::string ConfigFile) {
        auto data = toml::parse(ConfigFile);
        const auto &metaInfo = toml::find(data, "metaInfo");
        video.width = toml::find< int >(metaInfo, "width");
        video.height = toml::find< int >(metaInfo, "height");
    }
};
