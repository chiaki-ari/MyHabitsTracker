#include "output/ConsoleOutput.hpp"

void ConsoleOutput::print(const std::string &message, bool newline)
{
    std::cout << message << (newline ? "\n" : "");
}

void ConsoleOutput::printError(const std::string &message)
{
    std::cout << "✗ "
              << message
              << std::endl;
}
void ConsoleOutput::printAlert(const std::string &message)
{
    std::cout << "!!! "
              << message
              << std::endl;
}
void ConsoleOutput::printComplete(const std::string &message)
{
    std::cout << "✔ "
              << message
              << std::endl;
}
void ConsoleOutput::printTitle(const std::string &message)
{
    std::cout << "==== "
              << message
              << " ===="
              << std::endl;
}
void ConsoleOutput::printSub2Title(const std::string &message)
{
    std::cout << "--- "
              << message
              << " ---"
              << std::endl;
}
void ConsoleOutput::printSubTitle(const std::string &message)
{
    std::cout << "~~~ "
              << message
              << " ~~~"
              << std::endl;
}
void ConsoleOutput::printLine()
{
    std::cout << "---------------"
              << std::endl;
}
void ConsoleOutput::printGuide(const std::string &message)
{
    std::cout << ">>> "
              << message
              << std::endl;
}
void ConsoleOutput::printInput(const std::string &message, bool isCancel)
{
    std::cout << "> " << message;
    if (isCancel)
        std::cout << " (Enter to cancel)";
    if (message != "")
        std::cout << " :";
}
void ConsoleOutput::printQuestion(const std::string &message)
{
    std::cout << "? "
              << message
              << "(y/n)? :";
}
void ConsoleOutput::printParameter(const std::string &message)
{
    std::cout << "{"
              << message
              << " }"
              << std::endl;
}
void ConsoleOutput::printStrong(const std::string &message)
{
    std::cout << "+++ "
              << message
              << " +++"
              << std::endl;
}
void ConsoleOutput::printStatus(const std::string &message)
{
    std::cout << "@@@ "
              << message
              << " @@@"
              << std::endl;
}
void ConsoleOutput::printSettingMenu(const std::string &message)
{
    std::cout << "::: "
              << message
              << " :::"
              << std::endl;
}

void ConsoleOutput::printBack(const std::string &message)
{
    std::cout << "<<< "
              << message
              << std::endl;
}
void ConsoleOutput::printProcessing(const std::string &message)
{
    std::cout << "--> "
              << message
              << std::endl;
}
void ConsoleOutput::printNewLine()
{
    std::cout << std::endl;
}
void ConsoleOutput::printListWithHeader(const std::string& header, const std::vector<std::string>& items)
{
    printSub2Title(header);
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::cout << " " << std::to_string(i + 1) << ". " << items[i] << std::endl;
    }
}