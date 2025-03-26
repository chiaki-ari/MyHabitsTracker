#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "input/InputInterface.hpp"

class InputManager
{
public:
    InputManager(InputInterface &inputInterface);
    std::optional<std::string> getStringInput();

private:
    InputInterface &inputInterface_;
};

#endif // INPUT_MANAGER_HPP
