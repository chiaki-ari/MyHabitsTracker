#pragma once
#include "repositories/IAppStorage.hpp"

// モデル層 or ドメインロジック層
// 習慣リスト(habitsData_) の読み書き・永続化管理(JSONManagerを利用)
// 習慣の追加・編集・削除CRUD(ビジネスロジック)
// 習慣リストの提供 ( getAllHabits())

using json = nlohmann::json;

class HabitRepository
{
public:
    explicit HabitRepository(IAppStorage &storage)
        : storage_(storage)
    {
        load();
    }


    bool load();
    bool save();
    std::vector<std::string> getAllHabits();
    bool habitExists(const std::string &habit);
    bool addHabit(const std::string &habit);
    bool updateHabitName(const std::string &oldName, const std::string &newName);
    bool removeHabit(const std::string &habit);

private:
    IAppStorage &storage_; 
    json habitsData_;
};
