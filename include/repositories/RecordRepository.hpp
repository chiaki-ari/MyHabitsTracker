#pragma once
#include "repositories/IAppStorage.hpp"

// データの管理・保存・取得
//  RecordManageクラスの責務
//   データ管理:
//       習慣達成記録のデータを管理し、保存・読み込みを行う。
//  データ提供:
//       習慣達成記録を提供し、他のクラスが利用できるようにする。

using json = nlohmann::json;

class RecordRepository
{
public:
    explicit RecordRepository(IAppStorage &storage)
    : storage_(storage)
    {
        load();
    }

    bool load();
    bool save();

    // CRUD操作
    std::string updateRecord(const std::string &day,const std::string &habit, bool achieved);
    std::string getRecordsByDate(const std::string& day, nlohmann::json &habitsData);
    std::string getAllRecords(nlohmann::json &records);

private:
    IAppStorage &storage_;
    json recordData_;
};