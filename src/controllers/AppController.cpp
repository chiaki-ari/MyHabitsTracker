#include "controllers/AppController.hpp"
#include "menus/LeafMenu.hpp"
#include "model/UserManager.hpp"

AppController::AppController(I18nManager &i18nMgr,
                             InputManager &inputMgr,
                             OutputManager &outputMgr,
                             LogManager &logMgr /* ,
                              MessageHelper &messageHlpr */
                             )
    : i18nMgr_(i18nMgr),
      inputMgr_(inputMgr),
      outputMgr_(outputMgr),
      logMgr_(logMgr) /* ,
       messageHlpr_(messageHlpr) */
{
    // コンストラクタ本体で依存オブジェクトを生成
}

void AppController::initialize()
{
    UserManager::getInstance().loadUserList();
    // コンストラクタ外で初期化処理を呼ぶ
    switchUserFlow();
}
void AppController::switchUserFlow()
{
    auto &userManager = UserManager::getInstance();
    std::string selectedUser;
    while (true)
    {
        //outputMgr_.printSubMenu("User list");

        outputMgr_.printLine();
        // ユーザー一覧表示
        const auto &users = userManager.getUserList();
        for (size_t i = 0; i < users.size(); ++i)
        {
            outputMgr_.print(std::to_string(i + 1) + ". " + users[i], true);
        }
        // if (InputProcessor::shouldReturnToMenu(userInput, i18nMgr_.getText("back_to_menu")))
        // {
        //     return -1;
        // }
        // 入力プロンプト
        outputMgr_.printInput(i18nMgr_.getText("select_user_prompt"), false);
        selectedUser = inputMgr_.getStringInput().value_or("");
        // 入力が空ならエラーメッセージ表示
        if (selectedUser.empty())
        {
            outputMgr_.printError(i18nMgr_.getText("error_invalid_number"));
            continue;
        }
        // 番号として解釈できるかチェック
        try
        {
            int selectedIndex = std::stoi(selectedUser);
            if (selectedIndex >= 1 && selectedIndex <= static_cast<int>(users.size()))
            {
                selectedUser = users[selectedIndex - 1];
                outputMgr_.printProcessing(i18nMgr_.getText("switching_user_prompt") + selectedUser);
                userManager.switchUser(selectedUser);
                break;
            }
        }
        catch (...)
        {
            // 数字でない場合は無視して新規ユーザー名として扱う
        }

        // 新規ユーザーとして登録
        outputMgr_.printProcessing(i18nMgr_.getText("creating_new_user_prompt") + selectedUser);
        userManager.switchUser(selectedUser);
        break;
    }
    switchUser(userManager.getCurrentUser());
    outputMgr_.printNewLine();
}
void AppController::switchUser(const std::string &UserId)
{
    userId_ = UserId;
    // Init storages
    initStorages();
    // Init repositories
    initRepositories();
    // Init controllers
    initControllers();
}
void AppController::run()
{
    bool running = true;
    while (running)
    {
        // メインメニューを構築し、実行
        mainMenu_ = buildMainMenu();
        MenuResult res = mainMenu_->execute();
        /* if (res == MenuResult::SWITCH_USER)
        {
            switchUserFlow();
        }
        else  */if (res == MenuResult::EXIT)
        {
            running = false;
        }
    }
}

void AppController::initStorages()
{
    // フォルダ分け: e.g. "data/userA/"
    std::string basePath = "data/" + userId_ + "/";

    // フォルダの作成を試みる
    bool result = std::filesystem::create_directories(basePath);

    habitFile_ = basePath + "habits.json";
    recordFile_ = basePath + "records.json";
    weeklyFile_ = basePath + "weekly_summary.json";

    // JsonFileStorageの実体を unique_ptr で保持
    habitStorage_ = std::make_unique<JsonFileStorage>(habitFile_);
    recordStorage_ = std::make_unique<JsonFileStorage>(recordFile_);
    weeklyStorage_ = std::make_unique<JsonFileStorage>(weeklyFile_);

}

void AppController::initRepositories()
{
    // HabitRepository と RecordRepository に各ストレージをDI
    habitRepo_ = std::make_unique<HabitRepository>(*habitStorage_);
    recordRepo_ = std::make_unique<RecordRepository>(*recordStorage_);
    weeklyRepo_ = std::make_unique<WeeklySummaryRepository>(*weeklyStorage_);

    // Load them
    habitRepo_->load();
    recordRepo_->load();
    weeklyRepo_->load(); // optional
}

void AppController::initControllers()
{
    // コントローラに Repository/Manager, 各種Manager(メッセージ, 入出力, ログ)をDI
    habitCtrl_ = std::make_unique<HabitController>(*habitRepo_,
                                                   i18nMgr_,
                                                   inputMgr_,
                                                   outputMgr_,
                                                   logMgr_);
    recordCtrl_ = std::make_unique<RecordController>(*recordRepo_,
                                                     *weeklyRepo_,
                                                     *habitRepo_,
                                                     i18nMgr_,
                                                     inputMgr_,
                                                     outputMgr_,
                                                     logMgr_);
}

std::unique_ptr<BranchMenu> AppController::buildMainMenu()
{
    std::string menuMsg = i18nMgr_.getText("menu_title");
    auto mainMenu_ = std::make_unique<BranchMenu>(menuMsg,
                                                  branchMenuType::Main,
                                                  i18nMgr_,
                                                  inputMgr_,
                                                  outputMgr_);

    // [0] 記録更新
    std::string menuUpdateMsg = i18nMgr_.getText("menu_update_record");
    // mainMenu_->addChild(std::make_unique<LeafMenu<RecordController>>(*recordCtrl_, menuUpdateMsg, [](RecordController &rc)
    //                                                                  { rc.updateRecordsFlow(); }, i18nMgr_, outputMgr_));
    std::unique_ptr<BranchMenu> updateRecordMenu = buildUpdateRecordMenu();
    mainMenu_->addChild(std::move(updateRecordMenu));

    // [1] 記録表示
    std::unique_ptr<BranchMenu> showRecordMenu = buildShowRecordMenu();
    mainMenu_->addChild(std::move(showRecordMenu));

    // [2] 習慣管理
    std::unique_ptr<BranchMenu> habitMenu = buildHabitMenu();
    mainMenu_->addChild(std::move(habitMenu));

    return mainMenu_;
}

std::unique_ptr<BranchMenu> AppController::buildUpdateRecordMenu()
{
    // サブメニュー: 記録(3項目)
    std::string menuRecordMsg = i18nMgr_.getText("menu_update_record");
    auto updateRecordMenu = std::make_unique<BranchMenu>(menuRecordMsg,
        branchMenuType::Sub,
                                                         i18nMgr_,
                                                         inputMgr_,
                                                         outputMgr_);

    std::string recordTodayMsg = i18nMgr_.getText("record_today");
    updateRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordTodayMsg,
        leafMenuType::Update,
        [](RecordController &rc)
        { rc.updateRecordsFlow(UpdateType::Today); }, i18nMgr_, outputMgr_));
        
    std::string recordSelectDayMsg = i18nMgr_.getText("record_select_day");
    updateRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordSelectDayMsg,
        leafMenuType::Update,
        [](RecordController &rc)
        { rc.updateRecordsFlow(UpdateType::SelectedDate); }, i18nMgr_, outputMgr_));

    std::string recordOneHabitMsg = i18nMgr_.getText("record_sigle_habit");
    updateRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordOneHabitMsg,
        leafMenuType::Update,
        [](RecordController &rc)
        { rc.updateRecordsFlow(UpdateType::SpecificDateHabit); }, i18nMgr_, outputMgr_));


    // [1] 連続モード
    std::unique_ptr<BranchMenu> updateContinuousRecordMenu = buildUpdateContinuousRecordMenu();
    updateRecordMenu->addChild(std::move(updateContinuousRecordMenu));



    return updateRecordMenu;
}

std::unique_ptr<BranchMenu> AppController::buildUpdateContinuousRecordMenu()
{
    // サブメニュー: 連続記録(2項目)
    std::string menuContinuousMsg = i18nMgr_.getText("continuous_record_mode");
    auto updateContinuousRecordMenu = std::make_unique<BranchMenu>(menuContinuousMsg,
        branchMenuType::SubSub,
                                                         i18nMgr_,
                                                         inputMgr_,
                                                         outputMgr_);

    std::string recordContinuousDateMsg = i18nMgr_.getText("record_continuous_date");
    updateContinuousRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordContinuousDateMsg,
        leafMenuType::Update,
        [](RecordController &rc)
        { rc.updateRecordsFlow(UpdateType::Continuousbydate); }, i18nMgr_, outputMgr_));

    std::string recordContinuousHabitMsg = i18nMgr_.getText("record_continuous_habit");
    updateContinuousRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordContinuousHabitMsg,
        leafMenuType::Update,
        [](RecordController &rc)
        { rc.updateRecordsFlow(UpdateType::Continuousbyhabit); }, i18nMgr_, outputMgr_));

    return updateContinuousRecordMenu;
}

std::unique_ptr<BranchMenu> AppController::buildShowRecordMenu()
{
    // サブメニュー: 記録表示(5項目)
    std::string menuShowRecordMsg = i18nMgr_.getText("menu_view_record");
    auto showRecordMenu = std::make_unique<BranchMenu>(menuShowRecordMsg,
        branchMenuType::Sub,
                                                       i18nMgr_,
                                                       inputMgr_,
                                                       outputMgr_);

    std::string recordTodayMsg = i18nMgr_.getText("menu_option_show_today");
    showRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordTodayMsg,
        leafMenuType::View,
        [](RecordController &rc)
        { rc.showRecordFlow(ShowType::Today); }, i18nMgr_, outputMgr_));

    std::string recordWeekMsg = i18nMgr_.getText("menu_option_show_week");
    showRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordWeekMsg,
        leafMenuType::View,
        [](RecordController &rc)
        { rc.showRecordFlow(ShowType::LastWeek); }, i18nMgr_, outputMgr_));

    std::string recordMonthMsg = i18nMgr_.getText("menu_option_show_month");
    showRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
        *recordCtrl_, recordMonthMsg,
        leafMenuType::View,
        [](RecordController &rc)
        { rc.showRecordFlow(ShowType::ThisMonth); }, i18nMgr_, outputMgr_));

    // std::string recordSelectDayyMsg = i18nMgr_.getText("menu_option_show_selected_day");
    // showRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
    //     *recordCtrl_, recordSelectDayyMsg,
    //     leafMenuType::View,
    //     [](RecordController &rc)
    //     { rc.showRecordFlow(ShowType::SelectedDate); }, i18nMgr_, outputMgr_));

    // std::string recordSlctedWeekMsg = i18nMgr_.getText("menu_option_show_selected_week");
    // showRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
    //     *recordCtrl_, recordSlctedWeekMsg,
    //     leafMenuType::View,
    //     [](RecordController &rc)
    //     { rc.showRecordFlow(ShowType::SelectedWeek); }, i18nMgr_, outputMgr_));

    // std::string recordSlctedMonthMsg = i18nMgr_.getText("menu_option_show_selected_month");
    // showRecordMenu->addChild(std::make_unique<LeafMenu<RecordController>>(
    //     *recordCtrl_, recordSlctedMonthMsg,
    //     leafMenuType::View,
    //     [](RecordController &rc)
    //     { rc.showRecordFlow(ShowType::SelectedMonth); }, i18nMgr_, outputMgr_));

    return showRecordMenu;
}

std::unique_ptr<BranchMenu> AppController::buildHabitMenu()
{
    // サブメニュー: 習慣管理(4項目)
    std::string menuManageMsg = i18nMgr_.getText("menu_manage_habits");
    auto habitMenu = std::make_unique<BranchMenu>(menuManageMsg,
        branchMenuType::Setting,
                                                  i18nMgr_,
                                                  inputMgr_,
                                                  outputMgr_);

    std::string habitsViewMsg = i18nMgr_.getText("menu_view_habits");
    habitMenu->addChild(std::make_unique<LeafMenu<HabitController>>(
        *habitCtrl_, habitsViewMsg,
        leafMenuType::View,
        [](HabitController &hc)
        { hc.showHabitListFlow(); }, i18nMgr_, outputMgr_));

    std::string habitAddMsg = i18nMgr_.getText("menu_add_habit");
    habitMenu->addChild(std::make_unique<LeafMenu<HabitController>>(
        *habitCtrl_, habitAddMsg,
        leafMenuType::Setting,
        [](HabitController &hc)
        { hc.manageHabitFlow(HabitAction::Add); }, i18nMgr_, outputMgr_));

    std::string habitEditMsg = i18nMgr_.getText("menu_edit_habit");
    habitMenu->addChild(std::make_unique<LeafMenu<HabitController>>(
        *habitCtrl_, habitEditMsg,
        leafMenuType::Setting,
        [](HabitController &hc)
        { hc.manageHabitFlow(HabitAction::Edit); }, i18nMgr_, outputMgr_));

    std::string habitRemoveMsg = i18nMgr_.getText("menu_remove_habit");
    habitMenu->addChild(std::make_unique<LeafMenu<HabitController>>(
        *habitCtrl_, habitRemoveMsg,
        leafMenuType::Setting,
        [](HabitController &hc)
        { hc.manageHabitFlow(HabitAction::Remove); }, i18nMgr_, outputMgr_));

    return habitMenu;
}
