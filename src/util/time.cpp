#include "time.h"

std::string month_to_string(unsigned short month) {
    if (month > 1 || month < 12) {
        return month_names[month];
    } else {
        return "?";
    }
}

std::string time_to_string(struct time t) {
    std::stringstream stream;

    stream << month_to_string(t.month) << " ";
    stream << std::setw(2) << std::setfill('0') << t.day << " ";
    stream << t.year << " ";
    stream << std::setw(2) << std::setfill('0') << t.hour << ":";
    stream << std::setw(2) << std::setfill('0') << t.minute << ":";
    stream << std::setw(2) << std::setfill('0') << t.second;

    std::string s = stream.str();
    return s;
}