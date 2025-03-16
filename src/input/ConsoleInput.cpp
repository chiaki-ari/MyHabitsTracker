#include "input/ConsoleInput.hpp"

std::optional<std::string> ConsoleInput::getStringInput() {
    if (std::cin.peek() == '\n') { 
        std::cin.ignore();
    }
    std::string input;
    std::getline(std::cin, input);
    
    if (input.empty()) { 
        return std::nullopt; 
    } else {
        return input; 
    }
}
