#include "conv_util.h"


// Common regex as global variables
std::regex reD("\\d+");
std::regex dateRe("(\\d{1,2}[^[:alnum:]]){2}\\d{4}");
std::regex timeRe("\\d{1,2}[^[:alnum:]]\\d{1,2}");


/**
 *  makes a function for checking whether a string fits a regex
 *  @Params : regex for string to compare to
 *  @Returns : function, which takes a string as input and returns whether it
 *      fits the regex
 */
std::function<bool(std::string)> make_checker(std::regex re)
{
    return [re](std::string target)
    {
        return std::regex_match(target, re);
    };
}


/**
 *  @Parameters : String, which is assumed to be consisting of digits
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


/**
 *  @Params : two ints denoting an intervall in which some value is said to be
 *      valid
 *  @Returns : a function, which takes an int as input and returns whether it
 *      is valid
 */
std::function<bool(const int)> isValid(const int start, const int end)
{
    return [start, end](const int input)
    {
        return (input >= start && input <= end);
    };
}


/**
 *  @Params : a checker function and a inRange function
 *  @Returns : a function taking a string as input and returning whether it is
 *      valid according to the tow provided checkers
 */
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


// make inputIsValid functions, pooling above information
auto dateIsValid = inputIsValid(dateChecker, dateInRange);
auto timeIsValid = inputIsValid(timeChecker, timeInRange);
