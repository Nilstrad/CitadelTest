#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

class BinaryTranslator {
private:
    std::string storage_path = "C:/Users/artam/Desktop/Test/TLP/";
    static constexpr size_t kChunkMax = 20;

public:
    void set(const uint8_t* data, size_t size);
    void get(size_t offset, size_t size, std::vector<uint8_t>& result);
};
