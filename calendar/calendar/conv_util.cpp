#pragma warning(disable:4996)

#include "conv_util.h"
#include "checker.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>


// common regex as global variable
std::regex dateRe("(\\d{1,2}[^[:alnum:]]){2}\\d{4}");
std::regex timeRe("\\d{1,2}[^[:alnum:]]\\d{1,2}");


// make checkers (pattern according to regex)
auto timeChecker = make_checker(timeRe);
auto dateChecker = make_checker(dateRe);


// make isValid functions (value in intervall)
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


// inRange functions; checking isValid functions for all relevant tokens
bool dateInRange(std::vector<int> tokens)
{
    return (yearIsValid(tokens[2])
            && monthIsValid(tokens[1])
            && dayIsValid(tokens[0], tokens[1]));
}
bool timeInRange(std::vector<int> tokens)
{
    return (hoursIsValid(tokens[0]) && minutesIsValid(tokens[1]));
}


// make inputIsValid functions, pooling above information
auto dateIsValid = inputIsValid(dateChecker, dateInRange);
auto timeIsValid = inputIsValid(timeChecker, timeInRange);



/**
 *  @Params : two strings (date and time)
 *  @Returns : time_t object
 */
std::time_t stringToTime (std::string date, std::string time)
{
    std::vector<int> dateToken = get_tokens(date);
    std::vector<int> timeToken = get_tokens(time);
    if (!(dateIsValid(date, dateToken) && timeIsValid(time, timeToken)))
        throw std::invalid_argument("Eingabeformat des Datums nicht unterstuetzt...");

    std::stringstream ss;
    ss << dateToken[0] << "/" << dateToken[1] << "/" << dateToken[2];
    ss << "-" << timeToken[0] << ":" << timeToken[1];
    std::string datetimeString = ss.str();

    std::tm tm = {};
    std::istringstream is(datetimeString);
    is >> std::get_time(&tm, "%d/%m/%Y-%H:%M");
    const std::time_t tt = std::mktime(&tm);

    return tt;
}


/**
 *  @Params : time_t object
 *  @Returns : one datetime string
 */
std::string timeToString (std::time_t time)
{
    std::tm *tm = std::localtime(&time);
    char buffer[256];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y-%H:%M", tm);
    std::string output(buffer);
    return output;
}
