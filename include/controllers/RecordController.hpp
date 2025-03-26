#ifndef RECORD_CONTROLLER_HPP
#define RECORD_CONTROLLER_HPP

#include "repositories/RecordRepository.hpp"
#include "repositories/WeeklySummaryRepository.hpp"
#include "repositories/HabitRepository.hpp"
#include "output/I18nManager.hpp"
#include "input/InputManager.hpp"
#include "output/OutputManager.hpp"
#include "model/LogManager.hpp"
#include "services/RecordService.hpp"
#include <string>

// コントローラはインタラクションとビューに限定。ビジネスロジックはサービスに移譲
enum class ShowType
{
    Today,
    Yesterday,
    SelectedDate,
    SelectedWeek,
    SelectedMonth,
    All,
    ThisMonth,
    LastWeek
};
enum class UpdateType
{
    Today, // 今日の記録
    SelectedDate,
    Continuousbydate, // 指定日から連続記録
    Continuousbyhabit,
    SpecificDateHabit
};
class RecordController
{
public:
    RecordController(RecordRepository &recordRepo,
                     WeeklySummaryRepository &weeklyRepo,
                     HabitRepository &habitRepo,
                     I18nManager &i18nMgr, InputManager &inputMgr, OutputManager &outputMgr, LogManager &logMgr)
        : i18nMgr_(i18nMgr),
          inputMgr_(inputMgr),
          outputMgr_(outputMgr),
          logMgr_(logMgr),
          // recordRepo_(recordRepo),
          // weeklyRepo_(weeklyRepo),
          // habitRepo_(habitRepo),
          recordService_(recordRepo, weeklyRepo, habitRepo, logMgr)
    {
    }
    void showRecordFlow(ShowType showType);
    void updateRecordsFlow(UpdateType updateType); // 習慣記録を更新するフロー

private:
    I18nManager &i18nMgr_;
    InputManager &inputMgr_;
    OutputManager &outputMgr_;
    LogManager &logMgr_;
    RecordService recordService_;

    void updateRecords(const std::string &selectedDate, const std::string &currentDate, bool isContinuous, bool isHabitMode);

    std::string getSelectedDate(std::string &date, std::string prompt);
    std::string getSelectedWeek(std::string &date);
    std::string getSelectedMonth(int &year, int &month);

    std::pair<std::string,std::string> getDateRangeFromShowType(ShowType showType);
    void showRecordsInRange(std::string startDate,std::string endDate, ShowType showType);

    std::string showRecordForDate(const std::string &date);
    void showRecordSummaryWithFilter(const std::function<bool(const std::string &)> &filter); // フィルタをかけた記録表示

    int getValidUserInputForRecord(const auto &habit);
};

#endif // RECORD_CONTROLLER_HPP
