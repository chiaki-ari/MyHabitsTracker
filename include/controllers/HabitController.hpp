#ifndef HABIT_CONTROLLER_HPP
#define HABIT_CONTROLLER_HPP

#include "repositories/HabitRepository.hpp"
#include "output/I18nManager.hpp"
#include "input/InputManager.hpp"
#include "output/OutputManager.hpp"
#include "model/LogManager.hpp"
#include "services/HabitService.hpp"
#include <string>

// アプリケーション層 or UIロジック層
// ユーザーからの入力受付
// HabitRepository(モデル層)を呼び出して処理を実行
// 結果やエラーメッセージを i18nMgr_ から取得して出力
enum class HabitAction
{
    Add,
    Edit,
    Remove
};
class HabitController
{
public:
    HabitController(HabitRepository &habitRepo,
                    I18nManager &i18nMgr,
                    InputManager &inputMgr,
                    OutputManager &outputMgr,
                    LogManager &logMgr)
        : habitRepo_(habitRepo),
          i18nMgr_(i18nMgr),
          inputMgr_(inputMgr),
          outputMgr_(outputMgr),
          logMgr_(logMgr),
          habitService_(habitRepo, logMgr)
    {
    }
    void manageHabitFlow(HabitAction action);
    void showHabitListFlow();
    // HabitManagerのデータを取得するためのFacadeメソッド
    std::vector<std::string> getHabitsData()
    {
        return habitRepo_.getAllHabits();
    }

private:
    HabitRepository &habitRepo_;

    I18nManager &i18nMgr_;
    InputManager &inputMgr_;
    OutputManager &outputMgr_;
    LogManager &logMgr_;
    
    HabitService habitService_;
};

#endif // HABIT_CONTROLLER_HPP
