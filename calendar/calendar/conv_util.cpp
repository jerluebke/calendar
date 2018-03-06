#pragma warning(disable:4996)

#include "conv_util.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>


// Common regex as global variables
std::regex reD("\\d+");
std::regex dateRe("(\\d{1,2}[^[:alnum:]]){2}\\d{4}");
std::regex timeRe("\\d{1,2}[^[:alnum:]]\\d{1,2}");


int strToInt(std::string arg)
{
    int i;
    std::istringstream ss(arg);
    ss >> i;
    return i;
}


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



std::function<bool(std::string)> make_checker(std::regex re)
{
    return [re](std::string target)
    {
        return std::regex_match(target, re);
    };
}


/**
 *  @Parameters : String, which is assumed to consisting of digits
 *  @Returns : Vector containing the digit-sequences of the input string
 */
std::vector<const int> get_tokens(std::string input)
{
    std::vector<const int> token;
    std::smatch sm;
    while (std::regex_search(input, sm, reD))
    {
        token.push_back(strToInt(sm.str()));
        input = sm.suffix().str();
     }
    return token;
}


std::function<bool(const int)> isValid(const int start, const int end)
{
    return [start, end](const int input)
    {
        return (input >= start && input <= end);
    };
}

auto hoursIsValid = isValid(0, 23);
auto minutesIsValid = isValid(0, 59);
auto yearIsValid = isValid(1970, 2050);
auto monthIsValid = isValid(1, 12);
bool dayIsValid(const int day, const int month)
{
    int end;
    if (month == 2)
        end = 28;
    else if (month % 2 == 0)
        end = 30;
    else    // month % 2 == 1
        end = 31;
    return (day > 0 && day <= end);
}

auto timeChecker = make_checker(timeRe);
auto dateChecker = make_checker(dateRe);


std::function<bool(std::string)> inputIsValid(
        std::function<bool(std::string)> checker,
        std::function<bool(std::vector<const int>)> inRange)
{
    return [checker, inRange](std::string input)
    {
        if (!checker(input))
            return false;
        std::vector<const int> tokens = get_tokens(input);
        if (inRange(tokens))
            return true;
        return false;
    };
}


bool dateInRange(std::vector<const int> tokens)
{
    return (yearIsValid(tokens[2])
            && monthIsValid(tokens[1])
            && dayIsValid(tokens[0], tokens[1]));
}


bool timeInRange(std::vector<const int> tokens)
{
    return (hoursIsValid(tokens[0]) && minutesIsValid(tokens[1]));
}


auto dateIsValid = inputIsValid(dateChecker, dateInRange);
auto timeIsValid = inputIsValid(timeChecker, timeInRange);
