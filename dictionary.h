#include <utility>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary {
public:
    Dictionary(std::unordered_map<char, std::string> dict);
    Dictionary() = default;

    std::string encode(char c);
    char decode(std::string code);
    void savetofile(std::string filename);
    void getfromfile(std::string filename);

private:
    std::unordered_map<char, std::string> char_to_code;
    std::unordered_map<std::string, char> code_to_char;
};

#endif
