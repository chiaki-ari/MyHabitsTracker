#include "output/ConsoleOutput.hpp"

void ConsoleOutput::print(const std::string& message, bool newline) {
    if (newline) {
        std::cout << message << std::endl;
    } else {
        std::cout << message;
    }
}
