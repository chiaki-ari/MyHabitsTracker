#include "AppController.hpp"
#include "input/ConsoleInput.hpp"
#include "output/ConsoleOutput.hpp"
#include "utils/CommonUtils.hpp"

// 言語選択の入力を取得する関数
std::string selectLanguage(InputManager& inputManager) {
    auto& common_ = CommonUtils::getInstance();
    common_.setConsole();    
    std::cout << "Please select a language (e: English, j: Japanese)\n言語を選択してください (e: 英語, j: 日本語)\n> ";
    while (true) {
        auto input = inputManager.getStringInput();
        if (input.has_value() && (input.value() == "e" || input.value() == "j")) {
            return input.value() == "e" ? "en" : "ja";
        }
        std::cout << "⚠️ Please enter 'e' for English or 'j' for Japanese\n'e' または 'j' を入力してください\n> ";
    }
}

int main() {
    ConsoleInput consoleInput;
    InputManager inputManager(consoleInput);

    std::string lang = selectLanguage(inputManager);

    MessageManager messageManager(lang);
    ConsoleOutput consoleOutput;
    OutputManager outputManager(consoleOutput);
    
    AppController app("data/habits.json", "data/records.json", messageManager, inputManager, outputManager);
    app.run();

    return 0;
}
