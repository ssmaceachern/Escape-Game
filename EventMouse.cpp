#include "Event.h"
#include "EventMouse.h"


EventMouse::EventMouse(){}

void EventMouse::setMouseAction(enum MouseActionList new_mouse_action) {
	mouse_action = new_mouse_action;
	return;
}

enum MouseActionList EventMouse::getMouseAction(){
	return mouse_action;
}

void EventMouse::setMouseX(int new_x){
	mouse_x = new_x;
	return;
}

void EventMouse::setMouseY(int new_y){
	mouse_y = new_y;
	return;
}


int EventMouse::getMouseX(){
	return mouse_x;
}

int EventMouse::getMouseY(){
	return mouse_y;
}