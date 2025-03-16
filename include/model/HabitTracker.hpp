#ifndef HABIT_TRACKER_HPP
#define HABIT_TRACKER_HPP

#include "model/JSONManager.hpp"
#include "model/HabitListManager.hpp"
#include "message/MessageManager.hpp"
#include "input/InputManager.hpp"
#include "output/OutputManager.hpp"

// HabitTrackerクラスの責務
//  データ管理:
//      習慣達成記録のデータを管理し、保存・読み込みを行う。
// データ提供:
//      習慣達成記録を提供し、他のクラスが利用できるようにする。
class HabitTracker
{
public:
    explicit HabitTracker(
        const std::string &filename,
        HabitListManager &habitList,
        MessageManager &messageManager,
        InputManager &inputManager,
        OutputManager &outputManager);

    void record(const std::string &day);
    void show(const std::string &day);
    void showToday();
    void showSelectedDay();
    void showWeek();
    void showMonth();
    void showAll();

private:
    JSONManager jsonManager_;
    json recordData_;
    HabitListManager &habitListManager_;
    MessageManager &messageManager_;
    InputManager &inputManager_;
    OutputManager &outputManager_;

    std::vector<std::string> getSortedDates();
    void showSummary(
        const std::string &title,
        std::function<bool(const std::string &)> filter);
};

#endif
