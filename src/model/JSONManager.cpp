#include "model/JSONManager.hpp"
#include <fstream>
#include <iostream>

bool JSONManager::load(json &data) {
    // ファイルを開く
    std::ifstream inFile(filename_);
    
    if (!inFile) {
        // ファイルが開けなかった場合のエラーハンドリング
        std::cerr << "ERROR: Failed to load file '" << filename_ << "'" << std::endl;
        data = json::object();  // 空のオブジェクトを返す
        return LOAD_ERROR;
    }

    try {
        // JSONデータをパースする
        data = json::parse(inFile);
    } catch (json::parse_error &e) {
        // JSONパースエラーの場合のエラーハンドリング
        std::cerr << "ERROR: JSON parsing error - " << e.what() << std::endl;
        return LOAD_ERROR;
    }

    // ファイルを閉じる
    inFile.close();
    return LOAD_SUCCESS;
}

bool JSONManager::save(const json &data) {
    // ファイルを開く
    std::ofstream outFile(filename_);
    
    if (!outFile) {
        // ファイルが開けなかった場合のエラーハンドリング
        std::cerr << "ERROR: Failed to write to file '" << filename_ << "'" << std::endl;
        return SAVE_ERROR;
    }

    // JSONデータをファイルに書き込む
    outFile << data.dump(4);
    outFile.close();
    return SAVE_SUCCESS;
}
