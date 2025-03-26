#ifndef BASE_MENU_HPP
#define BASE_MENU_HPP

#include "output/I18nManager.hpp"
#include "output/OutputManager.hpp"
#include "input/InputManager.hpp"
#include "menus/MenuNode.hpp"
enum class branchMenuType
{
    Main,
    Sub,
    SubSub,
    Setting
};
class BranchMenu : public MenuNode
{
public:
    BranchMenu(const std::string &title,
        branchMenuType mType,
               I18nManager &i18nMgr,
               InputManager &inputMgr,
               OutputManager &outputMgr)
        : MenuNode(title),
        menuType_(mType),
          i18nMgr_(i18nMgr),
          inputMgr_(inputMgr),
          outputMgr_(outputMgr)
    {
        setTitle(title);
    }

    MenuResult execute() override;

private:
    void displayMenu() const;
    std::pair<MenuResult, int> handleUserSelection();

    branchMenuType menuType_;
    I18nManager &i18nMgr_;
    InputManager &inputMgr_;
    OutputManager &outputMgr_;

protected:
    // 派生クラスが必要に応じてオーバーライドできるフックメソッド
    virtual void onBeforeLoop() {}
    virtual void onExitLoop() {}
    virtual void onAfterLoop() {}
    virtual void onBeforeChildExecute() {}
    // virtual void onBeforeChildExecute(int /*selected*/) {}
    // virtual void onAfterChildExecute(int /*selected*/) {}

    // 既存の displayMenu(), handleUserSelection() は共通処理
};

#endif // BASE_MENU_HPP