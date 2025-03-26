#include "InputProcessor.hpp"
#include <format>
#include <conio.h>  // Windows環境で _getch() 使用

bool InputProcessor::shouldReturnToMenu(const std::string &input,
                                        const std::string &message)
{
    if (input == "x")
    {
        std::cout << message << std::endl;
        return true;
    }
    return false;
}

bool InputProcessor::shouldReturnToSwitchUser(const std::string &input)
{
    if (input == "s")
    {
        return true;
    }
    return false;
}
void InputProcessor::waitForEnter(I18nManager &i18nMgr)
{
    std::cout << i18nMgr.getText("wait_for_enter");
    if (std::cin.rdbuf()->in_avail() > 0)
    {
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.get();
}

bool InputProcessor::validateAndGetIndex(const std::string &input,
                                         int minValue,
                                         int maxValue)
{
    int index;
    try
    {
        index = std::stoi(input);
    }
    catch (...)
    {
        // return -1;
        return false;
    }

    if (index < minValue || index > maxValue)
    {
        return false;
    }

    return true;
}
InputProcessor::KeyType InputProcessor::getKeyInput()
{
    // まずは「何かキーが押されるまで待つ」
    // ※非ブロッキングにしたい場合は _kbhit() なども組み合わせる

    int c = _getch(); // 1文字取得

    // まず通常文字(ASCII)か、拡張キー(0, 0xE0) かを判別
    if (c == 0 || c == 0xE0)
    {
        // 矢印キーなどの「拡張キー」コードが続く
        c = _getch();
        switch (c)
        {
        case 72: // 上矢印
            return KeyType::ArrowUp;
        case 75: // 左矢印
            return KeyType::ArrowLeft;
        case 77: // 右矢印
            return KeyType::ArrowRight;
        case 80: // 下矢印
            return KeyType::ArrowDown;
        default:
            // それ以外の拡張キーは、とりあえず Other として扱う
            return KeyType::Other;
        }
    }
    else
    {
        // ASCII文字の場合
        if (c == 27) // ESCキー
        {
            return KeyType::Esc;
        }
        else if (c == 13)
        {
            // Enterキーなども捕捉したければここで返す (例: KeyType::Enter)
            return KeyType::Other;
        }
        else
        {
            // もしスペースや通常文字だったら Other 扱い
            // 「空欄」というのはコンソール上では通常存在しないため
            // 行バッファリングのように何も入力しないままEnterすると空文字列になるが
            // _getch() ではそもそも Enter キー押下が即座に 13 (CR) を返すため
            // 「何も押されていない」状態は取りづらい
            return KeyType::Other;
        }
    }
}