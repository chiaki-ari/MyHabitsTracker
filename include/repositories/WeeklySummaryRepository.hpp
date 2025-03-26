#pragma once
#include "repositories/IAppStorage.hpp"

using json = nlohmann::json;

class WeeklySummaryRepository
{
public:
    // コンストラクタ
    WeeklySummaryRepository(IAppStorage &storage)
        : storage_(storage)
    {
        // 必要なら load() 呼ぶ
        load();
    }
    bool load();
    bool save();

    // JSONを取得/設定するだけ
    void setWeeklyData(const nlohmann::json &weeklyData);
    void getWeeklyData(nlohmann::json &out) const;

private:
    IAppStorage &storage_;      // JSONManagerと同等の抽象ストレージ
    nlohmann::json weeklyData_; // { "weeks": [ ... ] }
};
