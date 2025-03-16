#include "InputProcessor.hpp"
#include <format>

bool InputProcessor::shouldReturnToMenu(
    const std::string& input, 
    const std::string& message) 
{
    if (input == "x") {
        std::cout << message << std::endl;
        return true;
    }
    return false;
}

void InputProcessor::waitForEnter(
    MessageManager& messageManager) 
{
    std::cout << messageManager.getMessage("wait_for_enter");
    if (std::cin.rdbuf()->in_avail() > 0) {
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.get();
}

bool InputProcessor::validateAndGetIndex(
    const std::string& input, 
    int minValue, 
    int maxValue, 
    const std::string& errorMessage, 
    MessageManager& messageManager) 
{
    int index;
    try {
        index = std::stoi(input);
    } catch (...) {
        std::string templateStr = messageManager.getMessage("alert_prompt");
        std::string result = std::vformat(
            templateStr, 
            std::make_format_args(errorMessage));
        std::cout << result << std::endl;
        //return -1;
        return false;
    }

    if (index < minValue || index > maxValue) {
        std::string templateStr = messageManager.getMessage("alert_prompt");
        std::string errorMsg = messageManager.getMessage("error_invalid_number");
        std::string result = std::vformat(
            templateStr, 
            std::make_format_args(errorMsg));
        std::cout << result << std::endl;
        return false;
    }

    return true;
}
