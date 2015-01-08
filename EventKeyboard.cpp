#include "Event.h"
#include "EventKeyboard.h"



EventKeyboard::EventKeyboard() {
}

void EventKeyboard::setKey(int new_key) {
	key_val = new_key;
	return;
}

int EventKeyboard::getKey() {
	return key_val;
}