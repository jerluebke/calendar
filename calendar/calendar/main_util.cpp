#include "conv_util.h"
#include <iostream>
#include <limits>
/*
int main()
{
    while (1)
    {
        std::string input;
        std::cout << "Gib ein Datum im Format dd/mm/yyyy-hh:mm ein" << std::endl;
        std::cin >> input;
        try
        {
            std::time_t time = stringToTime(input);
            std::string output = timeToString(time);
            std::cout << "timestamp: " << time << std::endl;
            std::cout << "zurück nach String: " << output << std::endl;
        }
        catch(const std::invalid_argument &ex)
        {
            std::cerr << ex.what() << std::endl;
        }
        std::cout << "\n\n";
        std::cin.clear();
        // std::cin.ignore(std::numeric_limits<int>::max());
    }

    return 0;

}*/
