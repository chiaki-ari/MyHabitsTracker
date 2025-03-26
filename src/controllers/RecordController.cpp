#include "controllers/RecordController.hpp"
#include "utils/DateUtils.hpp"
#include "utils/InputProcessor.hpp"
#include <iostream>
#include <format>
#include <iomanip> // std::setw, std::setfill



void RecordController::showRecordFlow(ShowType showType)
{
    auto range = getDateRangeFromShowType(showType);
    if (range.first.empty() && range.second.empty()) {
        // キャンセル等のエラーハンドリング
        return;
    }
    showRecordsInRange(range.first, range.second,showType);
    outputMgr_.printLine();
}

std::pair<std::string,std::string> RecordController::getDateRangeFromShowType(ShowType showType)
{
    auto &dateUtil = DateUtils::getInstance();
    std::string start, end;
    switch (showType)
    {
    case ShowType::Today:
        start = dateUtil.getTodayDate();
        end   = start;
        break;
    case ShowType::Yesterday:
        start = dateUtil.getYesterdayDate();
        end   = start;
        break;
    case ShowType::SelectedDate:
        if (getSelectedDate(start, "prompt_input_date") != "success") {
            // UIでキャンセルされたなら空を返す等
            return {"",""};
        }
        end = start;
        break;
    case ShowType::LastWeek:
    {
        time_t now = dateUtil.getCurrentTime();
        time_t weekAgo = now - (7 * 24 * 3600);
        start = dateUtil.formatDate(weekAgo);
        end = dateUtil.formatDate(now);
        break;
    }
    case ShowType::ThisMonth:
    {
        int y,m;
        dateUtil.getCurrentYearMonth(y, m);
        start = dateUtil.getMonthStartDate(y, m);
        end   = dateUtil.getMonthEndDate(y, m);
        break;
    }
    case ShowType::SelectedWeek:
        if (getSelectedWeek(start) != "success") {
            return {"",""};
        }
        end = dateUtil.shiftDate(start, 6); // 1週間後
        break;
    case ShowType::SelectedMonth:
    {
        int y,m;
        if (getSelectedMonth(y, m) != "success") {
            return {"",""};
        }
        // start = "YYYY-MM-01"; end = "YYYY-MM-last day"
        start = dateUtil.getMonthStartDate(y, m);
        end   = dateUtil.getMonthEndDate(y, m);
        break;
    }
    // 省略: ThisMonth/LastWeekなども同様
    default:
        // 全期間など
        start = "2000-01-01"; 
        end   = dateUtil.getTodayDate();
        break;
    }
    return {start, end};
}


void RecordController::showRecordsInRange(std::string startDate,std::string endDate, ShowType showType)
{
    std::string tmplTitle;
    int mode =0;
    int shiftDays = 0;
    std::string currentDate = startDate;
    std::string  currentEndDate = endDate;
    int currentMonth,currentYear;
    auto &dateUtil = DateUtils::getInstance();
    InputProcessor ip;
    bool running = true;
    switch (showType)
    {
    case ShowType::Today:
    case ShowType::Yesterday:
    case ShowType::SelectedDate:
        tmplTitle = i18nMgr_.getText("title_achievement_status");
        mode =1;
        shiftDays = 1;
        break;
    case ShowType::LastWeek:
    case ShowType::SelectedWeek:
        tmplTitle = i18nMgr_.getText("one_week_record_title");
        shiftDays = 7;
        mode =2;
        break;
    case ShowType::ThisMonth:
    case ShowType::SelectedMonth: 
        tmplTitle = i18nMgr_.getText("this_month_record_title");
        mode =3;
        break;
    default:
        outputMgr_.printError("Invalid update type.");
        break;
    }

    while(running)
    {    
        // タイトル表示
        if(mode == 1){
            std::string formattedMessage = std::vformat(tmplTitle, std::make_format_args(currentDate));
            outputMgr_.printSub2Title(formattedMessage);
        }else if(mode == 2){
            std::string formattedMessage = std::vformat(tmplTitle, std::make_format_args(currentDate, currentEndDate));
            outputMgr_.printSub2Title(formattedMessage);
            // showRecordSummaryWithFilter([&](const std::string &date)
            //     { return date >= currentDate && date <= currentEndDate; });
        }else if(mode == 3){
            dateUtil.getYearAndMonth(currentDate, currentYear, currentMonth);
            std::string formattedMessage = std::vformat(tmplTitle, std::make_format_args(currentYear, currentMonth));
            outputMgr_.printSub2Title(formattedMessage);

            // showRecordSummaryWithFilter([&](const std::string &date)
            // { return dateUtil.isSameYearMonth(date, currentYear, currentMonth); });
        }

        if(mode == 1){
            std::string result = showRecordForDate(currentDate);
            if(result != "success"){
                outputMgr_.printError(result);
            }
        }else{
            // まとめて表示
            showRecordSummaryWithFilter([&](const std::string &date) {
                return date >= currentDate && date <= currentEndDate;
            });
        }

        outputMgr_.printLine();
        outputMgr_.printInput(i18nMgr_.getText("recode_paging_guide"), true);
        auto key = ip.getKeyInput();
        switch (key)
        {
        case InputProcessor::KeyType::ArrowLeft:
            if(mode == 1 || mode == 2){
                currentDate = dateUtil.shiftDate(currentDate, -(shiftDays));
                currentEndDate = dateUtil.shiftDate(currentEndDate, -(shiftDays));
            }else{
                std::string res = dateUtil.shiftMonth(currentYear, currentMonth, -1);
            }
            break;
        case InputProcessor::KeyType::ArrowRight:
            if(mode == 1 || mode == 2){
                currentDate = dateUtil.shiftDate(currentDate, shiftDays);
                currentEndDate = dateUtil.shiftDate(currentEndDate, shiftDays);
            }else{
                std::string res = dateUtil.shiftMonth(currentYear, currentMonth, 1);
                currentDate = dateUtil.getMonthStartDate(currentYear, currentMonth);
                currentEndDate   = dateUtil.getMonthEndDate(currentYear, currentMonth);
            }
            break;
        case InputProcessor::KeyType::Esc:
        case InputProcessor::KeyType::Other:
            running = false;
            break;
        default:
            // 何もしない or エラー表示
            break;
        }
        std::cout << std::endl;
    }
}
std::string RecordController::showRecordForDate(const std::string &date)
{
    nlohmann::json recordData;
    std::string res;
    // 表示データ取得
    std::string getRecordResult = recordService_.getRecordsByDate(date, recordData);
    if (getRecordResult != "success") // error_no_record
    {
        res = getRecordResult;
    }
    else
    {
        // 出力表示
        int num = 1;
        // std::ostringstream oss;
        size_t maxDigits = std::to_string(recordData.size()).length(); // 最大桁数を計算
        for (auto &pair : recordData.items())
        {
            std::cout << " " << std::setw(maxDigits) << std::setfill(' ') << std::right << num << ". ";
            // std::cout << oss.str();
            if (pair.value())
            {
                //outputMgr_.print(i18nMgr_.getText("achievement_points"+ " ") + pair.key());
                std::cout << "v " << pair.key() << std::endl;
            }
            else
            {
                //outputMgr_.print(i18nMgr_.getText("unachievement_points"+ " ") + pair.key());
                std::cout << "  " << pair.key() << std::endl;
            }
            //std::cout << pair.key() << std::endl;
            num++;
        }
        if (recordData.size() > 0)
        {
            // 達成率の計算と表示
            double percentage = recordService_.calculateAchievementRate(recordData);
            int per = trunc(percentage);
            std::string templateStr = i18nMgr_.getText("prompt_achievement_rate");
            std::string result = std::vformat(templateStr, std::make_format_args(per));
            outputMgr_.printStrong(result);
        }
        res = "success";
    }
    return res;
}

void RecordController::showRecordSummaryWithFilter(const std::function<bool(const std::string &)> &filter)
{
    int validDays = 0;
    std::map<std::string, int> habitCount = recordService_.getFilteredHabitCount(filter, validDays);

    if (validDays == 0)
    {
        outputMgr_.printError(i18nMgr_.getText("error_no_data"));
        return;
    }
    // 最大文字数を計算
    size_t maxHabitLength = 0;
    std::vector<std::string> habitList = recordService_.getAllHabits();
    for (const auto &habit : habitList)
    {
        maxHabitLength = std::max(maxHabitLength, habit.length());
    }
    size_t maxDigits = std::to_string(habitList.size()).length(); // 最大桁数を計算
    // 星の数を生成
    double completed = 0, total = 0;
    std::ostringstream oss;
    for (const auto &[habit, count] : habitCount)
    {
        // 数字部分を出力
        //oss << " " << std::setw(maxDigits) << std::setfill('0') << num << ". ";
        std::cout << " " << std::setw(maxDigits) << std::setfill(' ') << std::right << total+1 << ". ";
        //std::cout << oss.str();
        // 習慣名と星マークを出力
        std::cout << std::setw(maxHabitLength) << std::setfill(' ') << std::left << habit << " | ";
        for (int i = 0; i < count; i++)
        {
            std::cout << "*";
            completed++;
        }
        std::cout << "\n";
        total++;
    }

    // 達成率の計算と表示
    if (total > 0)
    {
        double percentage = (completed / total) * 100.0;
        int per = trunc(percentage);
        std::string templateStr = i18nMgr_.getText("prompt_achievement_rate");
        std::string result = std::vformat(templateStr, std::make_format_args(per));
        outputMgr_.printStrong(result);
    }
}

void RecordController::updateRecordsFlow(UpdateType updateType)
{
    auto &dateUtil = DateUtils::getInstance();
    std::string selectedDate, selectedSecondDate;
    std::string formattedMessage;
    std::string currentDate = dateUtil.getTodayDate();

    if(updateType == UpdateType::Continuousbydate)
    {
        outputMgr_.printGuide(i18nMgr_.getText("guide_record_continuous_date"));
    }else if ( updateType == UpdateType::Continuousbyhabit){
        outputMgr_.printGuide(i18nMgr_.getText("guide_record_continuous_habit"));

    }

    // 日付取得または今日の日付設定
    switch (updateType)
    {
    case UpdateType::Today:
    {
        selectedDate = currentDate;
        selectedSecondDate = currentDate;
        formattedMessage = std::vformat(i18nMgr_.getText("record_today_progress"), std::make_format_args(selectedDate));
        outputMgr_.printGuide(formattedMessage);
        // updateSingledayRecord(selectedDate);
        break;
    }
    case UpdateType::SelectedDate:
    {
        std::string result = getSelectedDate(selectedDate, "prompt_input_date");
        if (result != "success")
        {
            outputMgr_.printError(i18nMgr_.getText(result));
            return;
        }
        selectedSecondDate = selectedDate;
        formattedMessage = std::vformat(i18nMgr_.getText("record_today_progress"), std::make_format_args(selectedDate));
        outputMgr_.printGuide(formattedMessage);
        // updateSingledayRecord(selectedDate);
        break;
    }
    case UpdateType::Continuousbydate:
    case UpdateType::Continuousbyhabit:
    {
        std::string result = getSelectedDate(selectedDate, "prompt_input_start_date");
        if (result != "success")
        {
            outputMgr_.printError(i18nMgr_.getText(result));
            return;
        }
        result = getSelectedDate(selectedSecondDate, "prompt_input_end_date");
        if (result != "success")
        {
            outputMgr_.printError(i18nMgr_.getText(result));
            return;
        }
        if(dateUtil.isStartDateLater(selectedDate, selectedSecondDate)){
            std::string tmp = selectedDate;
            selectedDate = selectedSecondDate;
            selectedSecondDate = tmp;
        }
        formattedMessage = std::vformat(i18nMgr_.getText("record_today_progress"), std::make_format_args(selectedDate));
        outputMgr_.printGuide(formattedMessage);
        // updateContinuousRecord(updateType, selectedDate, currentDate);
        break;
    }
    case UpdateType::SpecificDateHabit:
    {
        std::string result = getSelectedDate(selectedDate,"prompt_input_date");
        if (result != "success")
        {
            outputMgr_.printError(i18nMgr_.getText(result));
            return;
        }
        selectedSecondDate = selectedDate;
        formattedMessage = std::vformat(i18nMgr_.getText("record_specific_date_habit_progress"), std::make_format_args(selectedDate));
        outputMgr_.printGuide(formattedMessage);
        // updateSpecificHabitOnSpecificDate(selectedDate);
        break;
    }
    default:
    {
        outputMgr_.printError("Invalid update type.");
        return;
    }
    }
    // 共通更新処理呼び出し
    bool isContinuous = (updateType == UpdateType::Continuousbydate || updateType == UpdateType::Continuousbyhabit);
    bool isHabitMode = (updateType == UpdateType::Continuousbyhabit || updateType == UpdateType::SpecificDateHabit);

    updateRecords(selectedDate, selectedSecondDate, isContinuous, isHabitMode);
    outputMgr_.printLine();
    return;
}


void RecordController::updateRecords(const std::string &selectedDate, const std::string &endDate, bool isContinuous, bool isHabitMode)
{
    auto &dateUtil = DateUtils::getInstance();
    std::string recordDate = selectedDate;
    int count = 0;

    while (recordDate <= endDate)
    {
        std::vector<std::string> allHabits = recordService_.getAllHabits();
        if (allHabits.empty())
        {
            outputMgr_.printError(i18nMgr_.getText("error_no_habits"));
            return;
        }
        if (isHabitMode)
        {
            outputMgr_.printSub2Title(i18nMgr_.getText("habits_list_title"));
            size_t maxDigits = std::to_string(allHabits.size()).length(); // 最大桁数を計算
            for (size_t i = 0; i < allHabits.size(); ++i)
            {
                std::cout << " " << std::setw(maxDigits) << std::setfill(' ') << std::right << i + 1 << ". ";
                outputMgr_.print(allHabits[i]);
            }

            outputMgr_.printInput(i18nMgr_.getText("prompt_select_habit"), false);
            std::string habitInput = inputMgr_.getStringInput().value_or("");
            if (habitInput.empty())
            {
                outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
                return;
            }
            int habitIndex = std::stoi(habitInput) - 1;
            std::string habit = allHabits[habitIndex];

            int status = getValidUserInputForRecord(habit);
            if (status == -1)
            {
                outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
                return;
            }

            std::string updateRecordResult = recordService_.updateRecord(recordDate, habit, (status != 0));
            if (updateRecordResult != "success")
            {
                outputMgr_.printError(updateRecordResult);
                return;
            }
            count++;
        }
        else
        {
            for (const auto &habit : allHabits)
            {
                int status = getValidUserInputForRecord(habit);
                if (status == -1)
                {
                    outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
                    return;
                }

                std::string updateRecordResult = recordService_.updateRecord(recordDate, habit, (status != 0));
                if (updateRecordResult != "success")
                {
                    outputMgr_.printError(updateRecordResult);
                    return;
                }
                count++;
            }
        }

        if (!isContinuous)
            break;
        recordDate = dateUtil.shiftDate(recordDate, 1);
    }

    if (count > 0)
    {
        std::string templateStr = i18nMgr_.getText("prompt_record_complete");
        std::string result = std::vformat(templateStr, std::make_format_args(count));
        outputMgr_.printComplete(result);
    }
}std::string RecordController::getSelectedDate(std::string &date, std::string prompt)
{
    outputMgr_.printInput(i18nMgr_.getText(prompt), true);
    while (true)
    {
        // outputMgr_.printInput("");
        std::string userInput = inputMgr_.getStringInput().value_or("");
        if (userInput.empty())
        {
            return "prompt_cancel";
        }

        // 日付取得ロジックをサービスに移譲
        std::string result = recordService_.getSelectedDateLogic(userInput);
        if (result == "error_invalid_date")
        {
            outputMgr_.printError(result);
            continue;
        }

        date = result;
        break;
    }
    return "success";
}

std::string RecordController::getSelectedWeek(std::string &date)
{
    outputMgr_.printInput(i18nMgr_.getText("prompt_input_week"), true);
    while (true)
    {
        std::string userInput = inputMgr_.getStringInput().value_or("");
        if (userInput.empty())
        {
            return "prompt_cancel";
        }
        std::string result = recordService_.getSelectedDateLogic(userInput);
        if (result == "error_invalid_date")
        {
            outputMgr_.printError(result);
            continue;
        }
        date = result;
        break;
    }
    return "success";
}
std::string RecordController::getSelectedMonth(int &year, int &month)
{
    std::string yearInput, monthInput;
    while (true)
    {
        outputMgr_.printInput(i18nMgr_.getText("prompt_input_year"), true);
        yearInput = inputMgr_.getStringInput().value_or("");
        if (yearInput.empty())
        {
            return "prompt_cancel";
        }
        if (!InputProcessor::validateAndGetIndex(yearInput, 1900, 2100))
        {
            outputMgr_.printError(i18nMgr_.getText("error_invalid_year_input"));
            continue;
        }
        year = stoi(yearInput);
        break;
    }
    while (true)
    {
        outputMgr_.printInput(i18nMgr_.getText("prompt_input_month"), false);
        monthInput = inputMgr_.getStringInput().value_or("");
        if (monthInput.empty())
        {
            return "prompt_cancel";
        }
        if (!InputProcessor::validateAndGetIndex(monthInput, 1, 12))
        {
            outputMgr_.printError(i18nMgr_.getText("error_invalid_month_input"));
            continue;
        }
        month = stoi(monthInput);
        break;
    }
    return "success";
}

int RecordController::getValidUserInputForRecord(const auto &habit)
{
    int status;
    while (true)
    {
        outputMgr_.printInput(habit, false);
        std::string userInput = inputMgr_.getStringInput().value_or("");
        if (userInput.empty())
        {
            status = -1;
            break;
        }
        if (!InputProcessor::validateAndGetIndex(userInput,0,1))
        {
            outputMgr_.printError(i18nMgr_.getText("error_invalid_date"));
            continue;
        }
        status = std::stoi(userInput);
        break;
    }
    return status;
}