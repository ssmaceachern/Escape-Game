#include "Event.h"
#include "EventCollision.h"
#include "Object.h"



EventCollision::EventCollision(Object *p_o1, Object *p_o2, Position p) {
	setObject1(p_o1);
	setObject2(p_o2);
	setPosition(p);
}

EventCollision::EventCollision() {
	setPosition(Position(0,0));

}

Object* EventCollision::getObject1(){
	return p_obj1;
}

Object* EventCollision::getObject2(){
	return p_obj2;
}

void EventCollision::setObject1(Object *p_new_o1){
	p_obj1 = p_new_o1;
	return;
}

void EventCollision::setObject2(Object *p_new_o2){
	p_obj2 = p_new_o2;
	return;
}

Position EventCollision::getPosition(){
	return pos;
}

void EventCollision::setPosition(Position new_pos){
	pos = new_pos;
}