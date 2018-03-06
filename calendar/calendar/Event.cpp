#include "Event.h"

Event::Event(const time_t startPoint, const time_t endPoint, const std::string title) {

	m_startPoint = startPoint;
	m_endPoint = endPoint;
	m_title = title;
}

time_t Event::get_endPoint() const {

	return m_endPoint;

}
time_t Event::get_startPoint() const {

	return m_startPoint;

}

std::string Event::get_title() const {

	return m_title;
}

