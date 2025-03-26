#ifndef HABIT_SERVICE_HPP
#define HABIT_SERVICE_HPP

#include <string>
#include <vector>
#include "repositories/HabitRepository.hpp"
#include "model/LogManager.hpp"

class HabitService
{
public:
    HabitService(HabitRepository &habitRepo, LogManager &logMgr)
        : habitRepo_(habitRepo), logMgr_(logMgr) {}

    std::string createHabit(const std::string &habit);
    std::string updateHabit(const std::string &oldName, const std::string &newName);
    std::string deleteHabit(const std::string &habit);
    std::vector<std::string> getAllHabits();

private:
    HabitRepository &habitRepo_;
    LogManager &logMgr_;
};

#endif // HABIT_SERVICE_HPP
