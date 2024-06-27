#!/bin/bash

# Define your compiler (e.g., g++)
COMPILER="g++"

# Compiler options
COMPILER_OPTIONS="-std=c++20"

# List all your source files
SOURCE_FILES="game.cpp game_state.cpp randomBot.cpp main.cpp"

# Specify the output executable name
OUTPUT_EXECUTABLE="z_output_program"

# Compile the program
$COMPILER $COMPILER_OPTIONS -o $OUTPUT_EXECUTABLE $SOURCE_FILES

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running $OUTPUT_EXECUTABLE..."
    ./z_output_program  # Run the compiled program
else
    echo "Compilation failed."
fi
