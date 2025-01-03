
# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17 -I./include -I/usr/include/SDL2

# SDL2 libraries
CLIBS = -lSDL2 -lSDL2_ttf -lSDL2_image

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Project name
STATIC_LIB = gui.a

# Find all source files in SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Convert source files to object files in BUILD_DIR
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
.PHONY: all
all: $(STATIC_LIB)

# Building the static library
$(STATIC_LIB): $(OBJS)
	ar rcs $@ $^

# Compiling source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning up
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(STATIC_LIB) $(TARGET).o

# Rebuild the project
.PHONY: rebuild
rebuild: clean all

