#include "BinaryTranslator.h"
#include <iostream>
#include <iomanip>

int main() {
    BinaryTranslator translator;

    uint8_t data[50];
    for (int i = 0; i < 50; ++i) {
        data[i] = i;
    }

    translator.set(data, 50);

    std::vector<uint8_t> result;
    translator.get(30, 10, result);

    for (uint8_t byte : result) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }

    std::cout << std::dec << std::endl;

    return 0;
}
