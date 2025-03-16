#ifndef DATEUTILS_HPP
#define DATEUTILS_HPP

#include <string>
#include <vector>
#include <regex>
#include "json.hpp"

using json = nlohmann::json;

class DateUtils {
public:
    static DateUtils& getInstance() {
        static DateUtils instance;
        return instance;
    }

    std::string getTodayDate();
    std::string getYesterdayDate();
    bool isValidDate(const std::string& s);
    time_t parseDate(const std::string& dateStr);
    std::vector<std::string> getSortedDateKeys(const json& data);
    void getCurrentYearMonth(int& year, int& month);
    bool isSameYearMonth(const std::string& date, int year, int month);
    time_t getCurrentTime();
    std::string formatDate(time_t time);

private:
    DateUtils() {}  // コンストラクタを private に
    DateUtils(const DateUtils&) = delete;
    DateUtils& operator=(const DateUtils&) = delete;
};
#endif // DATEUTILS_HPP
