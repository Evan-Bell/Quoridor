// color.hpp

#ifndef COLOR_H
#define COLOR_H

#include <string>

// Define the color constants
const std::string Color_BLACK = "\u001b[30m";
const std::string Color_RED = "\u001b[31m";
const std::string Color_GREEN = "\u001b[32m";
const std::string Color_YELLOW = "\u001b[33m";
const std::string Color_ORANGE = "\u001b[38;5;208m";
const std::string Color_BLUE = "\u001b[34m";
const std::string Color_PINK = "\u001b[35m";
const std::string Color_MAGENTA = "\u001b[35m";
const std::string Color_CYAN = "\u001b[36m";
const std::string Color_WHITE = "\u001b[37m";
const std::string Color_RESET = "\u001b[0m";
const std::string Color_BROWN = "\033[0;33m";
const std::string Color_BACKGROUND_YELLOW = "\u001b[43m";

// Additional Colors
const std::string Color_LIGHT_RED = "\u001b[91m";
const std::string Color_LIGHT_GREEN = "\u001b[92m";
const std::string Color_LIGHT_YELLOW = "\u001b[93m";
const std::string Color_LIGHT_BLUE = "\u001b[94m";
const std::string Color_LIGHT_MAGENTA = "\u001b[95m";
const std::string Color_LIGHT_CYAN = "\u001b[96m";
const std::string Color_DARK_GRAY = "\u001b[90m";
const std::string Color_LIGHT_GRAY = "\u001b[37;1m";


#endif // COLOR_H
