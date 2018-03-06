#pragma once

#include <string>
#include <ctime>

std::time_t stringToTime (std::string date, std::string time);
std::string timeToString (std::time_t time);
