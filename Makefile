PROJECT_TARGET = shannon
TEST_TARGET = tests

CXX = g++
CXX_FLAGS = -std=c++17 -Wall -Wextra -O3
TEST_FLAGS = -lgtest -lgtest_main -lpthread

HEADERS = encoder.h decoder.h dictionary.h

GENERAL_SOURCES = encoder.cpp decoder.cpp dictionary.cpp
PROJECT_SOURCES = $(GENERAL_SOURCES) main.cpp
TEST_SOURCES = $(GENERAL_SOURCES) test.cpp

PROJECT_OBJ = $(PROJECT_SOURCES:.cpp=.o)
TEST_OBJ = $(TEST_SOURCES:.cpp=.o)

all: $(PROJECT_TARGET) $(TEST_TARGET)

$(PROJECT_TARGET): $(PROJECT_OBJ)
	$(CXX) $(C_FLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_FLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(PROJECT_TARGET) $(TEST_TARGET) *.o encoded.bin decoded.bin test_source.bin codes

.PHONY: all clean
