# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/include/SDL2
LDFLAGS = -lSDL2

# Source files and output
SRC_DIR = src
SOURCES = $(SRC_DIR)/chip8.cpp $(SRC_DIR)/op.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/chip8video.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = chip8_emulator

# Default target
all: $(EXECUTABLE)

# Link the final executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile each source file into an object file
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean