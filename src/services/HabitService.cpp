#include "services/HabitService.hpp"

std::string HabitService::createHabit(const std::string &habit)
{
    if (habitRepo_.habitExists(habit))
    {
        //logMgr_.logError("Habit already exists: " + habit);
        return "error_habit_already_exists";
    }

    if (!habitRepo_.addHabit(habit))
    {
        //logMgr_.logError("Failed to add habit: " + habit);
        return "error_save_failed";
    }

    //logMgr_.logInfo("Habit created: " + habit);
    return "success";
}

std::string HabitService::updateHabit(const std::string &oldName, const std::string &newName)
{
    if (!habitRepo_.habitExists(oldName))
    {
        //logMgr_.logError("Habit not found: " + oldName);
        return "error_habit_not_found";
    }

    if (!habitRepo_.updateHabitName(oldName, newName))
    {
        //logMgr_.logError("Failed to update habit: " + oldName + " to " + newName);
        return "error_save_failed";
    }

    //logMgr_.logInfo("Habit updated: " + oldName + " -> " + newName);
    return "success";
}

std::string HabitService::deleteHabit(const std::string &habit)
{
    if (!habitRepo_.habitExists(habit))
    {
        //logMgr_.logError("Habit not found: " + habit);
        return "error_habit_not_found";
    }

    if (!habitRepo_.removeHabit(habit))
    {
        //logMgr_.logError("Failed to remove habit: " + habit);
        return "error_save_failed";
    }

    //logMgr_.logInfo("Habit removed: " + habit);
    return "success";
}

std::vector<std::string> HabitService::getAllHabits()
{
    return habitRepo_.getAllHabits();
}
