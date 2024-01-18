CXX = g++
CXXFLAGS = -std=c++20 -Wall
SRC_DIR = console
BUILD_DIR = build
EXECUTABLE = z_output

# Get a list of all .cpp files in the source directory
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

# Create a list of corresponding .o files in the build directory
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# The default target is the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile individual .cpp files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Clean up all generated files
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# Phony targets (targets that don't represent files)
.PHONY: all clean

# The "all" target builds the executable
all: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
