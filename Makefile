TEST_TARGET = tests
PROJECT_TARGET = shannon

CXX = g++
C_FLAGS = -std=c++17
L_FLAGS = -lgtest -lgtest_main -lpthread

PROJECT_SOURCE = encoder.cpp decoder.cpp dictionary.cpp main.cpp
TEST_SOURCE = encoder.cpp decoder.cpp dictionary.cpp test.cpp
PROJECT_OBJ = $(PROJECT_SOURCE:.cpp=.o)
TEST_OBJ = $(TEST_SOURCE:.cpp=.o)

all: $(PROJECT_TARGET) $(TEST_TARGET)

$(PROJECT_TARGET): $(PROJECT_OBJ)
	$(CXX) $(C_FLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(C_FLAGS) -o $@ $^ $(L_FLAGS)

%.o: %.cpp
	$(CXX) $(C_FLAGS) -c $< -o $@


clean:
	rm -f $(PROJECT_TARGET) $(TEST_TARGET) *.o

test: $(TEST_TARGET)
	./$(TEST_TARGET)


.PHONY: all clean test
