#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include "getDate.hpp"

std::string getCurrentDate() {
    // Get the current time as a time_point
    auto now = std::chrono::system_clock::now();

    // Convert to time_t, which represents the time in seconds since epoch
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert to a tm structure for local time
    std::tm* now_tm = std::localtime(&now_time_t);

    // Extract year, month, day, hours, and minutes
    int year = now_tm->tm_year + 1900; // tm_year is years since 1900
    int month = now_tm->tm_mon + 1;    // tm_mon is months since January (0-11)
    int day = now_tm->tm_mday;
    int hours = now_tm->tm_hour;
    int minutes = now_tm->tm_min;

    std::stringstream buff;

    // Output the date and time
    buff << year << "/" << month << "/" << day << ", " << hours << ":" << minutes;

    std::string ret;
    getline(buff, ret);

    return ret;
}