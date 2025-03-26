#include "repositories/WeeklySummaryRepository.hpp"
#include <iostream>

bool WeeklySummaryRepository::load() {
    json temp;
    if (!storage_.load(temp)) {
        weeklyData_ = temp;
        return false;
    }
    weeklyData_ = temp;
    return true;
}

bool WeeklySummaryRepository::save() {
    return storage_.save(weeklyData_);
}

void WeeklySummaryRepository::setWeeklyData(const json &data) {
    weeklyData_ = data;
}

void WeeklySummaryRepository::getWeeklyData(json &out) const {
    out = weeklyData_;
}