#ifndef RECORD_SERVICE_HPP
#define RECORD_SERVICE_HPP

#include "repositories/RecordRepository.hpp"
#include "repositories/WeeklySummaryRepository.hpp"
#include "repositories/HabitRepository.hpp"
#include "model/LogManager.hpp"
// 日付範囲のモード: 単日 / 連続
enum class DateRangeMode {
    SingleDay,
    Continuous
};

// 習慣選択モード: 全習慣 / 指定習慣
enum class HabitMode {
    AllHabits,
    SingleHabit
};

class RecordService
{
public:
    RecordService(RecordRepository &recordRepo,
                  WeeklySummaryRepository &weeklyRepo,
                  HabitRepository &habitRepo,
                  LogManager &logMgr)
        : recordRepo_(recordRepo),
          weeklyRepo_(weeklyRepo),
          habitRepo_(habitRepo),
          logMgr_(logMgr)
    // BaseService(logMgr)

    {
    }

    std::vector<std::string> getAllHabits();
    std::string getSelectedDateLogic(const std::string &userInput);
    std::string updateRecords(const std::string &date, const std::vector<std::string> &habits);
    std::string updateRecord(const std::string &date, const std::string &habit, bool isComplete);
    std::string getRecordsByDate(const std::string &date, nlohmann::json &recordData);
    double calculateAchievementRate(const nlohmann::json &recordData);
    std::string getAllRecords(nlohmann::json &recordData);
    std::map<std::string, int> calculateHabitCountWithFilter(
        const nlohmann::json &recordData,
        const std::function<bool(const std::string &)> &filter,
        int &validDays);
    std::map<std::string, int> getFilteredHabitCount(
        const std::function<bool(const std::string &)> &filter,
        int &validDays);

private:
    RecordRepository &recordRepo_;
    WeeklySummaryRepository &weeklyRepo_;
    HabitRepository &habitRepo_;
    LogManager &logMgr_;

    nlohmann::json calculateWeeklySummary(const nlohmann::json &dailyRecords);
};

#endif // RECORD_SERVICE_HPP
