#pragma once
#include "json.hpp"

class IAppStorage {
public:
    virtual ~IAppStorage() = default;

    // JSONのロード・セーブだけ抽象化
    virtual bool load(nlohmann::json &data) = 0;
    virtual bool save(const nlohmann::json &data) = 0;
};
