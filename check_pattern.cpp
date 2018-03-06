#include "calendar/calendar/conv_util.h"
#include <iostream>
#include <vector>


// int strToInt(std::string arg)
// {
//     int i;
//     std::istringstream ss(arg);
//     ss >> i;
//     return i;
// }
//
// int main()
// {
//     // std::string input = "03/25/2001-12:54";
//     std::string input = "03/25/1989-12:54";
//
//     std::regex re("\\d{2}/\\d{2}/\\d{4}-\\d{2}:\\d{2}");
//     if (std::regex_match(input, re))
//         std::cout << "success!" << std::endl;
//     else
//         std::cout << "failure!" << std::endl;
//
//     // std::regex re4d("\\d\\d\\d\\d", std::regex_constants::ECMAScript);
//     std::regex re4d("[\\d]{4}", std::regex_constants::ECMAScript);
//     std::smatch match4d;
//     std::regex_search(input, match4d, re4d);
//     int year = strToInt(match4d.str());
//     input = std::regex_replace(input, re4d, "");
//     std::cout << year << std::endl;
//     std::cout << input << std::endl;
//
//
//     std::vector<int> dateTokens;
//
//     std::regex re2d("[\\d]{2}", std::regex_constants::ECMAScript);
//     std::smatch match2d;
//
//
//     while (std::regex_search(input, match2d, re2d))
//     {
//         dateTokens.push_back(strToInt(match2d.str()));
//         input = match2d.suffix().str();
//     }
//
//     for (int i: dateTokens)
//         std::cout << i << std::endl;
//
// }

int main()
{
    std::vector<std::string> dates = {
        "03/11/1989",
        "03-11-1989",
        "03.11.1989",
        "03111989",
        "3.1.1989",
        "something else...",
        "1989.89.23",
        "19991-2-432",
    };
    std::vector<std::string> times = {
        "19.55",
        "19:55",
        "19-55",
        "1955",
        "19 55",
        "312",
        "some string which is not a time",
        "789123",
        "312-43",
    };
    std::regex dateRe("(\\d{1,2}[^[:alnum:]]){2}\\d{4}");
    std::regex timeRe("\\d{1,2}[^[:alnum:]]\\d{1,2}");
    std::regex reD("\\d+");
    auto checkDate = make_checker(dateRe);
    auto checkTime = make_checker(timeRe);
    for (std::string d: dates)
    {
        std::cout << d << std::boolalpha << checkDate(d) << std::endl;
        if (checkDate(d))
        {
            std::smatch sm;
            while (std::regex_search(d, sm, reD))
            {
                std::cout << sm.str() << std::endl;
                d = sm.suffix().str();
            }
        }
    }
    for (std::string t: times)
        std::cout << t << std::boolalpha << checkTime(t) << std::endl;
}
