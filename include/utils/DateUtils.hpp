#ifndef DATEUTILS_HPP
#define DATEUTILS_HPP

#include <string>
#include <vector>
#include <regex>
#include "json.hpp"

using json = nlohmann::json;

class DateUtils
{
public:
    static DateUtils &getInstance()
    {
        static DateUtils instance;
        return instance;
    }

    time_t getCurrentTime();

    //std::string getNextDate(const std::string& dateStr);
    std::string shiftDate(const std::string& dateStr, long days);
    std::string getTodayDate();
    std::string getYesterdayDate();

    bool isValidDate(const std::string& s);
    time_t parseDate(const std::string& dateStr);
    std::vector<std::string> getSortedDateKeys(const nlohmann::json& data);

    void getCurrentYearMonth(int& year, int& month);
    bool isSameYearMonth(const std::string& date, int year, int month);
    std::string formatDate(time_t time);
    
    std::string getCurrentTimestamp();
    int getDateDifference(const std::string& date1, const std::string& date2);
    int getWeekNumber(const std::string &dateStr);
    // 週の開始/終了日を求めたいなら optional
    std::string getWeekStartDate(const std::string &anyDateOfWeek);
    std::string getWeekEndDate(const std::string &anyDateOfWeek);
    std::string shiftMonth(int &year, int &month, long shiftMonth) ;

    std::string getMonthStartDate(int year, int month);
    std::string getMonthEndDate(int year, int month);

    void getYearAndMonth(const std::string& dateStr, int& year, int& month);

    
bool isStartDateLater(const std::string& startDateStr, const std::string& endDateStr) ;
private:
    DateUtils() {} // コンストラクタを private に
    DateUtils(const DateUtils &) = delete;
    DateUtils &operator=(const DateUtils &) = delete;

    
    int getLastDayOfMonth(int year, int month);
};
#endif // DATEUTILS_HPP
