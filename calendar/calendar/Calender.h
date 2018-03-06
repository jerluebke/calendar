#pragma once
#include "Event.h"
#include <string>
#include <ctime>
#include <map>
#include<iostream>

class Calender {

public:

	Calender();
	Calender(time_t timePoint, Event event);

	void print_allEvents() const;
	void print_EventsOnDate(time_t date);
	void print_EventsInRange(time_t begin, time_t end);


private:

	std::map<time_t, Event> m_Calender;
};