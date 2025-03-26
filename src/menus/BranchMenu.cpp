#include "menus/BranchMenu.hpp"
#include "utils/CommonUtils.hpp"
#include "utils/InputProcessor.hpp"
#include "model/UserManager.hpp"
#include <iostream>
#include <format>

MenuResult BranchMenu::execute()
{
    bool running = true;
    MenuResult res;
    while (running)
    {
        ///if(!g_debugMode){
            auto &common_ = CommonUtils::getInstance();
            common_.clearScreen();
        //}
        displayMenu();
        auto reslt = handleUserSelection();
        res = reslt.first;
        if (res != MenuResult::OK)
        {
            running = false;
        }
        int inputNum = reslt.second;
        MenuResult cRes = children_[inputNum]->execute();
        //children_[inputNum]->execute();
        if(cRes != MenuResult::OK){
            //error
        }
    }
    return res;
}

void BranchMenu::displayMenu() const
{
    auto &userManager = UserManager::getInstance();
    // outputMgr_.printFormattedMessage1(i18nMgr_.getText("title_bar"), title_);
    switch (menuType_)
    {
    case branchMenuType::Main:
        outputMgr_.printTitle(title_);
        outputMgr_.printParameter(i18nMgr_.getText("current_user") + userManager.getCurrentUser());
        break;
    case branchMenuType::Sub:
        outputMgr_.printSubTitle(title_);
        break;
    case branchMenuType::SubSub:
        outputMgr_.printSub2Title(title_);
        break;
    case branchMenuType::Setting:
        outputMgr_.printSettingMenu(title_);
        break;
    default:
        outputMgr_.printSubTitle(title_);
        break;
    }
    for (size_t i = 0; i < children_.size(); ++i)
    {
        outputMgr_.print("[" + std::to_string(i) + "] " + children_[i]->getTitle());
    }
    //outputMgr_.print(i18nMgr_.getText("menu_option_switch_user"));
    outputMgr_.print(i18nMgr_.getText("menu_option_exit"));
}

std::pair<MenuResult, int> BranchMenu::handleUserSelection()
{
    while (true)
    {
        outputMgr_.printInput("", false);
        std::string userInput = inputMgr_.getStringInput().value_or("");

        if(menuType_ == branchMenuType::Main){
            if (InputProcessor::shouldReturnToMenu(userInput, i18nMgr_.getText("exit")))
            {
                return std::pair<MenuResult, int>{MenuResult::EXIT, -1};
            }
        }
        else{
            if (InputProcessor::shouldReturnToMenu(userInput, i18nMgr_.getText("back_to_menu")))
            {
                return std::pair<MenuResult, int>{MenuResult::BACK, -1};
            }
        }
        // if (InputProcessor::shouldReturnToSwitchUser(userInput))
        // {
        //     return std::pair<MenuResult, int>{MenuResult::SWITCH_USER, -1};
        // }
        if (!InputProcessor::validateAndGetIndex(userInput,
                                                 0,
                                                 children_.size() - 1))
        {
            outputMgr_.printError(i18nMgr_.getText("error_invalid_number"));
            continue;
        }
        return std::pair<MenuResult, int>{MenuResult::OK, stoi(userInput)};
    }
}
