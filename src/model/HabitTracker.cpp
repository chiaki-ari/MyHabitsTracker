#include "model/HabitTracker.hpp"
#include "utils/DateUtils.hpp"
#include "utils/InputProcessor.hpp"
#include <ctime>
#include <format>
#include <iostream>

HabitTracker::HabitTracker(
    const std::string& filename, 
    HabitListManager& habitList, 
    MessageManager& messageManager, 
    InputManager& inputManager, 
    OutputManager& outputManager)
        : jsonManager_(filename), 
        habitListManager_(habitList), 
        messageManager_(messageManager), 
        inputManager_(inputManager), 
        outputManager_(outputManager) {
        jsonManager_.load(recordData_);
}

void HabitTracker::record(const std::string& day){
    if(!recordData_.contains(day)){
        recordData_[day] = json::object();
    }
    std::vector<std::string> habitsList = habitListManager_.getHabitsList();
    if (habitsList.empty()) {
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string errorMsg = messageManager_.getMessage("error_no_habit");
        std::string result = std::vformat(templateStr, std::make_format_args(errorMsg));
        outputManager_.print(result);
        return;
    }

    for(const auto& habit : habitsList){
        int status;
        while(true){
            std::string templateStr = messageManager_.getMessage("habit_record_prompt");
            std::string result = std::vformat(templateStr, std::make_format_args(habit));
            outputManager_.print(result, false);

            std::string userInput = inputManager_.getStringInput().value_or("");
            if (InputProcessor::shouldReturnToMenu(userInput, messageManager_.getMessage("back_to_menu"))) {
                return;
            }

            if(!InputProcessor::validateAndGetIndex(
                userInput, 
                0, 
                1,
                result,
                messageManager_)) {

            }else{
                status = std::stoi(userInput);
                break;
            }
        }
        recordData_[day][habit] = (status == 1); 
    }
    jsonManager_.save(recordData_);
}

//指定日の習慣達成率の表示
void HabitTracker::show(const std::string& day){
    if (!recordData_.contains(day)) {
        std::string errorMsg = messageManager_.getMessage("error_no_record");
        std::string errorMsg_day = std::vformat(errorMsg, std::make_format_args(day));
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string result = std::vformat(templateStr, std::make_format_args(errorMsg_day));
        outputManager_.print(result);
        return;
    }

    json habits = recordData_[day];

    if(habits.empty()){
        std::string errorMsg = messageManager_.getMessage("error_no_record");
        std::string errorMsg_day = std::vformat(errorMsg, std::make_format_args(day));
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string result = std::vformat(templateStr, std::make_format_args(errorMsg_day));
        outputManager_.print(result);
        return;
    }
    
    std::string templateStr = messageManager_.getMessage("title_bar");
    std::string title = messageManager_.getMessage("title_achievement_status");
    std::string result = std::vformat(templateStr, std::make_format_args(day, title));
    outputManager_.print(result);

    double total = habits.size(), completed = 0;
    for (auto& pair : habits.items()) {
        if (pair.value()) {
            outputManager_.print(messageManager_.getMessage("achievement_points") + pair.key());
            completed++;
        } else {
            outputManager_.print(messageManager_.getMessage("unachievement_points") + pair.key());
        }
    }
    if (total > 0) {
        std::string templateStr = messageManager_.getMessage("prompt_achievement_rate");
        double percentage = (completed / total) * 100;
        std::string result = std::vformat(templateStr, std::make_format_args(percentage));
        outputManager_.print(result);
    }
}

// ソート済み日付の取得
std::vector<std::string> HabitTracker::getSortedDates() {
    auto& date_ = DateUtils::getInstance();
    return date_.getSortedDateKeys(recordData_);
}

// 今日
void HabitTracker::showToday() {
    auto& date_ = DateUtils::getInstance();
    show(date_.getTodayDate());
}


void HabitTracker::showSelectedDay() {
    auto& date_ = DateUtils::getInstance();
    outputManager_.print(messageManager_.getMessage("prompt_input_date_View"));
    std::string selectedDate;

    while (true) {
        outputManager_.print(messageManager_.getMessage("prompt_input_start"),false);
        std::string userInput = inputManager_.getStringInput().value_or("");
        
        // 空文字(Enterのみ) -> 今日
        if (userInput == "y") {
            selectedDate = date_.getYesterdayDate();
            break;
        } else {
            if (!date_.isValidDate(userInput)) {
                std::string templateStr = messageManager_.getMessage("alert_prompt");
                std::string errorMsg = messageManager_.getMessage("error_invalid_date_input");
                std::string result = std::vformat(templateStr, std::make_format_args(errorMsg));
                outputManager_.print(result);
                continue;
            }
            selectedDate = userInput;
            break;
        }
    }
    show(selectedDate);
}


void HabitTracker::showSummary(const std::string& title, std::function<bool(const std::string&)> filter) {
    auto sortedDates = getSortedDates();
    std::map<std::string, int> habitCount;
    int validDays = 0;

    for (const auto& date : sortedDates) {
        if (filter(date)) {
            json habits = recordData_[date];
            if (!habits.empty()) {
                validDays++;
                for (const auto& [habit, status] : habits.items()) {
                    if (status) habitCount[habit]++;
                }
            }
        }
    }

    std::string templateStr = messageManager_.getMessage("title_bar");
    std::string result = std::vformat(templateStr, std::make_format_args(title));
    outputManager_.print(result);
    if (validDays == 0) {
        std::string templateStr = messageManager_.getMessage("alert_prompt");
        std::string errorMsg = messageManager_.getMessage("error_no_data");
        result = std::vformat(templateStr, std::make_format_args(errorMsg));
        outputManager_.print(result);
        return;
    }

    for (const auto& [habit, count] : habitCount) {
        std::cout << std::setw(16) << std::left << habit << " | ";
        for (int i = 0; i < count; i++) std::cout << "*";
        std::cout << " (" << count << ")\n";
    }
}

// 1週間の記録
void HabitTracker::showWeek() {
    auto& date_ = DateUtils::getInstance();
    time_t now = date_.getCurrentTime();
    time_t weekAgo = now - (7 * 24 * 3600);

    std::string startDate = date_.formatDate(weekAgo);
    std::string endDate = date_.formatDate(now);
    
    std::string templateStr = messageManager_.getMessage("one_week_record_title");
    std::string result = std::vformat(templateStr, std::make_format_args(startDate, endDate));

    showSummary(result, [&](const std::string& date) {
        return date_.parseDate(date) >= weekAgo && date_.parseDate(date) <= now;
    });
}

// 1か月の記録
void HabitTracker::showMonth() {
    auto& date_ = DateUtils::getInstance();
    int year, month;
    date_.getCurrentYearMonth(year, month);

    std::string templateStr = messageManager_.getMessage("this_month_record_title");
    std::string result = std::vformat(templateStr, std::make_format_args(year, month));

    showSummary(result, [&](const std::string& date) {
        return date_.isSameYearMonth(date, year, month);
    });
}

// 全ての記録
void HabitTracker::showAll() {
    std::string result = messageManager_.getMessage("all_record_title");
    showSummary(result, [](const std::string&) { return true; });
}
