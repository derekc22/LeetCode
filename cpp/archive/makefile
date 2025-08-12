CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2

SRC_EASY := $(wildcard easy/*.cpp)
SRC_MED := $(wildcard medium/*.cpp)
SRC_HARD := $(wildcard hard/*.cpp)
SRCS := $(SRC_EASY) $(SRC_MED) $(SRC_HARD)

BUILD_DIR := build
BINS := $(addprefix $(BUILD_DIR)/,$(basename $(notdir $(SRCS))))

.PHONY: all clean
all: clean $(BINS)

# Build executables directly, no .o files
$(BUILD_DIR)/%: easy/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%: medium/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%: hard/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
