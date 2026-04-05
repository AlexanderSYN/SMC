//
// Created by AlexanderSYN on 04.04.2026.
//

#ifndef DATE_H
#define DATE_H

#include "include_date.h"

struct time {
    int tm_sec;   // seconds of minutes from 0 to 61
    int tm_min;   // minutes of hour from 0 to 59
    int tm_hour;  // hours of day from 0 to 24
    int tm_mday;  // day of month from 1 to 31
    int tm_mon;   // month of year from 0 to 11
    int tm_year;  // year since 1900
    int tm_wday;  // days since sunday
    int tm_yday;  // days since January 1st
    int tm_isdst; // hours of daylight savings time
};

namespace date {
    std::string local_time();
    std::string local_date_and_time();
}

#endif //DATE_H
