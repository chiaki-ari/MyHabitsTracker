#ifndef CONSOLE_OUTPUT_HPP
#define CONSOLE_OUTPUT_HPP

#include "output/OutputInterface.hpp"
#include <iostream>

class ConsoleOutput : public OutputInterface {
public:
    void print(const std::string& message, bool newline) override;
};

#endif // CONSOLE_OUTPUT_HPP
