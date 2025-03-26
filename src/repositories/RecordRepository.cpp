#include "repositories/RecordRepository.hpp"

bool RecordRepository::load() {
    json temp;
    if (!storage_.load(temp)) {
        // ファイルが無い or エラー
        // とりあえず空にしてreturn false
        recordData_ = temp;
        return false;
    }
    recordData_ = temp;
    return true;
}

bool RecordRepository::save() {
    // weeklyData_ を保存
    return storage_.save(recordData_);
}

// 記録更新
std::string RecordRepository::updateRecord(const std::string& day,const std::string& habit, bool achieved){
    // 指定日の記録に習慣達成状況を格納
    recordData_[day][habit] = achieved; 
    // 更新データ保存
    if(storage_.save(recordData_)){
        return "success";
    }else{
        return "error_save_failed";
    }
}
//指定日の習慣達成率取得
std::string RecordRepository::getRecordsByDate(const std::string& day,json& habitsData){
    // 指定日の記録が存在しない場合、空のオブジェクト作成
    if (!recordData_.contains(day)) 
    {
        recordData_[day] = json::object();
    }
    // 記録が空の場合、エラーを返す
    if(recordData_[day].empty()){
        return "error_no_record";
    }
    // 記録データを返す
    habitsData = json(recordData_[day]);
    return "success";
}

//習慣達成率
std::string RecordRepository::getAllRecords(json& records){
    // 記録が空の場合、エラーを返す
    if(recordData_.empty())
    {
        return "error_no_record";
    }
    // 記録データを返す
    records = json(recordData_);
    return "success";
}
