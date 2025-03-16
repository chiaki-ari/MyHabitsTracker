#include "output/OutputManager.hpp"

OutputManager::OutputManager(OutputInterface& outputInterface) : outputInterface_(outputInterface) {}

void OutputManager::print(const std::string& message, bool newline) {
    outputInterface_.print(message, newline);
}
