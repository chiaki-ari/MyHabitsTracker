#include "input/InputManager.hpp"

InputManager::InputManager(InputInterface& inputInterface)
    : inputInterface_(inputInterface) {}

std::optional<std::string> InputManager::getStringInput() {
    return inputInterface_.getStringInput();
}
