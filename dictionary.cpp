#include "dictionary.h"

Dictionary::Dictionary(std::unordered_map<char, std::string> dict): char_to_code(dict) {
    for (const auto& p : dict) {
        code_to_char[p.second] = p.first;
    }
}

void Dictionary::savetofile(std::string filename) {
    std::ofstream file(filename);
    for (const auto& p : char_to_code) {
        file << static_cast<int>(static_cast<unsigned char>(p.first)) << "," << p.second << "\n";
    }
    file.close();
}

void Dictionary::getfromfile(std::string filename) {
    char_to_code.clear();
    code_to_char.clear();

    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        size_t comma_pos = line.find(',');
        if (comma_pos == std::string::npos) continue;

        char c = static_cast<char>(std::stoi(line.substr(0, comma_pos)));
        std::string code = line.substr(comma_pos + 1);
        char_to_code[c] = code;
        code_to_char[code] = c;
    }
    file.close();
}

char Dictionary::decode(std::string code) {
    return code_to_char[code];
}

std::string Dictionary::encode(char c) {
    return char_to_code[c];
}
