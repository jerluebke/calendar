#pragma once

#include <string>
#include <functional>
#include <regex>
#include <vector>

int strToInt(std::string arg);
std::function<bool(std::string)> make_checker(std::regex re);
std::vector<const int> get_tokens(std::string input);
std::function<bool(const int)> isValid(const int start, const int end);
std::function<bool(std::string, std::vector<const int>)> inputIsValid(
        std::function<bool(std::string)> checker,
        std::function<bool(std::vector<const int>)> inRange);
