#include "services/RecordService.hpp"
#include "utils/DateUtils.hpp"
#include <format>
//記録の追加、更新、表示、週次集計を管理
//コントローラのビジネスロジックを移譲

std::string RecordService::updateRecord(const std::string &date,
                                        const std::string &habit,
                                        bool isComplete)
{
    //logInfo("Updating record for habit: " + habit + " on date: " + date);
    std::string result = recordRepo_.updateRecord(date, habit, isComplete);
    if (result != "success")
    {
        //logError("Failed to update record: " + result);
    }
    return result;
}
std::string RecordService::updateRecords(const std::string &date, const std::vector<std::string> &habits)
{
    for (const auto &habit : habits)
    {
        // 仮のステータス取得ロジック（実際にはコントローラが処理する）
        bool status = true;
        std::string result = updateRecord(date, habit, status);
        if (result != "success")
        {
            return result;
        }
    }

    // 日次データ取得
    nlohmann::json allDaily;
    if (recordRepo_.getAllRecords(allDaily) == "success")
    {
        // 週次集計
        nlohmann::json weeklyData = calculateWeeklySummary(allDaily);

        // 集計データを保存
        weeklyRepo_.setWeeklyData(weeklyData);
        weeklyRepo_.save();
    }

    return "success";
}
std::vector<std::string> RecordService::getAllHabits()
{
    return habitRepo_.getAllHabits();
}

std::string RecordService::getSelectedDateLogic(const std::string &userInput)
{
    auto &dateUt = DateUtils::getInstance();
    if (userInput == "t")
    {
        return dateUt.getTodayDate();
    }
    else if (userInput == "y")
    {
        return dateUt.getYesterdayDate();
    }
    else if (dateUt.isValidDate(userInput))
    {
        return userInput;
    }
    return "error_invalid_date";
}

nlohmann::json RecordService::calculateWeeklySummary(const nlohmann::json &dailyRecords)
{
    using json = nlohmann::json;
    auto &dateUtil = DateUtils::getInstance();

    // 週番号 -> 合計カウント
    std::map<int, int> totalCountMap;
    // 週番号 -> (習慣名 -> カウント)
    std::map<int, std::map<std::string, int>> habitCountMap;
    // 週番号 -> 最も早い日付 (週のstart/end計算のため)
    std::map<int, std::string> earliestDateMap;

    // (1) 日別データを走査
    for (auto &[dateStr, habitObj] : dailyRecords.items())
    {
        // ISO週番号を取得
        int weekNum = dateUtil.getWeekNumber(dateStr);
        if (weekNum == 0)
        {
            // パース失敗など
            continue;
        }

        // earliestDateMap 更新
        auto it = earliestDateMap.find(weekNum);
        if (it == earliestDateMap.end())
        {
            earliestDateMap[weekNum] = dateStr; // 初回登録
        }
        else
        {
            // より早い日付を採用
            if (dateStr < it->second)
            {
                it->second = dateStr;
            }
        }

        // (2) true/falseの数をカウント
        for (auto &[habitName, statusVal] : habitObj.items())
        {
            bool achieved = false;
            try
            {
                achieved = statusVal.get<bool>();
            }
            catch (...)
            {
                // bool以外ならスキップ
                continue;
            }
            int addCount = achieved ? 1 : 0;
            totalCountMap[weekNum] += addCount;
            habitCountMap[weekNum][habitName] += addCount;
        }
    }

    // (3) 週次データをJSONにまとめる
    json weeksArr = json::array();

    for (auto &[weekNum, totalCnt] : totalCountMap)
    {
        json weekItem;
        weekItem["weekNumber"] = weekNum;

        // startDate / endDate
        std::string baseDate = earliestDateMap[weekNum];
        std::string sDate = dateUtil.getWeekStartDate(baseDate);
        std::string eDate = dateUtil.getWeekEndDate(baseDate);
        weekItem["startDate"] = sDate;
        weekItem["endDate"] = eDate;

        weekItem["totalCount"] = totalCnt;

        // 各習慣
        json habitArr = json::array();
        if (habitCountMap.count(weekNum))
        {
            for (auto &[hName, hCount] : habitCountMap[weekNum])
            {
                json h;
                h["name"] = hName;
                h["count"] = hCount;
                habitArr.push_back(h);
            }
        }
        weekItem["habits"] = habitArr;

        weeksArr.push_back(weekItem);
    }

    json result;
    result["weeks"] = weeksArr;
    return result;
}

std::string RecordService::getRecordsByDate(const std::string &date, nlohmann::json &recordData)
{
    std::string result = recordRepo_.getRecordsByDate(date, recordData);
    if (result != "success")
    {
        //logError("Failed to get records for date: " + date);
    }
    return result;
}

double RecordService::calculateAchievementRate(const nlohmann::json &recordData)
{
    double total = recordData.size();
    double completed = 0;

    for (auto &pair : recordData.items())
    {
        if (pair.value())
        {
            completed++;
        }
    }

    if (total > 0)
    {
        return (completed / total) * 100.0;
    }
    return 0.0;
}

std::string RecordService::getAllRecords(nlohmann::json &recordData)
{
    return recordRepo_.getAllRecords(recordData);
}

std::map<std::string, int> RecordService::calculateHabitCountWithFilter(
    const nlohmann::json &recordData, 
    const std::function<bool(const std::string &)> &filter,
    int &validDays)
{
    auto &dateUtil = DateUtils::getInstance();
    auto sortedDates = dateUtil.getSortedDateKeys(recordData);

    std::map<std::string, int> habitCount;
    validDays = 0;

    for (const auto &date : sortedDates)
    {
        if (filter(date))
        {
            nlohmann::json habits = recordData[date];
            if (!habits.empty())
            {
                validDays++;
                for (const auto &[habit, status] : habits.items())
                {
                    if (status)
                        habitCount[habit]++;
                }
            }
        }
    }

    return habitCount;
}

std::map<std::string, int> RecordService::getFilteredHabitCount(
    const std::function<bool(const std::string &)> &filter,
    int &validDays)
{
    nlohmann::json recordData;
    std::string result = getAllRecords(recordData);
    if (result != "success")
    {
        //logError("Failed to get all records");
        return {};
    }

    return calculateHabitCountWithFilter(recordData, filter, validDays);
}