#ifndef SHOW_HABITS_MENU_HPP
#define SHOW_HABITS_MENU_HPP

#include "menus/MenuNode.hpp"
#include "model/HabitListManager.hpp"
#include "utils/InputProcessor.hpp"
// ShowHabitsMenuクラスの責務
//  メニュー操作:
//      習慣リストの表示を担当する。
//      ユーザー入力を処理し、エラー検知を行う。
//  アクションの実行:
//      習慣リストの表示を実行する。
class ShowHabitsMenu : public MenuNode {
public:
    ShowHabitsMenu(
        HabitListManager& listManager, 
        const std::string& title,
        MessageManager& messageManager, 
        InputManager& inputManager, 
        OutputManager& outputManager)
            : listManager_(listManager),
            messageManager_(messageManager), 
            inputManager_(inputManager), 
            outputManager_(outputManager)
        {
            setTitle(title);
        }

    void execute() override {
        auto& common_ = CommonUtils::getInstance();
        common_.clearScreen(); 
        listManager_.showHabits();
        InputProcessor::waitForEnter(messageManager_);
        }

private:
    HabitListManager& listManager_;
    MessageManager& messageManager_;
    InputManager& inputManager_;
    OutputManager& outputManager_;
};

#endif // SHOW_HABITS_MENU_HPP