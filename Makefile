# Compiler and Flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -lstdc++fs -finput-charset=UTF-8 -g \
    -Iinclude \
    -Iinclude/utils \
    -Iinclude/input \
    -Iinclude/output \
    -Iinclude/core \
    -Iinclude/model \
    -Iinclude/repositories \
    -Iinclude/menus \
    -Iinclude/controllers

# Build Directories
BUILD_DIR := build
SRC_DIRS := src/utils src/input src/output src/core src/model src/repositories src/menus src/services src/controllers src

# Source and Object Files
SRCS := $(wildcard $(foreach d,$(SRC_DIRS),$(d)/*.cpp))
OBJS := $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Ensure all directories exist before compilation
BUILD_SUBDIRS := $(foreach d,$(SRC_DIRS),$(BUILD_DIR)/$(notdir $(d)))
$(shell mkdir $(BUILD_DIR) 2> NUL)
$(foreach d,$(BUILD_SUBDIRS),$(shell mkdir $(d) 2> NUL))

# Linking
TARGET := tracker.exe
$(TARGET): $(OBJS)
	@echo "🔨 Linking..."
	@$(CXX) $(CXXFLAGS) -o $@ $^

# Object File Compilation
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure build directories exist before compiling
$(BUILD_SUBDIRS):
	@if not exist "$@" mkdir "$@"

# Clean Up
.PHONY: clean
clean:
	@echo "🧹 Cleaning up..."
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@if exist "$(TARGET)" del /F "$(TARGET)"
