#include "output/OutputManager.hpp"

OutputManager::OutputManager(OutputInterface& outputInterface) : outputInterface_(outputInterface) {}

void OutputManager::print(const std::string& message, bool newline) {
    outputInterface_.print(message, newline);
}
void OutputManager::printError(const std::string& message) {
    outputInterface_.printError(message);
}
void OutputManager::printAlert(const std::string& message) {
    outputInterface_.printAlert(message);
}
void OutputManager::printComplete(const std::string& message) {
    outputInterface_.printComplete(message);
}
void OutputManager::printTitle(const std::string& message) {
    outputInterface_.printTitle(message);
}
void OutputManager::printSub2Title(const std::string& message) {
    outputInterface_.printSub2Title(message);
}
void OutputManager::printSubTitle(const std::string& message) {
    outputInterface_.printSubTitle(message);
}
void OutputManager::printStrong(const std::string& message) {
    outputInterface_.printStrong(message);
}
void OutputManager::printLine() {
    outputInterface_.printLine();
}
void OutputManager::printGuide(const std::string& message) {
    outputInterface_.printGuide(message);
}
void OutputManager::printInput(const std::string& message, bool isCancel) {
    outputInterface_.printInput(message, isCancel);
}
void OutputManager::printQuestion(const std::string& message) {
    outputInterface_.printQuestion(message);
}
void OutputManager::printParameter(const std::string& message) {
    outputInterface_.printParameter(message);
}
void OutputManager::printStatus(const std::string& message) {
    outputInterface_.printStatus(message);
}
void OutputManager::printSettingMenu(const std::string& message) {
    outputInterface_.printSettingMenu(message);
}
void OutputManager::printBack(const std::string& message) {
    outputInterface_.printBack(message);
}
void OutputManager::printProcessing(const std::string& message) {
    outputInterface_.printProcessing(message);
}
void OutputManager::printNewLine() {
    outputInterface_.printNewLine();
}

void OutputManager::printListWithHeader(const std::string& header, const std::vector<std::string>& items)
{
    outputInterface_.printListWithHeader(header, items);
}
// void OutputManager::printFormattedMessage1(const std::string& templateStr, const std::string& param1) {
//     printFormattedMessage1(templateStr, param1);
// }

// void OutputManager::printFormattedMessage2(const std::string& templateStr, const std::string& param1, int param2) {
//     printFormattedMessage2(templateStr, param1, param2);
// }