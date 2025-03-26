#include "repositories/HabitRepository.hpp"

bool HabitRepository::load() { //TODO  いつload?
    json temp;
    if (!storage_.load(temp)) {
        // ファイルが無い or エラー
        // とりあえず空にしてreturn false
        habitsData_ = temp;
        return false;
    }
    habitsData_ = temp;
    return true;
}

bool HabitRepository::save() {
    // weeklyData_ を保存
    return storage_.save(habitsData_);
}

std::vector<std::string> HabitRepository::getAllHabits()
{
    std::vector<std::string> habits;
    for (const auto &habit : habitsData_["habits"])
    {
        habits.push_back(habit.get<std::string>());
    }
    return habits;
}

bool HabitRepository::habitExists(const std::string &habit)
{
    const auto &habitList = habitsData_["habits"];
    return std::find(habitList.begin(), habitList.end(), habit) != habitList.end();
}

bool HabitRepository::addHabit(const std::string &habit)
{
    habitsData_["habits"].push_back(habit);
    return save();
}

bool HabitRepository::updateHabitName(const std::string &oldName, const std::string &newName)
{
    auto &habitList = habitsData_["habits"];
    auto it = std::find(habitList.begin(), habitList.end(), oldName);
    if (it != habitList.end())
    {
        *it = newName;
        return save();
    }
    return false;
}

bool HabitRepository::removeHabit(const std::string &habit)
{
    auto &habitList = habitsData_["habits"];
    auto beforeSize = habitList.size();
    habitList.erase(std::remove(habitList.begin(), habitList.end(), habit), habitList.end());
    return (habitList.size() != beforeSize) && save();
}