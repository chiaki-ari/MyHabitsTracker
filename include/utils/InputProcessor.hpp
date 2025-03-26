#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include <string>
#include <iostream>
#include <limits>
#include "output/I18nManager.hpp"
#include "input/InputManager.hpp"

// 静的メソッドのみのユーティリティクラス
class InputProcessor
{

public:
    enum class KeyType
    {
        Empty, // 入力が空
        ArrowLeft,
        ArrowRight,
        ArrowUp,
        ArrowDown,
        Esc,
        Other // 上記以外の何か(Enterや通常文字など)
    };
    static bool shouldReturnToMenu(const std::string &input, const std::string &message);
    static bool shouldReturnToSwitchUser(const std::string &input);

    static void waitForEnter(I18nManager &i18nMgr);
    static bool validateAndGetIndex(const std::string &input, int minValue, int maxValue);
    KeyType getKeyInput();
};

#endif // INPUT_PROCESSOR_HPP
