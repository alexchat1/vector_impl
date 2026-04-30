CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++23 -Iincludes
DEBUG_FLAGS := -g -O0

SRC_DIR := src
INCLUDE_DIR := includes

# Main target
main: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Vector.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Test target
tests: $(SRC_DIR)/tests.cpp $(INCLUDE_DIR)/Vector.h
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $< -o $@

clean:
	rm -f main tests

rebuild: clean all

all: main test

.PHONY: all clean rebuild test