#include "encoder.h"
#include "decoder.h"
#include "dictionary.h"
#include <iostream>

int main() {
    encode("source.bin", "encoded.bin", "codes");
    std::cout << "encoding passed" << std::endl;

    decode("encoded.bin", "decoded.bin", "codes");
    std::cout << "decoding passed too" << std::endl;
}
