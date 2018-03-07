
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




            int n_events = 0;
            for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {

                if (it->first >= startPoint && it->first <= endPoint) {
                    std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl << std::endl;
                    n_events++;
                }
            }



            int n_events = 0;
            for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {
                if (it->first >= startPoint && it->first <= endPoint) {
                    std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl << std::endl;
                    n_events++;
                }
            }

