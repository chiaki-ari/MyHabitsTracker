#ifndef UPDATE_RECORD_MENU_HPP
#define UPDATE_RECORD_MENU_HPP

#include "menus/MenuNode.hpp"
#include "model/HabitTracker.hpp"
// UpdateRecordMenuクラスの責務
//  メニュー操作:
//      習慣達成記録の操作を担当する。
//      ユーザー入力を処理し、エラー検知を行う。
//  アクションの実行:
//      習慣達成記録を更新したい日付の受付を行う
//      記録の更新を実行する。
class UpdateRecordMenu : public MenuNode {
public:
    UpdateRecordMenu(
        HabitTracker& tracker, 
        const std::string& title, 
        MessageManager& messageManager, 
        InputManager& inputManager, 
        OutputManager& outputManager);
    void execute() override;

private:
    HabitTracker& tracker_;
    std::string title_;
    MessageManager& messageManager_;
    InputManager& inputManager_;
    OutputManager& outputManager_;
};
#endif // UPDATE_RECORD_MENU_HPP