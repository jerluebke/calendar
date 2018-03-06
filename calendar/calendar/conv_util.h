#pragma once

#include <ctime>
#include <string>
#include <regex>
#include <functional>

std::time_t stringToTime (std::string input);

std::string timeToString (std::time_t time);

std::function<bool(std::string)> make_checker(std::regex re);

//bool check_dateformat()
