#pragma once
#include <ctime>
#include <string>

class Event {

public:

	Event(const time_t startPoint, const time_t endPoint, const std::string title);

	time_t get_endPoint() const;
	time_t get_startPoint() const;
	std::string get_title() const;


private:

    const time_t m_startPoint;
    const time_t m_endPoint;
    const std::string m_title;
	// const time_t m_duration;

};
