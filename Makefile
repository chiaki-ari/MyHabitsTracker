# Compiler and Flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -g \
    -Iinclude \
    -Iinclude/menus \
    -Iinclude/model \
    -Iinclude/utils \
    -Iinclude/core \
    -Iinclude/input \
    -Iinclude/output \
    -Iinclude/message

# Build Directories
BUILD_DIR := build
BUILD_SUBDIRS := $(BUILD_DIR) $(BUILD_DIR)/menus $(BUILD_DIR)/model $(BUILD_DIR)/utils $(BUILD_DIR)/core $(BUILD_DIR)/input $(BUILD_DIR)/output $(BUILD_DIR)/message
SRC_DIRS := src src/menus src/model src/utils src/core src/input src/output src/message
TARGET := tracker.exe

# Source and Object Files
SRCS := $(wildcard $(foreach d,$(SRC_DIRS),$(d)/*.cpp))
OBJS := $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Ensure all directories exist before compilation
$(shell mkdir $(BUILD_DIR) 2> NUL)
$(shell mkdir $(BUILD_DIR)/menus 2> NUL)
$(shell mkdir $(BUILD_DIR)/model 2> NUL)
$(shell mkdir $(BUILD_DIR)/utils 2> NUL)
$(shell mkdir $(BUILD_DIR)/input 2> NUL)
$(shell mkdir $(BUILD_DIR)/output 2> NUL)
$(shell mkdir $(BUILD_DIR)/message 2> NUL)

# Linking
$(TARGET): $(OBJS)
	@echo "🔨 Linking..."
	@$(CXX) $(CXXFLAGS) -o $@ $^

# Object File Compilation
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/menus/%.o: src/menus/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/model/%.o: src/model/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utils/%.o: src/utils/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/core/%.o: src/core/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/input/%.o: src/input/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/output/%.o: src/output/%.cpp | $(BUILD_SUBDIRS)
	@echo "🔧 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/message/%.o: src/message/%.cpp | $(BUILD_SUBDIRS)
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
