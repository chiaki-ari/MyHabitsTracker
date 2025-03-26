#include "controllers/AppController.hpp"
#include "input/ConsoleInput.hpp"
#include "output/ConsoleOutput.hpp"
#include "utils/CommonUtils.hpp"


// グローバル変数の定義
bool g_debugMode = false;

// コマンドライン引数の処理関数
void parseCommandLineArguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--debug") {
            g_debugMode = true;
            std::cout << "Debug mode is ON." << std::endl;
            break;
        }
    }
}

// 言語選択の入力を取得する関数
std::string selectLanguage(InputManager& inputMgr) {
    auto& common_ = CommonUtils::getInstance();
    common_.setConsole();   

    std::cout << "Please select a language (e: English, j: 日本語) :";
    while (true) {
        auto input = inputMgr.getStringInput();
        if (input.has_value() && (input.value() == "e" || input.value() == "j")) {
            return input.value() == "e" ? "en" : "ja";
        }
        std::cout << "⚠️ Please enter 'e' for English or 'j' for Japanese\n'e' または 'j' を入力してください\n> ";
    }
}

int main(int argc, char* argv[]) {
    parseCommandLineArguments(argc, argv);
    ConsoleInput consoleInput;
    InputManager inputMgr(consoleInput);

    std::string lang = selectLanguage(inputMgr);

    LogManager logMgr;
    //DEBUGレベル以下のログがすべて出力
    logMgr.createLogFileIfNotExists();
    logMgr.setLogLevel(LogLevel::DEBUG);
    // logMgr.logInfo("Application started.");

    I18nManager i18nMgr(lang);
    ConsoleOutput consoleOutput;
    OutputManager outputMgr(consoleOutput);
    
    AppController app(i18nMgr, inputMgr, outputMgr, logMgr);
    app.initialize();
    app.run();

    return 0;
}
