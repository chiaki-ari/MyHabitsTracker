#include "utils/DateUtils.hpp"
#include <ctime>
#include <iomanip>   // for std::get_time
#include <sstream>   // for std::istringstream
#include <ctime>     // for std::tm, std::mktime, std::strftime
#include <stdexcept>

time_t DateUtils::getCurrentTime() {
    return std::time(nullptr);
}

std::string DateUtils::getTodayDate() {
    time_t now = getCurrentTime();
    tm* localT = std::localtime(&now);
    char buf[16];
    sprintf(buf, "%04d-%02d-%02d", localT->tm_year + 1900, localT->tm_mon + 1, localT->tm_mday);
    return std::string(buf);
}

std::string DateUtils::getYesterdayDate() {
    time_t now = getCurrentTime();
    now -= 24 * 3600;
    tm* localT = std::localtime(&now);
    char buf[16];
    sprintf(buf, "%04d-%02d-%02d", localT->tm_year + 1900, localT->tm_mon + 1, localT->tm_mday);
    return std::string(buf);
}


std::string DateUtils::shiftDate(const std::string& dateStr, long days) {
    time_t preDate = parseDate(dateStr);
    preDate = preDate + (days * 24 * 3600);
    tm* localT = std::localtime(&preDate);
    char buf[16];
    sprintf(buf, "%04d-%02d-%02d", localT->tm_year + 1900, localT->tm_mon + 1, localT->tm_mday);
    return std::string(buf);
}

std::string DateUtils::shiftMonth(int &year, int &month, long shiftMonth) {
    int newYear = year;
    int newMonth = month;
    // 月数を加算
    long totalMonths = (newYear * 12) + newMonth + shiftMonth;
    newYear = totalMonths / 12;
    newMonth = (totalMonths % 12);
    // 月が0の場合、前の年の12月に調整
    if (newMonth == 0) {
        newYear--;
        newMonth = 12;
    }
    // 結果を文字列に変換して代入
    year = newYear;
    month = newMonth;
    return "success";
}

bool DateUtils::isValidDate(const std::string& s) {
    std::regex re(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(s, re);
}

time_t DateUtils::parseDate(const std::string& dateStr) {
    int y, m, d;
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &y, &m, &d) != 3) {
        return (time_t)0;
    }
    std::tm tm_ = {};
    tm_.tm_year = y - 1900;
    tm_.tm_mon  = m - 1;
    tm_.tm_mday = d;
    return std::mktime(&tm_);
}

std::vector<std::string> DateUtils::getSortedDateKeys(const json& data) {
    std::vector<std::string> dates;
    for (auto& [dateKey, _] : data.items()) {
        dates.push_back(dateKey);
    }
    std::sort(dates.begin(), dates.end());
    return dates;
}

void DateUtils::getCurrentYearMonth(int& year, int& month) {
    time_t now = getCurrentTime();
    struct tm* t = localtime(&now);
    year = t->tm_year + 1900;
    month = t->tm_mon + 1;
}

bool DateUtils::isSameYearMonth(const std::string& date, int year, int month) {
    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3) {
        return false;
    }
    return y == year && m == month;
}

void DateUtils::getYearAndMonth(const std::string& dateStr, int& year, int& month) {
    int y, m, d;
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &y, &m, &d) != 3) {
        // 解析に失敗した場合の処理
        //std::cerr << "Invalid date format." << std::endl;
        return;
    }
    year = y;
    month = m;
}

std::string DateUtils::formatDate(time_t time){
    struct tm* timeInfo = localtime(&time);
    char buffer[11]; // "YYYY-MM-DD\0" の長さ
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeInfo);
    return std::string(buffer);
}

// タイムスタンプを文字列として取得する関数
std::string DateUtils::getCurrentTimestamp() {
    time_t now = std::time(nullptr);
    struct tm* timeInfo = std::localtime(&now);
    char buffer[20]; // "YYYY-MM-DD HH:MM:SS\0" の長さ
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return std::string(buffer);
}

int DateUtils::getWeekNumber(const std::string &dateStr)
{
    // 1) parseDate() で柔軟に"YYYY-M-D"などを解析
    time_t t = parseDate(dateStr);
    if (t <= 0) {
        return 0;
    }
    // 2) ISO週番号をstrftime("%V")で取得
    char buffer[3];
    std::strftime(buffer, sizeof(buffer), "%V", std::localtime(&t));
    return std::stoi(buffer); // 01~53
}

std::string DateUtils::getWeekStartDate(const std::string &anyDateOfWeek)
{
    time_t t = parseDate(anyDateOfWeek);
    if (t <= 0) return anyDateOfWeek; // fallback

    std::tm *lt = std::localtime(&t);
    int wday = lt->tm_wday; // 日曜=0, 月曜=1, ...
    // 月曜始まりにしたい => wday=1が週開始
    int offset = (wday == 0) ? 6 : (wday - 1); 
    t -= offset * 24 * 3600; // 月曜に合わせる
    return formatDate(t);
}

std::string DateUtils::getWeekEndDate(const std::string &anyDateOfWeek)
{
    std::string start = getWeekStartDate(anyDateOfWeek);
    time_t startT = parseDate(start);
    startT += 6 * 24 * 3600; // +6日で週末(日曜)
    return formatDate(startT);
}
// 日付差分を計算する関数
int DateUtils::getDateDifference(const std::string& date1, const std::string& date2) {
    time_t time1 = parseDate(date1);
    time_t time2 = parseDate(date2);
    
    // 日付差分を秒単位で取得し、日単位に変換
    double differenceInSeconds = std::difftime(time1, time2);
    int differenceInDays = static_cast<int>(std::abs(differenceInSeconds) / 86400);
    return differenceInDays;
}
// 指定された年と月の最初の日を取得する関数
std::string DateUtils::getMonthStartDate(int year, int month) {
    std::string start = std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-01";
    return start;
}
// 指定された年と月の最後の日を取得する関数
std::string DateUtils::getMonthEndDate(int year, int month) {
    int lastDay = getLastDayOfMonth(year, month);
    std::string end = std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-" + std::to_string(lastDay);
    return end;
}
// 月の最後の日を取得する関数
int DateUtils::getLastDayOfMonth(int year, int month) {
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return 29; // うるう年
        } else {
            return 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30; // 4月、6月、9月、11月は30日
    } else {
        return 31; // それ以外の月は31日
    }
}
// 日付を比較する関数
bool DateUtils::isStartDateLater(const std::string& startDateStr, const std::string& endDateStr) {
    try {
        if (startDateStr > endDateStr) return true;
        return false;
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid date format.");
    }
}