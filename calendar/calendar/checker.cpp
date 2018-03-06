#include "checker.h"

// Common regex as global variables
std::regex reD("\\d+");

// utility function for converting string to int
// without error-checking!
int strToInt(std::string arg)
{
    int i;
    std::istringstream ss(arg);
    ss >> i;
    return i;
}


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
std::function<bool(std::string, std::vector<const int>)> inputIsValid(
        std::function<bool(std::string)> checker,
        std::function<bool(std::vector<const int>)> inRange)
{
    return [checker, inRange](std::string input, std::vector<const int> tokens)
    {
        if (!checker(input))
            return false;
        if (inRange(tokens))
            return true;
        return false;
    };
}
