#ifndef SHOW_RECORD_MENU_HPP
#define SHOW_RECORD_MENU_HPP

#include "menus/MenuNode.hpp"
#include "model/HabitTracker.hpp"
#include "utils/InputProcessor.hpp"
// ShowRecordMenuクラスの責務
//  メニュー操作:
//      習慣達成記録の表示を担当する。
//      ユーザー入力を処理し、エラー検知を行う。
//  アクションの実行:
//      習慣達成記録の表示したい期間の入力を受け付ける。
//      記録の表示を実行する。
class ShowRecordMenu : public MenuNode {
public:
    ShowRecordMenu(
        HabitTracker& tracker, 
        const std::string& title, 
        std::function<void(HabitTracker&)> action,
        MessageManager& messageManager, 
        InputManager& inputManager, 
        OutputManager& outputManager)
            : tracker_(tracker), 
            title_(title), 
            action_(action), 
            messageManager_(messageManager), 
            inputManager_(inputManager), 
            outputManager_(outputManager)
    {
        setTitle(title);
    }

    void execute() override{
        // 受け取った表示ロジックを実行
        auto& common_ = CommonUtils::getInstance();
        common_.clearScreen(); 
        action_(tracker_);
        InputProcessor::waitForEnter(messageManager_);
    }

private:
    HabitTracker& tracker_;
    std::string title_;
    std::function<void(HabitTracker&)> action_;
    MessageManager& messageManager_;
    InputManager& inputManager_;
    OutputManager& outputManager_;
};

#endif // SHOW_RECORD_MENU_HPP