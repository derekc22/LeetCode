CXX := g++
CXXFLAGS := -std=c++20 -Wall -O2 -Wno-comment

FILE := $(file) # pass with make file=filename.cpp
SRC := $(FILE)

BUILD_DIR := build
BIN := $(BUILD_DIR)/$(notdir $(FILE:.cpp=))

.PHONY: all clean
all: clean $(BIN)

$(BIN): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)