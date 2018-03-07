#pragma once

#include <string>
#include <functional>
#include <regex>
#include <vector>

std::function<bool(std::string)> make_checker(std::regex re);
std::vector<int> get_tokens(std::string input);
std::function<bool(const int)> isValid(const int start, const int end);
std::function<bool(std::string, std::vector<int>)> inputIsValid(
        std::function<bool(std::string)> checker,
        std::function<bool(std::vector<int>)> inRange);
