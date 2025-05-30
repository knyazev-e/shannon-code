#include "encoder.h"
#include "dictionary.h"

void encode(std::string input_path, std::string output_path, std::string dict_path) {
    // reading the contents
    std::ifstream input_file(input_path, std::ios::binary);
    std::vector<char> contents;
    char c;
    while (input_file.read(&c, 1)) {
        contents.push_back(c);
    }
    input_file.close();

    // generating dictionary
    Dictionary dictionary(shannon_code(input_path));

    // encoding
    std::string encoded_contents;
    for (char c : contents) {
        encoded_contents += dictionary.encode(c);
    }

    std::vector<char> encoded_bin;
    for (size_t i = 0; i < encoded_contents.size(); i += 8) {
        std::string byte = encoded_contents.substr(i, 8);
        if (byte.size() < 8) {
            byte.append(8 - byte.size(), '0');
        }
        encoded_bin.push_back(static_cast<char>(std::bitset<8>(byte).to_ulong()));
    }

    // output
    std::ofstream output_file(output_path, std::ios::binary);
    output_file.write(encoded_bin.data(), encoded_bin.size());
    output_file.close();

    dictionary.savetofile(dict_path);
}

std::unordered_map<char, std::string> shannon_code(std::string filename) {
    // opening the file and count each character's frequency
    std::ifstream input_file(filename, std::ios::binary);

    std::vector<int> frequencies(256, 0);
    int total_symbols = 0;
    char symbol;
    while (input_file.read(&symbol, 1)) {
        frequencies[symbol]++;
        total_symbols++;
    }

    input_file.close();

    // making a vector of character-frequency pairs and sorting it to descending order
    std::vector<std::pair<char, int>> char_freq;
    for (int i = 0; i < 256; ++i) {
        if (frequencies[i] != 0) {
            std::pair<char, int> p(static_cast<char>(i), frequencies[i]);
            char_freq.push_back(p);
        }
    }

    std::sort(char_freq.begin(), char_freq.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // creating a dictionary
    double cumulative_probability = 0.0;
    std::unordered_map<char, std::string> dictionary;

    for (std::pair<char, int>& p : char_freq) {
        double probability = static_cast<double>(p.second) / total_symbols;
        int length = static_cast<int>(std::ceil(-std::log2(probability)));

        std::string code;
        double prob_copy = cumulative_probability;
        for (int i = 0; i < length; ++i) {
            prob_copy *= 2;
            int bit = static_cast<int>(prob_copy);
            code += std::to_string(bit);
            prob_copy -= bit;
        }
        dictionary[p.first] = code;
        cumulative_probability += probability;
    }

    return dictionary;
}
