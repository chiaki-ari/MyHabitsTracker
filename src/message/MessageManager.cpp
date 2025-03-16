#include "message/MessageManager.hpp"
#include "model/JSONManager.hpp"
#include <iostream>

MessageManager::MessageManager(const std::string& lang) {
    language_ = lang;
    std::string filename = "data/messages_" + lang + ".json";

    JSONManager jsonManager(filename);
    if (!jsonManager.load(messagesData_)) {
        std::cerr << "⚠️ Failed to load language file / 言語ファイルの読み込みに失敗しました: " << filename << std::endl;
    }
}

std::string MessageManager::getMessage(const std::string& key) const {
    if (messagesData_.contains(key)) {
        return messagesData_[key];
    }
    return "⚠️ [" + key + "] Undefined / 未定義";
}