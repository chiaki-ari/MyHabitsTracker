#include "model/JSONManager.hpp"
#include <iostream>

bool JSONManager::load(json& data){
    std::ifstream inFile(filename_);

    if(!inFile){
        std::cerr << "ERROR: '" << filename_ << "'' の読み込み失敗" <<std::endl;
        data = json::object(); //空のJSONオブジェクトを生成
        return LOAD_ERROR;
    }
    try {
        inFile >> data;
    } catch (json::parse_error& e){
        std::cerr << "ERROR: JSONパースエラー" << e.what() << std::endl;
        data = json::object();
        return LOAD_ERROR;
    }
        inFile.close();
        return LOAD_SUCCESS;
}

bool JSONManager::save(const json& data){
    std::ofstream outFile(filename_);
    if(!outFile){
        std::cerr << "ERROR: '" << filename_ << "'' の書き込み失敗" <<std::endl;
        return SAVE_ERROR;
    }
    try {
        outFile << data.dump(4);
    } catch (const std::exception& e) {
        std::cerr << "ERROR: JSON 書き込みエラー: " << e.what() << std::endl;
        return SAVE_ERROR;
    }
    outFile.close();
    return SAVE_SUCCESS;
}