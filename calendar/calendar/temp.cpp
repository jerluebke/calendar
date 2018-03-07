// TODO:
// einbinden in main

#include <algorithm>


            for (std::map<time_t, Event> ::iterator it = Calender.begin();
                it != Calender.end(); ++it) {

                if ((it->second.get_startPoint() < startPoint
                            && it->second.get_endPoint() > startPoint)
                    && (it->second.get_startPoint() < endPoint
                        && it->second.get_endPoint() > endPoint)
                    && (it->second.get_startPoint() > startPoint
                        && it->second.get_endPoint() < endPoint)) {

                    std::string msg =
                        "Es existiert bereits ein Termin in diesem Zeitraum!\n"
                        + it->second.get_title() + ": "
                        + timeToString(it->second.get_startPoint()) + " - "
                        + timeToString(it->second.get_endPoint()) + "\n";
                    valid_event = false;
                    error(msg);
                    break;

                }
            }


//---------------------------------------------------------------------------------
        // print-if

			for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {
				std::cout << timeToString(it->first) << '\t';
                std::cout << it->second.get_title() << std::endl;
			}



			for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it->first < now; ++it) {
				if (it->second.get_endPoint() < now) {
					std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl;
				}
			}



			for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {
				if (it->first > now) {
					std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl;
				}
			}


std::function make_printer<void(void)> (
        std::map<time_t, Event> &map,
        std::function<bool(std::pair<time_t, Event>&)> for_cond,
        std::function<bool(std::pait<time_t, Event>&)> if_cond)
{
    return [&map, for_cond, if_cond](void)
    {
        for (*map::iterator it = Calender.begin(); for_cond(it); ++it)
        {
            if (if_cond(it))
                printer(it);
        }
    };
}

auto all_for = [&Calender](std::pair<time_t, Event> &pair)
{
    return (pair != Calender->end());
};
auto all_if = [](std::pair<time_t, Event> &pair) { return true; };
auto until_now_for = [now](std::pair<time_t, Event> &pair)
{
    return (pair->first < now);
};
auto until_now_if = [now](std::pair<time_t, Event> &pair)
{
    return (pair->second.get_endPoint() < now);
};
auto since_now = [now](std::pair<time_t, Event> &pair)
{
    return (pair->first > now);
};


auto print_all = make_printer(all_for, all_if);
auto print_until = make_printer(until_now_for, until_now_if);
auto print_since = make_printer(all_for, since_now);
// call with `print_all(Calendar)`

//--------------------------------------------------------------------------------
    // conting elements

            int n_events = 0;
            for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {

                if (it->first >= startPoint && it->first <= endPoint) {
                    std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl;
                    n_events++;
                }
            }

        int n_events = count_if (Calender.begin(), Calender.end(),
                [](std::pair<time_t, Event> &pair)
                    {
                        if (pair->first >= startPoint && pair->first <= endPoint)
                        {
                            printer(pair);
                            return true;
                        }
                        return false;
                    });

//------------------------------------------------------------------------------------
    // util

        auto printer = [](std::pair<time_t, Event> &pair)
        {
            std::cout << timeToString(pair->first) << '\t';
            std::cout << pair->second.get_title() << std::endl;
        };
