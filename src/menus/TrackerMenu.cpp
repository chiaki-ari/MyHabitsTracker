#include "menus/TrackerMenu.hpp"
#include "utils/CommonUtils.hpp"
#include "utils/InputProcessor.hpp"
#include <iostream>
#include <format>

TrackerMenu::TrackerMenu(
    const std::string& title, 
    MessageManager& messageManager, 
    InputManager& inputManager, 
    OutputManager& outputManager)
        : messageManager_(messageManager), 
        inputManager_(inputManager), 
        outputManager_(outputManager), 
        title_(title) 
    {
        setTitle(title);
    }

void TrackerMenu::execute() {
    while (true) {
        auto& common_ = CommonUtils::getInstance();
        common_.clearScreen();  
        displayMenu();
        int inputMenuNum = handleUserSelection();
        if (inputMenuNum == -1) return; // 戻る処理
        children_[inputMenuNum]->execute();
    }
}


void TrackerMenu::displayMenu() const {
    std::string templateStr = messageManager_.getMessage("title_bar");
    std::string result = std::vformat(templateStr, std::make_format_args(title_));
    outputManager_.print(result);
    for (size_t i = 0; i < children_.size(); ++i) {
        outputManager_.print("[" + std::to_string(i) + "] " + children_[i]->getTitle());
    }
    outputManager_.print(messageManager_.getMessage("menu_option_exit"));
}


int TrackerMenu::handleUserSelection() {
    while (true) {
        outputManager_.print(messageManager_.getMessage("prompt_input_start"),false);
        std::string userInput = inputManager_.getStringInput().value_or("");
        if (InputProcessor::shouldReturnToMenu(userInput, messageManager_.getMessage("back_to_menu"))) {
            return -1;
        }
        if(!InputProcessor::validateAndGetIndex(
            userInput, 
            0, 
            children_.size()-1,
            messageManager_.getMessage("error_invalid_number_input"),
            messageManager_)) {
                continue;
        }
        return stoi(userInput);
    }
}
