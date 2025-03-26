#ifndef APP_CONTROLLER_HPP
#define APP_CONTROLLER_HPP
#include <memory>       // for unique_ptr
#include <string>
#include "menus/BranchMenu.hpp"
#include "repositories/RecordRepository.hpp"
#include "repositories/HabitRepository.hpp"
#include "model/LogManager.hpp"
#include "controllers/RecordController.hpp"
#include "controllers/HabitController.hpp"
#include "repositories/HabitRepository.hpp"
#include "repositories/JsonFileStorage.hpp"
#include "repositories/WeeklySummaryRepository.hpp"
#include "repositories/IAppStorage.hpp"

class AppController
{
public:
  // コンストラクタで各クラスを初期化
  AppController(I18nManager &i18nMgr,
                InputManager &inputMgr,
                OutputManager &outputMgr,
                LogManager &logMgr/* ,
              MessageHelper &messageHlpr */);
  void initialize();
  void run();

private:
  std::string userId_;

  // 初期化処理を分割
  void initStorages();
  void initRepositories();
  void initControllers();

  void switchUserFlow();
  void switchUser(const std::string &newUserId);

  // メニュー構築
  std::unique_ptr<BranchMenu> buildMainMenu();
  std::unique_ptr<BranchMenu> buildUpdateRecordMenu();
  std::unique_ptr<BranchMenu> buildUpdateContinuousRecordMenu();
  std::unique_ptr<BranchMenu> buildShowRecordMenu();
  std::unique_ptr<BranchMenu> buildHabitMenu();

  // コンストラクタ引数として受け取るもの
  std::string habitFile_;
  std::string recordFile_;
  std::string weeklyFile_;
  I18nManager &i18nMgr_;
  InputManager &inputMgr_;
  OutputManager &outputMgr_;
  LogManager &logMgr_;/* 
  MessageHelper &messageHlpr_; */

  // ストレージ (抽象インタフェース)
  std::unique_ptr<IAppStorage> habitStorage_;
  std::unique_ptr<IAppStorage> recordStorage_;
  std::unique_ptr<IAppStorage> weeklyStorage_;

  // リポジトリとマネージャ (ビジネスロジック層)
  std::unique_ptr<HabitRepository> habitRepo_;
  std::unique_ptr<RecordRepository> recordRepo_;
  std::unique_ptr<WeeklySummaryRepository> weeklyRepo_ ;

  // コントローラ (UIロジック層)
  std::unique_ptr<HabitController> habitCtrl_;
  std::unique_ptr<RecordController> recordCtrl_;

   // メインメニュー
  std::unique_ptr<BranchMenu> mainMenu_;
};

#endif // APP_CONTROLLER_HPP