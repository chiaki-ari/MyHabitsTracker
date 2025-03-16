#ifndef APP_CONTROLLER_HPP
#define APP_CONTROLLER_HPP

#include "menus/TrackerMenu.hpp"
#include "model/HabitTracker.hpp"
#include "model/HabitListManager.hpp"

class AppController
{
public:
  // コンストラクタで各クラスを初期化
  AppController(
      const std::string &habitListFile,
      const std::string &dataFile,
      MessageManager &messageManager,
      InputManager &inputManager,
      OutputManager &outputManager)
      : habitListManager_(
          habitListFile, 
          messageManager, 
          inputManager, 
          outputManager),
        habitTracker_(
          dataFile, 
          habitListManager_, 
          messageManager, 
          inputManager, 
          outputManager),
        messageManager_(messageManager), // 参照を初期化
        inputManager_(inputManager),     // 参照を初期化
        outputManager_(outputManager)    // 参照を初期化
  {
  }
  void run();

private:
  void chooseLang();
  std::unique_ptr<TrackerMenu> mainMenu_;
  std::unique_ptr<TrackerMenu> buildMenu(); // メニュー構築を分離

  HabitListManager habitListManager_;
  HabitTracker habitTracker_;

  MessageManager &messageManager_;
  InputManager &inputManager_;
  OutputManager &outputManager_;
};

#endif // APP_CONTROLLER_HPP