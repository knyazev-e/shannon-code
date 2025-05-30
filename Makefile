PROJECT_TARGET = shannon

CXX = g++
CXX_FLAGS = -std=c++17 -Wall -Wextra -O3

PROJECT_SOURCE = encoder.cpp decoder.cpp dictionary.cpp main.cpp
HEADERS = encoder.h decoder.h dictionary.h
PROJECT_OBJ = $(PROJECT_SOURCE:.cpp=.o)

all: $(PROJECT_TARGET)

$(PROJECT_TARGET): $(PROJECT_OBJ)
	$(CXX) $(C_FLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(PROJECT_TARGET) *.o encoded.bin decoded.bin codes

.PHONY: all clean
