#pragma once
#include "menus/MenuNode.hpp"
#include "output/I18nManager.hpp"
#include "output/OutputManager.hpp"
#include "utils/CommonUtils.hpp"
#include "utils/InputProcessor.hpp"
#include <functional>
#include <format>
enum class leafMenuType
{
    Setting,
    View,
    Update
};
template <typename Controller>
class LeafMenu : public MenuNode
{
public:
    LeafMenu(Controller &ctrl,
             const std::string &title,
             leafMenuType mType,
             std::function<void(Controller &)> action,
             I18nManager &i18nMgr,
             OutputManager &outputMgr)
        : MenuNode(title),
          menuType_(mType),
          ctrl_(ctrl),
          action_(action),
          i18nMgr_(i18nMgr),
          outputMgr_(outputMgr)
    {
    }

    MenuResult execute() override
    {
        // 単発の動作を行い、戻る(＝上位に返る)
        onBeforeCallBack();
        action_(ctrl_);
        onAfterCallBack();
        return MenuResult::OK; // TODO
    }

private:
    leafMenuType menuType_;
    Controller &ctrl_;
    // std::string title_;
    std::function<void(Controller &)> action_; 
    I18nManager &i18nMgr_;
    OutputManager &outputMgr_;

protected:
    virtual void onBeforeCallBack()
    {
        // auto &common_ = CommonUtils::getInstance();
        // common_.clearScreen();
        switch (menuType_)
        {
        case leafMenuType::Setting:
            outputMgr_.printSettingMenu(title_);
            break;
        case leafMenuType::View:
            outputMgr_.printSettingMenu(title_);
            break;
        case leafMenuType::Update:
            outputMgr_.printSettingMenu(title_);
            break;
        default:
            outputMgr_.printSettingMenu(title_);
            break;
        }
    }
    virtual void onAfterCallBack()
    {
        InputProcessor::waitForEnter(i18nMgr_);
    }
};
