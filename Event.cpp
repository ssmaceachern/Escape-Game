#include "Event.h"
#include <string>


Event::Event() {
	event_type = UNDEFINED_EVENT;
}
Event::~Event(){}

void Event::setType(string new_type) {
	event_type = new_type;
}

string Event::getType(){
	return event_type;
}

