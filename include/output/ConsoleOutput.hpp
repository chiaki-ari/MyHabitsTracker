#ifndef CONSOLE_OUTPUT_HPP
#define CONSOLE_OUTPUT_HPP

#include "output/OutputInterface.hpp"
#include <iostream>
#include <format>
class ConsoleOutput : public OutputInterface
{
public:
    void print(const std::string &message, bool newline) override;
    void printError(const std::string &message) override;
    void printAlert(const std::string &message) override;
    void printComplete(const std::string &message) override;
    void printTitle(const std::string &message) override;
    void printSub2Title(const std::string &message) override;
    void printSubTitle(const std::string &message) override;
    void printLine() override;
    void printGuide(const std::string &message) override;
    void printInput(const std::string &message, bool isCancel) override;
    void printQuestion(const std::string &message) override;
    void printParameter(const std::string &message) override;
    void printStatus(const std::string &message) override;
    void printSettingMenu(const std::string &message) override;
    void printBack(const std::string &message) override;
    void printProcessing(const std::string &message) override;
    void printStrong(const std::string &message) override;
    void printListWithHeader(const std::string& header, const std::vector<std::string>& items) override;
    void printNewLine() override;
    // void printFormattedMessage1(const std::string &templateStr, const std::string &param1) override;
    // void printFormattedMessage2(const std::string &templateStr, const std::string &param1, int param2) override;
};

#endif // CONSOLE_OUTPUT_HPP
