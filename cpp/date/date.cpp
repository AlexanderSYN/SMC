//
// Created by AlexanderSYN on 04.04.2026.
//

#include "../../header/date/include_date.h"
#include "../../header/date/date.h"

#include <print>


///
/// @return (day of the week) month (day of the month)
///         hour:min:sec yy * (24 hour)
std::string date::local_date_and_time() {
    try {
        // current date/time based on current system
        time_t now = time(0);

        // convert now to string form
        char* dt = ctime(&now);

        return std::string(dt);

    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_LOCAL_DATE_AND_TIME] ", e.what());
    }

    return "None";
}

///
/// @return hours minutes seconds
std::string date::local_time() {
    try {
        time_t now = time(0);

        tm *ltm = localtime(&now);
        std::string t = std::format("{}:{}:{}", ltm->tm_hour, ltm->tm_min,ltm->tm_sec);

        return t;
    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_LOCAL_TIME] ", e.what());
    }
    return "None";
}
