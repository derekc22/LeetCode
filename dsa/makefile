CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2

SRC_ALGOS := $(wildcard algorithms/*.cpp)
SRC_DS := $(wildcard data-structures/*.cpp)
SRCS := $(SRC_ALGOS) $(SRC_DS)

BUILD_DIR := build
BINS := $(addprefix $(BUILD_DIR)/,$(basename $(notdir $(SRCS))))

.PHONY: all clean
all: $(BINS)

# Build executables directly, no .o files
$(BUILD_DIR)/%: algorithms/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%: data-structures/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
