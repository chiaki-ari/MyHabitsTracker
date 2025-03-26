#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

#include <system_error>
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <filesystem>

#include "utils/DateUtils.hpp"

enum class LogLevel { DEBUG, INFO, WARNING, APP_ERROR };

class LogManager {
public:
    LogManager() {
    }

    void setLogLevel(LogLevel level) { logLevel_ = level; }
    //LogLevel::DEBUG: DEBUG、INFO、WARNING、ERROR のすべてのログを出力します。
    //LogLevel::INFO: INFO、WARNING、ERROR のログを出力します。
    //LogLevel::WARNING: WARNING、ERROR のログを出力します。
    //LogLevel::ERROR: ERROR のログのみを出力します。

    void logError(/*const std::error_code& ec, */const std::string& additionalMessage) {
        if (logLevel_ <= LogLevel::APP_ERROR) {
            std::lock_guard<std::mutex> lock(mutex_);
            std::ofstream file(logFile_, std::ios_base::app);
            std::string timestamp = DateUtils::getInstance().getCurrentTimestamp();
            std::string logMessage = "[" + timestamp + /*"] ERROR: Error Code: " + std::to_string(ec.value()) + " (" + ec.message() + "), Additional Info: " +*/ additionalMessage;
            file << logMessage << std::endl;
            std::cout << logMessage << std::endl;
        }
    }
    
    void logDebug(const std::string& message) {
        if (logLevel_ <= LogLevel::DEBUG) {
            std::lock_guard<std::mutex> lock(mutex_);
            std::ofstream file(logFile_, std::ios_base::app);
            std::string timestamp = DateUtils::getInstance().getCurrentTimestamp();
            std::string logMessage = "[" + timestamp + "] DEBUG: " + message;
            file << logMessage << std::endl;
            std::cout << logMessage << std::endl;
        }
    }

    void logInfo(const std::string& message) {
        if (logLevel_ <= LogLevel::INFO) {
            std::lock_guard<std::mutex> lock(mutex_);
            std::ofstream file(logFile_, std::ios_base::app);
            std::string timestamp = DateUtils::getInstance().getCurrentTimestamp();
            std::string logMessage = "[" + timestamp + "] INFO: " + message;
            file << logMessage << std::endl;
            std::cout << logMessage << std::endl;
        }
    }

    
    void logWarning(const std::string& message) {
        if (logLevel_ <= LogLevel::WARNING) {
            std::lock_guard<std::mutex> lock(mutex_);
            std::ofstream file(logFile_, std::ios_base::app);
            std::string timestamp = DateUtils::getInstance().getCurrentTimestamp();
            std::string logMessage = "[" + timestamp + "] WARNING: " + message;
            file << logMessage << std::endl;
            std::cout << logMessage << std::endl;
        }
    }

    void createLogFileIfNotExists() {
        std::string basePath = "log/";
        try {
            // フォルダの作成を試みる
            if (!std::filesystem::exists(basePath)) {
                std::filesystem::create_directory(basePath);
            }
            logFile_ = basePath + "application.log";
            if (!std::filesystem::exists(logFile_)) {
                std::ofstream file(logFile_);
                file << "Log file created.\n";
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            // エラー処理をここに追加
        }
    }
private:

    std::string logFile_;
    LogLevel logLevel_ = LogLevel::INFO;
    std::mutex mutex_;
};

#endif // LOG_MANAGER_HPP