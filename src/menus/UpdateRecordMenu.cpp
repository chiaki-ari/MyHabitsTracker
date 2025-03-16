#include "menus/UpdateRecordMenu.hpp"
#include "utils/DateUtils.hpp"
#include "utils/InputProcessor.hpp"
#include <iostream>
#include <format>

UpdateRecordMenu::UpdateRecordMenu(
    HabitTracker& tracker, 
    const std::string& title, 
    MessageManager& messageManager, 
    InputManager& inputManager, 
    OutputManager& outputManager)
    : tracker_(tracker),
    title_(title), 
    messageManager_(messageManager), 
    inputManager_(inputManager), 
    outputManager_(outputManager) 
{
    setTitle(title);
}

void UpdateRecordMenu::execute() {
    auto& date_ = DateUtils::getInstance();
    std::string templateStr = messageManager_.getMessage("title_bar");
    std::string result = std::vformat(templateStr, std::make_format_args(title_));
    outputManager_.print(result);
    outputManager_.print(messageManager_.getMessage("prompt_input_date"));

    while (true) {
        outputManager_.print(messageManager_.getMessage("prompt_input_start"),false);
        std::string userInput = inputManager_.getStringInput().value_or("");
        
        // 空文字(Enterのみ) -> 今日
        std::string selectedDate;
        if (userInput == "t") {
            selectedDate = date_.getTodayDate();
        }
        else if (userInput == "y") {
            selectedDate = date_.getYesterdayDate();
        } else {
            // その他 → 形式チェック
            if (!date_.isValidDate(userInput)) {
                templateStr = messageManager_.getMessage("alert_prompt");
                std::string errorMsg = messageManager_.getMessage("error_invalid_date_input");
                result = std::vformat(templateStr, std::make_format_args(errorMsg));
                outputManager_.print(result);
                continue;
            }
            selectedDate = userInput;
        }

        // 記録更新
        outputManager_.print(messageManager_.getMessage("bullet_points"));
        templateStr = messageManager_.getMessage("prompt_record");
        result = std::vformat(templateStr, std::make_format_args(selectedDate));
        outputManager_.print(result);
        tracker_.record(selectedDate);
        tracker_.show(selectedDate);
        InputProcessor::waitForEnter(messageManager_);
        return;
    }
}
