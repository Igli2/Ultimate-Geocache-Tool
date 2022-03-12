#pragma once

#include <string>
#include <sstream>
#include <iomanip>

const std::string month_names[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

struct time {
    unsigned short year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
};

std::string month_to_string(unsigned short month);

std::string time_to_string(struct time t);