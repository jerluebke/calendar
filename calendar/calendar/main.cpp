// TODO:
// Ausgabe der Termine mit lambda realisieren (Code reuse)
// Einlesen der Daten von der Konsole (1, 6) als eigene Funktion schreiben
// Header aufräumen
//
// TESTEN!


#include "Event.h"
#include "conv_util.h"
#include <string>
#include <ctime>
#include <map>
#include <iostream>
#include <functional>
#include <algorithm>
#include <ios>
#include <regex>
#include <vector>
#include <utility>
#include <limits>


// Nachrichten
std::string gruss =
    "+++++++++++++Kalender+++++++++++"
    "\nFunktionen:"
    "\n\tErstellen eines neuen Termins:             1"
    "\n\tAusgabe aller Termine:                     2"
    "\n\tAusgabe vergangener Termine:               3"
    "\n\tAusgabe zukuenftiger Termine:              4"
    "\n\tAusgabe der Termine eines Datums:          5"
    "\n\tAusgabe der Termine einer Zeitspanne:      6"
    "\n\tKalender beenden:                          7"
    "\n\n";
std::string INPUT_INVALID = "Eingabe nicht unterstuetzt!\n";
std::string ADDED = "Termin wurde hinzugefuegt!\n";
std::string NOT_ADDED = "Es wurde kein Termin hinzugefuegt!\n";
std::string PROMPT = "Fuer beenden: 7 zurueck zum Kalender: 0\n";
std::string TOO_EARLY =
    "Ungueltige Eingabe: "
    "Endpunkt vor Startpunkt oder Startpunkt vor 01/01/1970!";
std::string NO_TITLE = "Ungueltige Eingabe: Kein Titel!";
std::string ENTER_DATE = "Gebe ein Datum ein (dd/mm/yyyy): ";
std::string ENTER_TIME = "Gebe eine Uhrzeit ein (hh:mm): ";
std::string ENTER_ENDDATE = "Gebe das Enddatum ein (dd/mm/yyyy): ";
std::string ENTER_ENDTIME = "Gebe eine Uhrzeit des Enddatums ein (hh:mm): ";



void error(std::string msg)
{
    system("cls");
    std::cout << msg << "\n\n" << std::endl;
}

void invalidInput(std::string msg = "")
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<int>::max());
    error(INPUT_INVALID.append(msg));
}

void promptForDate(time_t storage, std::string datetime="",
        std::string MSG_DATE="", std::string MSG_TIME="")
{
    std::string date = "";
    std::cout << MSG_DATE;
    std::cin >> date;
    // std::cout << std::endl;
    if (datetime == "")
    {
        std::cout << MSG_TIME;
        std::cin >> datetime;
    }
    storage = stringToTime(date, datetime);
}



int main() {

	std::map<time_t, Event> Calender;
	time_t now;
	time(&now);


	std::vector<std::string> Dates = {
	 "24/12/2017", "00:00",
	 "25/12/2017", "00:00",
	 "23/07/2017", "10:00",
	 "30/07/2017", "10:00",
	 "25/03/2019", "20:00",
	 "26/03/2019", "03:00",
	 "17/01/2019", "10:00",
	 "17/01/2019", "11:00",
	 "01/05/2018", "13:00",
	 "01/05/2018", "17:00",
	 "01/05/2018", "10:00",
	 "01/05/2018", "12:00",
	 "06/03/2018", "09:00",
	 "06/03/2018", "17:00", };
	std::vector<time_t> tp;

	for (size_t i = 0; i < Dates.size()-1; i+=2) {

		tp.push_back(stringToTime(Dates[i], Dates[i+1]));
	}

	Calender.insert(std::pair<time_t, Event>(tp[0], Event(tp[0], tp[1], "Jesus Birthday")));
	Calender.insert(std::pair<time_t, Event>(tp[2], Event(tp[2], tp[3], "Urlaub am Nordpol")));
	Calender.insert(std::pair<time_t, Event>(tp[4], Event(tp[4], tp[5], "Sophies Geburtstagsparty")));
	Calender.insert(std::pair<time_t, Event>(tp[6], Event(tp[6], tp[7], "Friseur")));
	Calender.insert(std::pair<time_t, Event>(tp[8], Event(tp[8], tp[9], "Pippi Langstrumpf zu Besuch")));
	Calender.insert(std::pair<time_t, Event>(tp[10], Event(tp[10], tp[11], "Klausur")));
	Calender.insert(std::pair<time_t, Event>(tp[12], Event(tp[12], tp[13], "C++")));


	// std::string n;
    char n;
	bool beendet = false;

	std::string title;
	time_t startPoint;
	time_t endPoint;


	while (beendet == false) {
        system("cls");
		std::cout << gruss;
		std::cin >> n;


        if (n == '1') {

			try {
			    std::cin.exceptions(std::ios::failbit);

				std::cout << "Titel des Termins: ";
				getchar();
				std::getline(std::cin, title);
				std::cout << std::endl;

                promptForDate(startPoint, "", ENTER_DATE, ENTER_TIME);
                promptForDate(endPoint, "", ENTER_ENDDATE, ENTER_ENDTIME);

                std::cout << std::endl;
			}
			catch (std::ios_base::failure & exc) {
                invalidInput();
                continue;
			}
            catch (std::invalid_argument &exc) {
                invalidInput(exc.what());
                continue;
            }

			if (endPoint < startPoint || startPoint == -1) {
                invalidInput(TOO_EARLY);
                continue;
			}
			else if (title == "") {
                invalidInput(NO_TITLE);
                continue;
			}

            bool valid_event = true;

            //check if there is already an event:
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

            if (valid_event) {
                Calender.insert(std::pair<time_t,
                        Event>(startPoint, Event(startPoint, endPoint, title)));
                std::cout << ADDED << PROMPT;
                std::cin >> n;
            }
            else {
                std::cout << NOT_ADDED << PROMPT;
                std::cin >> n;
            }
		}


		else if (n == '2') {

			std::cout << "Alle gespeicherten Termine:\n";

			for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {
				std::cout << timeToString(it->first) << '\t';
                std::cout << it->second.get_title() << std::endl;
			}

			std::cout << PROMPT;
			std::cin >> n;

		}


        else if (n == '3') {

			std::cout << "Alle vergangenen Termine:\n";

			for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it->first < now; ++it) {
				if (it->second.get_endPoint() < now) {
					std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl;
				}
			}

			std::cout << PROMPT;
			std::cin >> n;

		}


		else if (n == '4') {

			std::cout << "Alle zukuenftigen Termine:\n";

			for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {
				if (it->first > now) {
					std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl;
				}
			}

			std::cout << PROMPT;
			std::cin >> n;

		}


		else if (n == '5') {

            try {
			    std::cin.exceptions(std::ios::failbit);
                promptForDate(startPoint, "00:01", ENTER_DATE);
            }
			catch (std::ios_base::failure & exc) {
                invalidInput();
                continue;
			}
            catch (std::invalid_argument &exc) {
                invalidInput(exc.what());
                continue;
            }

            struct tm start_tm = *localtime(&startPoint);
            struct tm end_tm = start_tm;
            end_tm.tm_sec += 86398;        // endPoint: date-23:59
            endPoint = std::mktime(&end_tm);

			std::cout << std::endl;

            int n_events = 0;
            for (std::map<time_t, Event> ::iterator it = Calender.begin();
                    it != Calender.end(); ++it) {

                if (it->first >= startPoint && it->first <= endPoint) {
                    std::cout << timeToString(it->first) << '\t';
                    std::cout << it->second.get_title() << std::endl << std::endl;
                    n_events++;
                }
            }

			std::cout << n_events << " an diesem Tag\n";

			std::cout << PROMPT;
			std::cin >> n;

		}

		else if (n == '6') {

			try {
			    std::cin.exceptions(std::ios::failbit);

                promptForDate(startPoint, "", ENTER_DATE, ENTER_TIME);
                promptForDate(endPoint, "", ENTER_ENDDATE, ENTER_ENDTIME);

                std::cout << std::endl;
			}
			catch (std::ios_base::failure & exc) {
                invalidInput();
                continue;
			}
            catch (std::invalid_argument &exc) {
                invalidInput(exc.what());
                continue;
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

            std::cout << n_events << " in dieser Zeitspanne!\n";

			std::cout << PROMPT;
			std::cin >> n;

		}


		if (n == '7')
			beendet = true;

        else if (n == '0')
            continue;

		else
            error("Keine gueltige Eingabe!\n");

	}


	system("pause");

}

