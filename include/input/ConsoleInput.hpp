#ifndef CONSOLE_INPUT_HPP
#define CONSOLE_INPUT_HPP

#include "input/InputInterface.hpp"
#include <iostream>

class ConsoleInput : public InputInterface {
public:
    std::optional<std::string> getStringInput() override;
};

#endif // CONSOLE_INPUT_HPP
