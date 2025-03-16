#ifndef JSON_MANAGER_HPP
#define JSON_MANAGER_HPP

#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class JSONManager {
public:
    explicit JSONManager(const std::string& file) 
    : filename_(file) {}
    //クラスのインスタンス作成時、filenameを引数fileで初期化

    static constexpr bool LOAD_SUCCESS = true;
    static constexpr bool LOAD_ERROR = false;
    
    static constexpr bool SAVE_SUCCESS = true;
    static constexpr bool SAVE_ERROR = false;

    bool load(json& data);
    bool save(const json& data);
private:
    std::string filename_;
    //MessageUtils& msgUtils_;
};

#endif // JSON_MANAGER_HPP
