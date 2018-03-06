#include "Event.h"
#include "conv_util.h"
#include <string>
#include <ctime>
#include <map>
#include <iostream>
#include <functional>
#include <algorithm>
#include <ios>
#include <limits>
#include <utility>

void print_EventsOnDate(time_t date);
void print_EventsInRange(time_t begin, time_t end);

std::function<void(void)> make_printAllEvents(std::map<time_t, Event> m) {

    return [m] (void) {
        std::for_each(m.begin(), m.end(), [](const std::pair<time_t, Event> &pair) {

            std::cout << pair.second.get_startPoint() << " bis " << pair.second.get_endPoint()\
            << "\tTitle: " << pair.second.get_title() << std::endl;

        });
        };
    /*return [m]() -> void {

        for (std::map<time_t, Event>::iterator it = m.begin(); it != m.end(); ++it) {
            std::cout << it->first << '\t' << it->second.get_title() << std::endl << std::endl;
        }

    };*/

}

int main() {

	std::map<time_t, Event> Calender;
	time_t now;
	time(&now);

	std::string n;
	bool beendet = false;

	std::string date;
	time_t startPoint;
	std::string title;
	std::string date_end;
	time_t endPoint;

	//Beispiel:
	time_t timer = now + 70000;
	time_t timer2 = 200;
	Calender.insert(std::pair<time_t, Event>(timer, Event(timer, timer + 20, "Hello")));
	Calender.insert(std::pair<time_t, Event>(timer2, Event(timer2, timer2 + 40, "secondEvent")));

    auto printAllEvents = make_printAllEvents(Calender);

	while (beendet == false) {
		std::cout << "----Kalender----------- \nFunktionen:\nErstellen eines neuen Termins: 1 \nAusgabe aller Termine: 2 \nAusgabe vergangener Termine: 3 \nAusgabe zukuenftiger Termine: 4 \nAusgabe der Termine eines Datums: 5 \nAusgabe der Termine einer Zeitspanne: 6\nKalender beenden: 7\n\n";
		std::cin >> n;


		if (n == "1") {

			try {
				std::cin.exceptions(std::ios::failbit);



				std::cout << "Titel des Termins:";
				// std::cin >> title;
                std::getline(std::cin, title);

				std::cout << "Eingabe von Datum und Uhrzeit (dd/mm/yyyy-hh:mm)" ;
				// std::cin >> date;
                std::getline(std::cin, date);

				std::cout << "Eingabe von End-Datum und Uhrzeit (dd/mm/yyyy-hh:mm)";
				// std::cin >> date_end;
                std::getline(std::cin, date_end);



			}
			catch (std::ios_base::failure & exc) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max());
				std::cout << "Falsche Eingabe!" << std::endl;

			}

			startPoint = stringToTime(date); //throws exception?
			endPoint = stringToTime(date_end);
			bool valid_event = true;


			//check if there is already an event:
			for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it) {

				if (it->second.get_startPoint() < startPoint && it->second.get_endPoint() > startPoint) {

					std::cout << " Es existiert bereits ein Termin in diesem Zeitraum!" << std::endl;
					valid_event = false;
					break;

				}
				else if (it->second.get_startPoint() < endPoint && it->second.get_endPoint() > endPoint) {

					std::cout << " Es existiert bereits ein Termin in diesem Zeitraum!\n" << it->second.get_startPoint() << '\t' << it->second.get_title() << std::endl;
					valid_event = false;
					break;
				}
				else if (it->second.get_startPoint() > startPoint && it->second.get_endPoint() < endPoint) {

					std::cout << " Es existiert bereits ein Termin in diesem Zeitraum!\n" << it->second.get_startPoint() << '\t' << it->second.get_title() << std::endl;
					valid_event = false;
					break;
				}

			}

			if (valid_event) {
				Calender.insert(std::pair<time_t, Event>(startPoint, Event(startPoint, endPoint, title)));

				std::cout << "Termin wurde hinzugefuegt!\nFuer beenden: 7 zurueck zum Kalender: 0\n";
				std::cin >> n;
			}
			else {
				std::cout << "Es wurde kein Termin hinzugefuegt!\nFuer beenden: 7 zurueck zum Kalender: 0\n";
				std::cin >> n;
			}
			if (n == "7") {
				beendet = true;
			}
		}
		else if (n == "2") {

			std::cout << "Alle gespeicherten Termine:\n";

			// for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it) {
			//     std::cout << it->first << '\t' << it->second.get_title() << std::endl << std::endl;
			// }

            printAllEvents();

			std::cout << "Fuer beenden: 7 zurueck zum Kalender: 0\n";
			std::cin >> n;
			if (n == "7") {
				beendet = true;
			}
		}
		else if (n == "3") {

			std::cout << "Alle vergangenen Termine:\n";

			for (std::map<time_t, Event> ::iterator it = Calender.begin(); it->first < now; ++it) {
				std::cout << it->first << '\t' << it->second.get_title() << std::endl << std::endl;
			}

			std::cout << "Fuer beenden: 7 zurueck zum Kalender: 0\n";
			std::cin >> n;
			if (n == "7") {
				beendet = true;
			}
		}
		else if (n == "4") {

			std::cout << "Alle zukuenftigen Termine:\n";

			for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it) {
				if (it->first > now) {
					std::cout << it->first << '\t' << it->second.get_title() << std::endl << std::endl;
				}
			}

			std::cout << "Fuer beenden: 7 zurueck zum Kalender: 0\n";
			std::cin >> n;
			if (n == "7") {
				beendet = true;
			}

		}
		else if (n == "5") {

			std::cout << "Eingabe des Datums (dd/mm/yyyy):\n";
			std::cin >> date;

			std::cout << "Fuer beenden: 7 zurueck zum Kalender: 0\n";
			std::cin >> n;
			if (n == "7") {
				beendet = true;
			}
		}
		else if (n == "7") {
			beendet = true;
		}
		else {
			std::cerr << "Keine gueltige Eingabe!\n\n";
		}
	}

	/*time_t timer = now + 70000;
	time_t timer2 = 200;
	Calender.insert(std::pair<time_t, Event>(timer, Event(timer+20, "Hello")));
	Calender.insert(std::pair<time_t, Event>(timer2, Event(timer2 + 40, "secondEvent")));


	for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it){
		std::cout << it->first << '\t' << it-> second.get_title() << std::endl;
		}

	std::cout << Calender.find(timer)->second.get_title() << std::endl;*/

	system("pause");

}

