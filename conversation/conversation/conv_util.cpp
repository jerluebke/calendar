#pragma warning(disable:4996)

#define _XOPEN_SOURCE
#include <time.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>


std::time_t stringToTime (std::string input)
{
    std::tm tm = {};
    // std::istringstream ss(input);
    // ss >> std::get_time(&tm, "%d/%m/%Y-%H:%M");
    char cinput[1024];
    strncpy(cinput, input.c_str(), sizeof(cinput));
    cinput[sizeof(cinput) - 1] = 0;
    char *returnvalue = strptime(cinput, "%d/%m/%Y-%H:%M", &tm);
    // if (ss.fail())
    if (returnvalue == NULL)
        throw std::invalid_argument("Date format not understood");
    std::time_t time = mktime(&tm);
    return time;
}

std::string timeToString (std::time_t time)
{
    std::tm *tm = std::localtime(&time);
    char buffer[256];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y-%H:%M", tm);
    std::string output(buffer);
    return output;
}
