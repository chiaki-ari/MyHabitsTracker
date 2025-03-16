#ifndef HABIT_LIST_MANAGER_HPP
#define HABIT_LIST_MANAGER_HPP

#include "model/JSONManager.hpp"
#include "message/MessageManager.hpp"
#include "input/InputManager.hpp"
#include "output/OutputManager.hpp"

// HabitListManagerクラスの責務
//  データ管理:
//      習慣リストのデータを管理し、保存・読み込みを行う。
//      習慣の追加、編集、削除を行う。
//  データ提供:
//      習慣リストを提供し、他のクラスが利用できるようにする。

class HabitListManager {
public:
    explicit HabitListManager(
        const std::string& filename, 
        MessageManager& messageManager, 
        InputManager& inputManager, 
        OutputManager& outputManager);
    
    std::vector<std::string> getHabitsList();
    void showHabits();
    void addHabit();
    void editHabit();
    void removeHabit();

private:
    JSONManager jsonManager_;
    json dataRecords_;
    MessageManager& messageManager_;
    InputManager& inputManager_;
    OutputManager& outputManager_;
    
    void renameHabitInData(const std::string& oldName, const std::string& newName);
};

#endif // HABIT_LIST_MANAGER_HPP
