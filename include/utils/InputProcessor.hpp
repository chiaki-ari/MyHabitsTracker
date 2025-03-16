#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include <string>
#include <iostream>
#include <limits>
#include "message/MessageManager.hpp"
#include "input/InputManager.hpp"

//静的メソッドのみのユーティリティクラス
class InputProcessor {
    public:
        static bool shouldReturnToMenu(
            const std::string& input, 
            const std::string& message);

        static void waitForEnter(
            MessageManager& messageManager);

        static bool validateAndGetIndex(
            const std::string& input, 
            int minValue, 
            int maxValue, 
            const std::string& errorMessage, 
            MessageManager& messageManager);
    };
    
#endif // INPUT_PROCESSOR_HPP
    