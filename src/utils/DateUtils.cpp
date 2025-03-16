#include "utils/DateUtils.hpp"
#include <ctime>

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

time_t DateUtils::getCurrentTime() {
    return std::time(nullptr);
}

std::string DateUtils::formatDate(time_t time){
    struct tm* timeInfo = localtime(&time);
    char buffer[11]; // "YYYY-MM-DD\0" の長さ
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeInfo);
    return std::string(buffer);
}