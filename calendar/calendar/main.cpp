#include "Event.h"
#include "conv_util.h"
#include <string>
#include <ctime>
#include <map>
#include<iostream>
#include<functional>
#include<algorithm>
#include<ios>
#include <regex>
#include <vector>
#include <utility>


std::function<void(void)> make_printAllEvents(std::map<time_t, Event> m) {

	return [m](void) {
		std::for_each(m.begin(), m.end(), []( const std::pair<time_t, Event> &pair) {

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

//std::regex re("\\d{2}/\\d{2}/\\d{4}-\\d{2}:\\d{2}");
//
//std::function<void(void)> make_checkFormat(std::regex re) {
//
//	return[re](void){
//		if (std::regex_match(date.begin(), date.end(), re) && std::regex_match(date_end.begin(), date_end.end(), re)) { return true }
//		else {
//			std::cout << "Ungueltiges Datumsformat!" << std::endl;
//			return false;
//
//
//auto check_format = [re](std::string date, std::string date_end) {
//std::cmatch m;
//
//
//}};


int main() {

	std::map<time_t, Event> Calender;
	time_t now;
	time(&now);

	

	std::vector<std::string> Dates = {
	"24/12/2017-00:00",
	 "25/12/2017-00:00",
	 "23/07/2017-10:00",
	 "30/07/2017-10:00",
	 "25/03/2019-20:00",
	 "26/03/2019-03:00",
	 "17/01/2019-10:00",
	 "17/01/2019-11:00",
	 "01/05/2018-13:00",
	 "01/05/2018-17:00",
	 "01/05/2018-10:00",
	 "01/05/2018-12:00",
	 "06/03/2018-09:00",
	 "06/03/2018-17:00", };
	std::vector<time_t> tp;

	for (int i = 0; i < Dates.size(); ++i) {

		tp.push_back(stringToTime(Dates[i]));
	}

	Calender.insert(std::pair<time_t, Event>(tp[0], Event(tp[0], tp[1], "Jesus Birthday")));
	Calender.insert(std::pair<time_t, Event>(tp[2], Event(tp[2], tp[3], "Urlaub am Nordpol")));
	Calender.insert(std::pair<time_t, Event>(tp[4], Event(tp[4], tp[5], "Sophies Geburtstagsparty")));
	Calender.insert(std::pair<time_t, Event>(tp[6], Event(tp[6], tp[7], "Friseur")));
	Calender.insert(std::pair<time_t, Event>(tp[8], Event(tp[8], tp[9], "Pippi Langstrumpf zu Besuch")));
	Calender.insert(std::pair<time_t, Event>(tp[10], Event(tp[10], tp[11], "Klausur")));
	Calender.insert(std::pair<time_t, Event>(tp[12], Event(tp[12], tp[13], "C++")));

	auto printAllEvents = make_printAllEvents(Calender);

	std::string n;
	bool beendet = false;

	std::string date = "";
	time_t startPoint;
	std::string title;
	std::string date_end;
	time_t endPoint;


	while (beendet == false) {
		std::cout << "----Kalender----------- \nFunktionen:\nErstellen eines neuen Termins: 1 \nAusgabe aller Termine: 2 \nAusgabe vergangener Termine: 3 \nAusgabe zukuenftiger Termine: 4 \nAusgabe der Termine eines Datums: 5 \nAusgabe der Termine einer Zeitspanne: 6\nKalender beenden: 7\n\n";
		std::cin >> n;


		if (n == "1") {

			bool valid_input = true;

			try {

				std::cin.exceptions(std::ios::failbit);

				std::cout << "Titel des Termins: ";
				getchar();
				std::getline(std::cin, title);
				std::cout << std::endl;
				std::cout << "Eingabe von Datum und Uhrzeit (dd/mm/yyyy-hh:mm)" ;
				std::cin >> date;
				std::cout << "Eingabe von End-Datum und Uhrzeit (dd/mm/yyyy-hh:mm)";
				std::cin >> date_end;
				
			}
			catch (std::ios_base::failure & exc) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max());
				std::cout << "Falsche Eingabe!" << std::endl;
				valid_input = false;
			}

			//check format:
			std::regex re("\\d{2}/\\d{2}/\\d{4}-\\d{2}:\\d{2}");
			std::cmatch m;
			if (std::regex_match(date.begin(), date.end(), re) && std::regex_match(date_end.begin(), date_end.end(), re)) {}
			else {
				std::cout << "Ungueltiges Datumsformat!" << std::endl;
				valid_input = false;

			}

			//string to time:
			try {
				startPoint = stringToTime(date); 
				endPoint = stringToTime(date_end);
			}
			catch (std::invalid_argument &exc) {

				std::cerr << exc.what() << std::endl;
				valid_input = false;
			}

			
			if (endPoint < startPoint || startPoint == -1) {

				valid_input = false;
				std::cerr << "Ungueltige Eingabe: Endpunkt vor Startpunkt oder Startpunkt vor 01/01/1970!" << std::endl;
			}
			else if (title == "") {
				valid_input = false;
				std::cerr << "Ungueltige Eingabe: Kein Titel!" << std::endl;
			}
			
			if(valid_input == true){

				bool valid_event = true;


				//check if there is already an event:
				for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it) {

					if (it->second.get_startPoint() < startPoint && it->second.get_endPoint() > startPoint) {

						std::cout << "Es existiert bereits ein Termin in diesem Zeitraum!" << std::endl;
						std::cout << it->second.get_title() << ": " << timeToString(it->second.get_startPoint()) << " - " << timeToString(it->second.get_endPoint()) << std::endl;
						valid_event = false;
						break;

					}
					else if (it->second.get_startPoint() < endPoint && it->second.get_endPoint() > endPoint) {

						std::cout << " Es existiert bereits ein Termin in diesem Zeitraum!\n" << std::endl;
						std::cout << it->second.get_title() << ": " << timeToString(it->second.get_startPoint()) << " - " << timeToString(it->second.get_endPoint()) << std::endl;
						valid_event = false;
						break;
					}
					else if (it->second.get_startPoint() > startPoint && it->second.get_endPoint() < endPoint) {

						std::cout << " Es existiert bereits ein Termin in diesem Zeitraum!\n"  << std::endl;
						std::cout << it->second.get_title() << ": " << timeToString(it->second.get_startPoint()) << " - " << timeToString(it->second.get_endPoint()) << std::endl;
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

			/*for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it) {
				std::cout << timeToString(it->first) << '\t' << it->second.get_title() << std::endl << std::endl;
			}*/

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
				if (it->second.get_endPoint() < now) {
					std::cout << timeToString(it->first) << '\t' << it->second.get_title() << std::endl << std::endl;
				}
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
					std::cout << timeToString(it->first) << '\t' << it->second.get_title() << std::endl << std::endl;
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
			std::cout << std::endl;
			//check format:
			std::regex re("\\d{2}/\\d{2}/\\d{4}");
			std::cmatch m;
			if (std::regex_match(date.begin(), date.end(), re) ) {

				date_end = date;
				date.append("-00:01");
				date_end.append("-23:59");

				try {
					startPoint = stringToTime(date);
					endPoint = stringToTime(date_end);
				}
				catch (std::invalid_argument &exc) {

					std::cerr << exc.what() << std::endl;
				}

				int n_events = 0;
				for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it) {
					if (it->first >= startPoint && it->first <= endPoint) {
						std::cout << timeToString(it->first) << '\t' << it->second.get_title() << std::endl << std::endl;
						n_events++;
					}
				}

				std::cout << n_events << " an diesem Tag\n";
			}
			else {
				std::cout << "Ungueltiges Zeitformat!" << std::endl;
			}
			std::cout << "Fuer beenden: 7 zurueck zum Kalender: 0\n";
			std::cin >> n;
			if (n == "7") {
				beendet = true;
			}
		}
		else if (n == "6") {

			std::cout << "Eingabe des Start-Punktes: (dd/mm/yyyy-hh:mm):\n";
			std::cin >> date;

			std::cout << "Eingabe des End-Punktes: (dd/mm/yyyy-hh:mm):\n";
			std::cin >> date_end;
			std::cout << std::endl;

			//check format:
			std::regex re("\\d{2}/\\d{2}/\\d{4}-\\d{2}:\\d{2}");
			std::cmatch m;
			if (std::regex_match(date.begin(), date.end(), re) && std::regex_match(date_end.begin(), date_end.end(), re)) {


				try {
					startPoint = stringToTime(date);
					endPoint = stringToTime(date_end);
				}
				catch (std::invalid_argument &exc) {

					std::cerr << exc.what() << std::endl;
				}

				int n_events = 0;
				for (std::map<time_t, Event> ::iterator it = Calender.begin(); it != Calender.end(); ++it) {
					if (it->first >= startPoint && it->first <= endPoint) {
						std::cout << timeToString(it->first) << '\t' << it->second.get_title() << std::endl << std::endl;
						n_events++;
					}
				}

				std::cout << n_events << " in dieser Zeitspanne!\n";
			}
			else {
				std::cout << "Ungueltiges Zeitformat!" << std::endl;

			}
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


	system("pause");

}

