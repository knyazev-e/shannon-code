#include "decoder.h"

void decode(std::string input_path, std::string output_path, std::string dict_path) {
    Dictionary dict;
    dict.getfromfile(dict_path);

    std::ifstream input(input_path, std::ios::binary);
    std::string contents;
    char byte;
    while (input.read(&byte, 1)) {
        contents += std::bitset<8>(byte).to_string();
    }

    std::string code;
    std::ofstream output(output_path, std::ios::binary);

    for (char bit : contents) {
        code += bit;
        if (dict.code_to_char.count(code)) {
            output << dict.decode(code);
            code.clear();
        }
    }
}
