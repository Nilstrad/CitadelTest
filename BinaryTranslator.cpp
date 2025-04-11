#include "BinaryTranslator.h"
#include <fstream>
#include <iostream>


void BinaryTranslator::set(const uint8_t* data, size_t size) {
    std::string filename;
    int counter = 0;

    for (size_t i = 0; i < size; i += kChunkMax) {
        filename = storage_path + "file" + std::to_string(counter) + ".bin";
        std::ofstream file(filename, std::ios::binary);

        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(data + i), std::min(kChunkMax, size - i));
            file.close();
            std::cout << "File created successfully: " << filename << std::endl;
        } else {
            std::cerr << "Unable to create file: " << filename << std::endl;
        }
        ++counter;
    }
}

void BinaryTranslator::get(size_t offset, size_t size, std::vector<uint8_t>& result) {
    result.clear();
    size_t bytes_read = 0;
    int counter = 0;

    while (offset > kChunkMax) {
        offset -= kChunkMax;
        ++counter;
    }

    std::string filename;

    while (bytes_read < size) {
        filename = storage_path + "file" + std::to_string(counter) + ".bin";
        std::ifstream file(filename, std::ios::binary);

        if (file.is_open()) {
            file.seekg(offset, std::ios::beg);
            size_t bytes_to_read = std::min(kChunkMax - offset, size - bytes_read);
            std::vector<uint8_t> buffer(bytes_to_read);

            file.read(reinterpret_cast<char*>(buffer.data()), bytes_to_read);
            size_t actually_read = file.gcount();

            result.insert(result.end(), buffer.begin(), buffer.begin() + actually_read);
            bytes_read += actually_read;

            file.close();
            std::cout << "File read successfully: " << filename << std::endl;
        } else {
            std::cerr << "Unable to read file: " << filename << std::endl;
            break;
        }

        offset = 0;
        ++counter;
    }
}
