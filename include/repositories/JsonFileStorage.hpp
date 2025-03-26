#pragma once
#include "repositories/IAppStorage.hpp"
#include "model/JSONManager.hpp"

class JsonFileStorage : public IAppStorage {
public:
    explicit JsonFileStorage(const std::string& filename)
        : jsonManager_(filename)
    {
    }

    bool load(nlohmann::json &data) override {
        return jsonManager_.load(data);
    }

    bool save(const nlohmann::json &data) override {
        return jsonManager_.save(data);
    }

private:
    JSONManager jsonManager_;
};
