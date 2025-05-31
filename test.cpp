#include <gtest/gtest.h>
#include "encoder.h"
#include "decoder.h"
#include "dictionary.h"
#include <random>

TEST(ShannonTests, Test) {
    std::ofstream test_file("test_source.bin");
    std::string test_string = "These are the contents of the test file.";
    for (char c : test_string) {
        test_file << c;
    }
    test_file.close();

    encode("test_source.bin", "encoded.bin", "codes");
    decode("encoded.bin", "decoded.bin", "codes");

    std::ifstream source("test_source.bin");
    std::ifstream decoded("decoded.bin");

    std::string source_content((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
    std::string decoded_content((std::istreambuf_iterator<char>(decoded)), std::istreambuf_iterator<char>());

    EXPECT_EQ(source_content, decoded_content);
}


TEST(ShannonTests, RandomTest) {
    std::ofstream test_file("test_source.bin");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<char> dist(0, 127);
    for (int i = 0; i < 300; ++i) {
        test_file << dist(gen);
    }
    test_file.close();

    encode("test_source.bin", "encoded.bin", "codes");
    decode("encoded.bin", "decoded.bin", "codes");

    std::ifstream source("test_source.bin");
    std::ifstream decoded("decoded.bin");

    std::string source_content((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
    std::string decoded_content((std::istreambuf_iterator<char>(decoded)), std::istreambuf_iterator<char>());

    EXPECT_EQ(source_content, decoded_content);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
