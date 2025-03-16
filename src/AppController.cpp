#include "AppController.hpp"
#include "menus/ShowHabitsMenu.hpp"
#include "menus/UpdateRecordMenu.hpp"
#include "menus/UpdateHabitsMenu.hpp"
#include "menus/ShowRecordMenu.hpp"

void AppController::run()
{
    mainMenu_ = buildMenu();
    mainMenu_->execute();
}

std::unique_ptr<TrackerMenu> AppController::buildMenu() {

    std::string menuMsg = messageManager_.getMessage("menu_title");
    
    auto mainMenu_ = 
        std::make_unique<TrackerMenu>(
            menuMsg, 
            messageManager_, 
            inputManager_, 
            outputManager_);
    
    // サブメニュー: 記録表示(4項目)
    std::string menuRecordMsg = messageManager_.getMessage("menu_option_record");
    std::string recordTodayMsg = messageManager_.getMessage("menu_option_record_today");
    std::string recordWeekMsg = messageManager_.getMessage("menu_option_record_week");
    std::string recordMonthMsg = messageManager_.getMessage("menu_option_record_month");
    std::string recordAllMsg = messageManager_.getMessage("menu_option_record_all");
    std::string recordSlctedMsg = messageManager_.getMessage("menu_option_record_selected_day");
    
    auto showRecordMenu = 
        std::make_unique<TrackerMenu>(
            menuRecordMsg, 
            messageManager_, 
            inputManager_, 
            outputManager_);
    

    showRecordMenu->addChild(
        std::make_unique<ShowRecordMenu>(
            habitTracker_, 
            recordTodayMsg, 
            [](HabitTracker &t){ t.showToday(); },
            messageManager_,  
            inputManager_, 
            outputManager_ 
        )
    );
    showRecordMenu->addChild(
        std::make_unique<ShowRecordMenu>(
            habitTracker_, 
            recordWeekMsg, 
            [](HabitTracker &t){ t.showWeek(); },
            messageManager_,  
            inputManager_, 
            outputManager_ 
        )
    );
    showRecordMenu->addChild(
        std::make_unique<ShowRecordMenu>(
            habitTracker_, 
            recordMonthMsg, 
            [](HabitTracker &t){ t.showMonth(); },
            messageManager_,  
            inputManager_, 
            outputManager_ 
        )
    );
    showRecordMenu->addChild(
        std::make_unique<ShowRecordMenu>(
            habitTracker_, 
            recordAllMsg, 
            [](HabitTracker &t){ t.showAll(); },
            messageManager_,  
            inputManager_, 
            outputManager_ 
        )
    );
    showRecordMenu->addChild(
        std::make_unique<ShowRecordMenu>(
            habitTracker_, 
            recordSlctedMsg, 
            [](HabitTracker &t){ t.showSelectedDay(); },
            messageManager_,  
            inputManager_, 
            outputManager_ 
        )
    );
  
    // サブメニュー: 習慣管理(2項目)
    std::string menuManageMsg = messageManager_.getMessage("menu_option_manage");
    std::string habitsViewMsg = messageManager_.getMessage("menu_option_habits_view");
    std::string habitAddMsg = messageManager_.getMessage("menu_option_add");
    std::string habitEditMsg = messageManager_.getMessage("menu_option_edit");
    std::string habitRemoveMsg = messageManager_.getMessage("menu_option_remove");
    
    auto habitMenu = 
        std::make_unique<TrackerMenu>(
            menuManageMsg, 
            messageManager_, 
            inputManager_, 
            outputManager_);
    
    habitMenu->addChild(
        std::make_unique<ShowHabitsMenu>(
            habitListManager_, 
            habitsViewMsg,
            messageManager_,  
            inputManager_, 
            outputManager_ 
        ));
    habitMenu->addChild(
        std::make_unique<UpdateHabitsMenu>(
            habitListManager_, 
            habitAddMsg, 
            [](HabitListManager &m){ m.addHabit(); },
            messageManager_, 
            inputManager_,  
            outputManager_ 
        ));
    habitMenu->addChild(
        std::make_unique<UpdateHabitsMenu>(
            habitListManager_, 
            habitEditMsg, 
            [](HabitListManager &m){ m.editHabit(); },
            messageManager_,  
            inputManager_, 
            outputManager_ 
        ));
    habitMenu->addChild(
        std::make_unique<UpdateHabitsMenu>(
            habitListManager_, 
            habitRemoveMsg, 
            [](HabitListManager &m){ m.removeHabit(); },
            messageManager_,  
            inputManager_, 
            outputManager_ 
        ));
    
    std::string menuUpdateMsg = messageManager_.getMessage("menu_option_update");
    mainMenu_->addChild(std::make_unique<UpdateRecordMenu>(
        habitTracker_, 
        menuUpdateMsg, 
        messageManager_, 
        inputManager_, 
        outputManager_)); // [0] 記録更新
    mainMenu_->addChild(std::move(showRecordMenu)); // [1] 記録表示
    mainMenu_->addChild(std::move(habitMenu)); // [2] 習慣管理
    
    return mainMenu_;

}
