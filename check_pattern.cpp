#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>


int strToInt(std::string arg)
{
    int i;
    std::istringstream ss(arg);
    ss >> i;
    return i;
}

int main()
{
    // std::string input = "03/25/2001-12:54";
    std::string input = "03/25/1989-12:54";

    std::regex re("\\d{2}/\\d{2}/\\d{4}-\\d{2}:\\d{2}");
    if (std::regex_match(input, re))
        std::cout << "success!" << std::endl;
    else
        std::cout << "failure!" << std::endl;

    // std::regex re4d("\\d\\d\\d\\d", std::regex_constants::ECMAScript);
    std::regex re4d("[\\d]{4}", std::regex_constants::ECMAScript);
    std::smatch match4d;
    std::regex_search(input, match4d, re4d);
    int year = strToInt(match4d.str());
    input = std::regex_replace(input, re4d, "");
    std::cout << year << std::endl;
    std::cout << input << std::endl;


    std::vector<int> dateTokens;

    std::regex re2d("[\\d]{2}", std::regex_constants::ECMAScript);
    std::smatch match2d;


    while (std::regex_search(input, match2d, re2d))
    {
        dateTokens.push_back(strToInt(match2d.str()));
        input = match2d.suffix().str();
    }

    for (int i: dateTokens)
        std::cout << i << std::endl;

}
