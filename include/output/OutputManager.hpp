#ifndef OUTPUT_MANAGER_HPP
#define OUTPUT_MANAGER_HPP

#include "output/OutputInterface.hpp"

class OutputManager
{
public:
    OutputManager(OutputInterface &outputInterface);
    void print(const std::string &message, bool = true);
    void printError(const std::string& message);
    void printAlert(const std::string& message);
    void printComplete(const std::string& message);
    void printTitle(const std::string& message);
    void printSub2Title(const std::string& message);
    void printSubTitle(const std::string& message);
    void printLine();
    void printGuide(const std::string& message);
    void printInput(const std::string& message, bool isCancel);
    void printQuestion(const std::string& message);
    void printParameter(const std::string& message);
    void printStatus(const std::string& message);
    void printSettingMenu(const std::string& message);
    void printBack(const std::string& message);
    void printProcessing(const std::string& message);
    void printStrong(const std::string& message);
    void printListWithHeader(const std::string& header, const std::vector<std::string>& items);
    void printNewLine();
    // void printFormattedMessage1(const std::string& templateStr, const std::string& param1);
    // void printFormattedMessage2(const std::string& templateStr, const std::string& param1, int param2);
private:
    OutputInterface &outputInterface_;
};

#endif // OUTPUT_MANAGER_HPP
