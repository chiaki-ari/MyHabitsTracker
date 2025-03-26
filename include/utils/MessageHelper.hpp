#ifndef MESSAGE_HELPER_HPP
#define MESSAGE_HELPER_HPP

#include <string>
#include "output/OutputManager.hpp"
#include "model/LogManager.hpp"

class MessageHelper {
public:
    MessageHelper(OutputManager& outputMgr, LogManager& logMgr)
        : outputMgr_(outputMgr), logMgr_(logMgr) {}

    void printSuccessMessage(const std::string& message) {
        outputMgr_.print("✅ " + message);
        logMgr_.logInfo(message);
    }

    void printErrorMessage(const std::string& message) {
        outputMgr_.print("❌ " + message);
        logMgr_.logError(message);
    }

    void printInfoMessage(const std::string& message) {
        outputMgr_.print("ℹ️ " + message);
        logMgr_.logInfo(message);
    }

private:
    OutputManager& outputMgr_;
    LogManager& logMgr_;
};

#endif // MESSAGE_HELPER_HPP
