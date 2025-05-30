#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <bitset>
#include <cmath>

#ifndef ENCODER_H
#define ENCODER_H

void encode(std::string input_path, std::string output_path, std::string dict_path);

std::unordered_map<char, std::string> shannon_code(std::string filename);

#endif
