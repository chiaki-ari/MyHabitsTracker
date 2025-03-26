#ifndef OUTPUT_INTERFACE_HPP
#define OUTPUT_INTERFACE_HPP

#include <string>
#include <vector>
class OutputInterface
{
public:
    virtual void print(const std::string &message, bool newline = true) = 0; 
    // virtual void printFormattedMessage1(const std::string &templateStr, const std::string &param1) = 0;
    // virtual void printFormattedMessage2(const std::string &templateStr, const std::string &param1, int param2) = 0;
    virtual void printError(const std::string &message) = 0;
    virtual void printAlert(const std::string &message) = 0;
    virtual void printComplete(const std::string &message) = 0;
    virtual void printTitle(const std::string &message) = 0;
    virtual void printSub2Title(const std::string &message) = 0;
    virtual void printSubTitle(const std::string &message) = 0;
    virtual void printLine() = 0;
    virtual void printGuide(const std::string &message) = 0;
    virtual void printInput(const std::string &message, bool isCancel) = 0;
    virtual void printQuestion(const std::string &message) = 0;
    virtual void printParameter(const std::string &message) = 0;
    virtual void printStatus(const std::string &message) = 0;
    virtual void printSettingMenu(const std::string &message) = 0;
    virtual void printBack(const std::string &message) = 0;
    virtual void printProcessing(const std::string &message) = 0;
    virtual void printStrong(const std::string &message) = 0;
    virtual void printListWithHeader(const std::string& header, const std::vector<std::string>& items) = 0;
    virtual void printNewLine() = 0;
    virtual ~OutputInterface() = default;
};

#endif // OUTPUT_INTERFACE_HPP
