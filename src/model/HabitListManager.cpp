#include <format>
#include "utils/InputProcessor.hpp"
#include "model/HabitListManager.hpp"
// HabitListManagerクラスの責務
// データ管理:
// 習慣リストのデータを管理し、保存・読み込みを行う。
// 習慣の追加、編集、削除を行う。
// データ提供:
// 習慣リストを提供し、他のクラスが利用できるようにする。
HabitListManager::HabitListManager(
    const std::string& filename, 
    MessageManager& messageManager, 
    InputManager& inputManager, 
    OutputManager& outputManager)
        : jsonManager_(filename), 
        messageManager_(messageManager), 
        inputManager_(inputManager), 
        outputManager_(outputManager) 
{
        jsonManager_.load(dataRecords_);
}

std::vector<std::string> HabitListManager::getHabitsList() {
    std::vector<std::string> habitList;
    if (!dataRecords_.contains("habits") || !dataRecords_["habits"].is_array()) {
        return habitList; // 空のリストを返す
    }
    
    for (const auto& habit : dataRecords_["habits"]) {
        habitList.push_back(habit.get<std::string>());
    }
    
    return habitList;
}

void HabitListManager::showHabits() {
    std::string templateStr = messageManager_.getMessage("title_bar");
    std::string title = messageManager_.getMessage("habits_list_title");
    std::string result = std::vformat(templateStr, std::make_format_args(title));
    outputManager_.print(result);
    
    for (const auto& habit : dataRecords_["habits"]) {
        outputManager_.print(
            messageManager_.getMessage("bullet_points") + habit.get<std::string>());
    }
}

void HabitListManager::addHabit() {
    std::string habit = inputManager_.getStringInput().value_or("");
    if (habit.empty()) {
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string errorMsg = messageManager_.getMessage("prompt_cancel");
        std::string result = std::vformat(templateStr, std::make_format_args(errorMsg));
        outputManager_.print(result);
        return;
    }
    
    dataRecords_["habits"].push_back(habit);
    jsonManager_.save(dataRecords_);
    
    std::string templateStr = messageManager_.getMessage("add_habit_complete");
    std::string result = std::vformat(templateStr, std::make_format_args(habit));
    outputManager_.print(result);
}

void HabitListManager::editHabit() {
    std::string oldName = inputManager_.getStringInput().value_or("");
    if (oldName.empty()) {
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string errorMsg = messageManager_.getMessage("prompt_cancel");
        std::string result = std::vformat(templateStr, std::make_format_args(errorMsg));
        outputManager_.print(result);
        return;
    }
    
    std::string newName = inputManager_.getStringInput().value_or("");
    if (newName.empty()) {
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string errorMsg = messageManager_.getMessage("prompt_cancel");
        std::string result = std::vformat(templateStr, std::make_format_args(errorMsg));
        outputManager_.print(result);
        return;
    }
    
    auto& arr = dataRecords_["habits"];
    auto it = std::find(arr.begin(), arr.end(), oldName);
    if (it != arr.end()) {
        arr.erase(it);
        arr.push_back(newName);
        jsonManager_.save(dataRecords_);
        
        renameHabitInData(oldName, newName);
        
        std::string templateStr = messageManager_.getMessage("edit_habit_complete");
        std::string result = std::vformat(templateStr, std::make_format_args(oldName, newName));
        outputManager_.print(result);
    } else {
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string errorMsg = messageManager_.getMessage("error_invalid_habit_input");
        std::string result = std::vformat(templateStr, std::make_format_args(oldName, errorMsg));
        outputManager_.print(result);
        return;
    }
}

void HabitListManager::removeHabit() {
    std::string habit = inputManager_.getStringInput().value_or("");
    if (habit.empty()) {
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string errorMsg = messageManager_.getMessage("prompt_cancel");
        std::string result = std::vformat(templateStr, std::make_format_args(errorMsg));
        outputManager_.print(result);
        return;
    }
    
    auto& habitList = dataRecords_["habits"];
    habitList.erase(std::remove(habitList.begin(), habitList.end(), habit), habitList.end());
    jsonManager_.save(dataRecords_);
    
    std::string templateStr = messageManager_.getMessage("remove_habit_complete");
    std::string result = std::vformat(templateStr, std::make_format_args(habit));
    outputManager_.print(result);
}

void HabitListManager::renameHabitInData(const std::string& oldName, const std::string& newName) {
    for (auto& [day, habitObj] : dataRecords_.items()) {
        if (habitObj.is_object() && habitObj.contains(oldName)) {
            // rename
            habitObj[newName] = habitObj[oldName];
            habitObj.erase(oldName);
        }
    }
}
