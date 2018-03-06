#pragma warning(disable:4996)

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <functional>


std::time_t stringToTime (std::string input)
{
    std::tm tm = {};
    std::istringstream ss(input);
    ss >> std::get_time(&tm, "%d/%m/%Y-%H:%M");
    if (ss.fail())
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



std::function<std::regex(std::string)> make_regex(std::string fmt)
{
    return [fmt](std::string target)
        {
            std::regex_match(target, std::regex(fmt));
        };
}
