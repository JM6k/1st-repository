# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Target executable
TARGET = $(BUILD_DIR)/tictactoe

# Source files (will be added as we create them)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files to create executable
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean rebuild run
