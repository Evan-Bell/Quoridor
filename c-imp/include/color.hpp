// color.hpp

#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color {
public:
    static const std::string BLACK;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string ORANGE;
    static const std::string BLUE;
    static const std::string PINK;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string RESET;
    static const std::string BROWN;
    static const std::string BACKGROUND_YELLOW;
    
    // Additional Colors
    static const std::string LIGHT_RED;
    static const std::string LIGHT_GREEN;
    static const std::string LIGHT_YELLOW;
    static const std::string LIGHT_BLUE;
    static const std::string LIGHT_MAGENTA;
    static const std::string LIGHT_CYAN;
    static const std::string DARK_GRAY;
    static const std::string LIGHT_GRAY;
};

// Define the color constants
const std::string Color::BLACK = "\u001b[30m";
const std::string Color::RED = "\u001b[31m";
const std::string Color::GREEN = "\u001b[32m";
const std::string Color::YELLOW = "\u001b[33m";
const std::string Color::ORANGE = "\u001b[38;5;208m";
const std::string Color::BLUE = "\u001b[34m";
const std::string Color::PINK = "\u001b[35m";
const std::string Color::MAGENTA = "\u001b[35m";
const std::string Color::CYAN = "\u001b[36m";
const std::string Color::WHITE = "\u001b[37m";
const std::string Color::RESET = "\u001b[0m";
const std::string Color::BROWN = "\033[0;33m";
const std::string Color::BACKGROUND_YELLOW = "\u001b[43m";

// Additional Colors
const std::string Color::LIGHT_RED = "\u001b[91m";
const std::string Color::LIGHT_GREEN = "\u001b[92m";
const std::string Color::LIGHT_YELLOW = "\u001b[93m";
const std::string Color::LIGHT_BLUE = "\u001b[94m";
const std::string Color::LIGHT_MAGENTA = "\u001b[95m";
const std::string Color::LIGHT_CYAN = "\u001b[96m";
const std::string Color::DARK_GRAY = "\u001b[90m";
const std::string Color::LIGHT_GRAY = "\u001b[37;1m";


#endif // COLOR_H
