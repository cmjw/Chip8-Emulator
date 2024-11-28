# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -O2
LDFLAGS = -lSDL2 -L/usr/lib

SRC_DIR = src
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
TARGET = chip8_emulator

# Default rule
all: $(BUILD_DIR) $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Placeholder
run: $(TARGET)
	./$(TARGET) roms/pong.ch8 