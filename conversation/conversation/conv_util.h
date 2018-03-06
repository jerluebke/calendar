#pragma once

#include <ctime>
#include <string>

std::time_t stringToTime (std::string input);

std::string timeToString (std::time_t time);
