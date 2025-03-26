#include "controllers/HabitController.hpp"
#include "utils/DateUtils.hpp"
#include "utils/InputProcessor.hpp"
#include <functional>
#include <format>
#include <iomanip>  // std::setw, std::setfill

void HabitController::showHabitListFlow()
{
    outputMgr_.printSub2Title(i18nMgr_.getText("habits_list_title"));
    
    std::vector<std::string> habits = habitRepo_.getAllHabits();
    size_t maxDigits = std::to_string(habits.size()).length();  // 最大桁数を計算

    for (size_t i = 0; i < habits.size(); ++i)
    {
        std::ostringstream oss;
        oss << " " << std::setw(maxDigits) << std::setfill(' ') << std::right << (i + 1) << ". " << habits[i];
        outputMgr_.print(oss.str(), true);
    }

}

void HabitController::manageHabitFlow(HabitAction action)
{
    std::string promptMessage;
    std::string successMessage;
    std::string secondPromptMessage;
    std::string result;
    std::string input1, input2;

    // アクションごとのプロンプト設定
    switch (action)
    {
    case HabitAction::Add:
        promptMessage = i18nMgr_.getText("prompt_input_add_habit");
        successMessage = i18nMgr_.getText("add_habit_complete");
        break;

    case HabitAction::Edit:
        promptMessage = i18nMgr_.getText("prompt_input_edit_habit");
        successMessage = i18nMgr_.getText("edit_habit_complete");
        secondPromptMessage = i18nMgr_.getText("prompt_input_replace_habit");
        break;

    case HabitAction::Remove:
        promptMessage = i18nMgr_.getText("prompt_input_remove_habit");
        successMessage = i18nMgr_.getText("remove_habit_complete");
        break;

    default:
        outputMgr_.printError("Invalid action type.");
        return;
    }
    while(true)
    {
        std::vector<std::string> habits = habitRepo_.getAllHabits();
        // 番号付き
        for (size_t i = 0; i < habits.size(); ++i)
        {
            outputMgr_.print(" "+std::to_string(i + 1) + ". " + habits[i], true);
        }


        if(action == HabitAction::Add){
            outputMgr_.printInput(promptMessage, true);
            input1 = inputMgr_.getStringInput().value_or("");
            if (input1.empty())
            {
                outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
                return;
            }
        }else{
            // 編集・削除時の番号入力
            outputMgr_.printInput(promptMessage, true);
            std::string selectedNum = inputMgr_.getStringInput().value_or("");
            if (selectedNum.empty()) {
                outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
                return;
            }

            int selectedIndex = -1;
            try {
                selectedIndex = std::stoi(selectedNum);
                if (selectedIndex >= 1 && selectedIndex <= static_cast<int>(habits.size())) {
                    input1 = habits[selectedIndex - 1];
                } else {
                    outputMgr_.printError(i18nMgr_.getText("error_invalid_number"));
                    continue;
                }
            } catch (...) {
                outputMgr_.printError(i18nMgr_.getText("error_invalid_number"));
                continue;
            }

            // 編集時のみ新しい名前を入力
            if (action == HabitAction::Edit) {
                outputMgr_.printInput(secondPromptMessage, true);
                input2 = inputMgr_.getStringInput().value_or("");
                if (input2.empty()) {
                    outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
                    return;
                }
            }
        }
        // // 確認メッセージ [ ]
        // outputMgr_.printInput(i18nMgr_.getText("prompt_confirm"));
        // std::string confirmInput = inputMgr_.getStringInput().value_or("");
        // if (confirmInput != "y" && confirmInput != "Y") {
        //     outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
        //     continue;
        // }

        // スイッチ文でサービス呼び出し
        switch (action)
        {
        case HabitAction::Add:
            result = habitService_.createHabit(input1);
            break;

        case HabitAction::Edit:
            result = habitService_.updateHabit(input1, input2);
            break;

        case HabitAction::Remove:
            result = habitService_.deleteHabit(input1);
            break;
        }

        // 実行結果表示
        if (result == "success")
        {
            std::string resultMessage = std::vformat(successMessage, std::make_format_args(input1, input2));
            outputMgr_.printComplete(resultMessage);
        }
        else
        {
            outputMgr_.printError(result);
        }
    }
}


// void HabitController::manageHabitFlow(HabitAction action) {
//     std::string promptMessage;
//     std::string successMessage;
//     std::string secondPromptMessage;
//     std::string result;
//     std::string input1, input2;
//     bool loop = true;

//     // アクションごとのプロンプト設定
//     switch (action) {
//         case HabitAction::Add:
//             promptMessage = i18nMgr_.getText("prompt_input_add_habit");
//             successMessage = i18nMgr_.getText("add_habit_complete");
//             break;

//         case HabitAction::Edit:
//             promptMessage = i18nMgr_.getText("prompt_input_edit_habit");
//             successMessage = i18nMgr_.getText("edit_habit_complete");
//             secondPromptMessage = i18nMgr_.getText("prompt_input_replace_habit");
//             break;

//         case HabitAction::Remove:
//             promptMessage = i18nMgr_.getText("prompt_input_remove_habit");
//             successMessage = i18nMgr_.getText("remove_habit_complete");
//             break;

//         default:
//             outputMgr_.printError("Invalid action type.");
//             return;
//     }

//     while (loop) {
//         // 習慣一覧表示
//         std::vector<std::string> habits = habitRepo_.getAllHabits();
//         if (habits.empty()) {
//             outputMgr_.printError(i18nMgr_.getText("error_no_habits"));
//             return;
//         }

//         outputMgr_.print(i18nMgr_.getText("habits_list_title"));
//         for (size_t i = 0; i < habits.size(); ++i) {
//             outputMgr_.print(" " + std::to_string(i + 1) + ". " + habits[i], true);
//         }

//         // 入力受付（番号または名前）
//         outputMgr_.printInput(promptMessage);
//         input1 = inputMgr_.getStringInput().value_or("");
//         if (input1.empty()) {
//             outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
//             return;
//         }

//         int selectedIndex = -1;
//         try {
//             selectedIndex = std::stoi(input1);
//             if (selectedIndex >= 1 && selectedIndex <= static_cast<int>(habits.size())) {
//                 input1 = habits[selectedIndex - 1];
//             } else {
//                 outputMgr_.printError(i18nMgr_.getText("error_invalid_number"));
//                 continue;
//             }
//         } catch (...) {
//             // 数字でない場合はそのまま使う
//         }

//         // 編集時のみ2つ目の入力を取得
//         if (action == HabitAction::Edit) {
//             outputMgr_.printInput(secondPromptMessage);
//             input2 = inputMgr_.getStringInput().value_or("");
//             if (input2.empty()) {
//                 outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
//                 return;
//             }
//         }

//         // 確認メッセージ
//         outputMgr_.printInput(i18nMgr_.getText("prompt_confirm"));
//         std::string confirmInput = inputMgr_.getStringInput().value_or("");
//         if (confirmInput != "y" && confirmInput != "Y") {
//             outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
//             continue;
//         }

//         // サービス呼び出し
//         switch (action) {
//             case HabitAction::Add:
//                 result = habitService_.createHabit(input1);
//                 break;

//             case HabitAction::Edit:
//                 result = habitService_.updateHabit(input1, input2);
//                 break;

//             case HabitAction::Remove:
//                 result = habitService_.deleteHabit(input1);
//                 break;
//         }

//         // 実行結果表示
//         if (result == "success") {
//             std::string resultMessage = std::vformat(successMessage, std::make_format_args(input1, input2));
//             outputMgr_.printComplete(resultMessage);
//         } else {
//             outputMgr_.printError(result);
//         }

//         // ループ継続確認
//         outputMgr_.printInput(i18nMgr_.getText("prompt_continue"));
//         std::string continueInput = inputMgr_.getStringInput().value_or("");
//         if (continueInput.empty()) {
//             outputMgr_.printError(i18nMgr_.getText("prompt_cancel"));
//             break;
//         }
//     }
// }