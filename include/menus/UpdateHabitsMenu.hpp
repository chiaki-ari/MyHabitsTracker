#ifndef UPDATE_HABITS_MENU_HPP
#define UPDATE_HABITS_MENU_HPP

#include "menus/MenuNode.hpp"
#include "model/HabitListManager.hpp"
#include <functional>
#include <format>
// UpdateHabitsMenuクラスの責務
//  メニュー操作:
//      習慣管理メニューの表示と操作を担当する。
//      ユーザー入力を処理し、エラー検知を行う。
//  アクションの実行:
//      習慣リストの操作（追加、編集、削除）を実行する。

class UpdateHabitsMenu : public MenuNode
{
public:
    UpdateHabitsMenu(
        HabitListManager &listManager,
        const std::string &title,
        std::function<void(HabitListManager &)> action,
        MessageManager &messageManager,
        InputManager &inputManager,
        OutputManager &outputManager)
        : listManager_(listManager),
        title_(title),
          action_(action),
          messageManager_(messageManager),
          inputManager_(inputManager),
          outputManager_(outputManager)
    {
        setTitle(title);
    }
    void execute() override
    {
        auto &common_ = CommonUtils::getInstance();
        common_.clearScreen();
        std::string templateStr = messageManager_.getMessage("title_bar");
        std::string result = std::vformat(templateStr, std::make_format_args(title_));
        outputManager_.print(result);
        action_(listManager_);
        InputProcessor::waitForEnter(messageManager_);
    }

private:
    HabitListManager &listManager_;
    std::string title_;
    std::function<void(HabitListManager &)> action_;
    MessageManager &messageManager_;
    InputManager &inputManager_;
    OutputManager &outputManager_;
};
#endif // UPDATE_HABITS_MENU_HPP