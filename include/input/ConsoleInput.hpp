#ifndef CONSOLE_INPUT_HPP
#define CONSOLE_INPUT_HPP

#include "input/InputInterface.hpp"
#include <iostream>
#include <locale>
#include <codecvt>

class ConsoleInput : public InputInterface 
{
public:
    std::optional<std::string> getStringInput() override;
private:
    std::string shiftJisToUtf8(const std::string& sjisStr);
};

#endif // CONSOLE_INPUT_HPP
