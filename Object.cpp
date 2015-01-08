#include "LogManager.h"
#include "Object.h"
#include "WorldManager.h"
#include "Event.h"
#include "Position.h"
#include "GameManager.h"
#include "EventStep.h"
#include "InputManager.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "EventOut.h"
#include <math.h>
#include "GraphicsManager.h"
#include "WorldManager.h"


Object::Object() {
	pos = Position(); 
	event_count = 0;
	WorldManager::getInstance().insertObject(this);
}

Object::~Object() {
	int eventCount = event_count;
	for (int index = 0; index <= eventCount - 1; index++){
		unregisterInterest(event_name[0]);}
	WorldManager &wm = WorldManager::getInstance();
	wm.removeObject(this);
}

void Object::setType(string new_type) {
	type = new_type;
}

string Object::getType() {
	return type;
}

void Object::setPosition(Position new_pos) {
	pos.setXY(new_pos.getX(), new_pos.getY());
}

Position Object::getPosition(){
	return pos;
}

int Object::eventHandler(Event *p_event) {
	LogManager &lm = LogManager::getInstance();
	if (p_event->getType() == STEP_EVENT)WorldManager::getInstance().insertObject(this);
	if (p_event->getType() == OUT_EVENT)WorldManager::getInstance().markForDelete(this);
	if (p_event->getType() == MOUSE_EVENT){
		EventMouse* k_event = static_cast<EventMouse*>(p_event);
		setPosition(Position(k_event->getMouseX(), k_event->getMouseY()));
		lm .writeLog("X = %d,Y = %d", k_event->getMouseX(),k_event->getMouseY());
	}
	if (p_event->getType() == KEYBOARD_EVENT){
		EventKeyboard* k_event = static_cast<EventKeyboard*>(p_event);
		if(k_event->getKey() == 'q')
			GameManager::getInstance().setGameOver();
		else if(k_event->getKey() == 'a'){
			setPosition(Position(pos.getX() - 1, pos.getY()));
		}else if(k_event->getKey() == 'd'){
			setPosition(Position(pos.getX() + 1, pos.getY()));
		}else if(k_event->getKey() == 'w'){
			setPosition(Position(pos.getX(), pos.getY()-1));
		}else if(k_event->getKey() == 's'){
			setPosition(Position(pos.getX(), pos.getY()+1));
		}
	}
	if (p_event->getType() == COLLISION_EVENT)WorldManager::getInstance().markForDelete(this);
	return 0;
}

int Object::registerInterest(string event){
	LogManager &lm = LogManager::getInstance();
	if(event_count == MAX_OBJ_EVENTS){
		return -1;}

	if(event == STEP_EVENT){
		lm .writeLog("GameManager---register");
		event_name[event_count] = event;
		GameManager &gm = GameManager::getInstance();
		gm.registerInterest(this, event);
	} else if(event == MOUSE_EVENT || event == KEYBOARD_EVENT){
		event_name[event_count] = event;
		lm .writeLog("InputManager---register");
		InputManager::getInstance().registerInterest(this, event);
	} else {
		event_name[event_count] = event;
		lm .writeLog("WorldManager---register");
		WorldManager &wm = WorldManager::getInstance();
		wm.registerInterest(this, event);
	}
	event_count++;
	return 0;
}

int Object::unregisterInterest(string event){
	LogManager &lm = LogManager::getInstance();
	bool found = false;
	int temp_count;
	for (int index = 0; index <= event_count; index++){
		if (event_name[index] == event){
			temp_count = index;
			found = true;
		}
	}
	if(!found){return -1;}

	if(event == STEP_EVENT){
		GameManager &gm = GameManager::getInstance();
		gm.unregisterInterest(this, event);
	} if(event == MOUSE_EVENT || event == KEYBOARD_EVENT){
		InputManager::getInstance().unregisterInterest(this, event);
	}  else {
		WorldManager &wm = WorldManager::getInstance();
		wm.unregisterInterest(this, event);
	}
		for(int i = temp_count; i <= event_count; i++) {
			event_name[i] = event_name[i+1];
		}

	event_count--;
	return 0;
}

void Object::setXVelocity(float new_x_velocity){
	x_velocity = new_x_velocity;
	return;
}

void Object::setYVelocity(float new_y_velocity){
	y_velocity = new_y_velocity;
	return;
}


float Object::getXVelocity(){
	return x_velocity;
}

float Object::getYVelocity(){
	return y_velocity;
}


int Object::getXVelocityStep(){
	if (x_velocity == 0)
		return 0;
	x_velocity_countdown -= x_velocity;
	if (x_velocity_countdown == 0)
		return 0;
	int spaces = floor(1 - x_velocity_countdown);
	x_velocity_countdown = 1 + fmod(x_velocity_countdown, 1);

	if(x_velocity > 0){
		return spaces;
	} else {
		return -1 * spaces;
	}
}


int Object::getYVelocityStep(){
	if (y_velocity == 0)
		return 0;
	y_velocity_countdown -= y_velocity;
	if (y_velocity_countdown == 0)
		return 0;
	int spaces = floor(1 - y_velocity_countdown);
	y_velocity_countdown = 1 + fmod(y_velocity_countdown, 1);

	if(y_velocity > 0){
		return spaces;
	} else {
		return -1 * spaces;
	}
}

void Object::draw(){
	
}

bool Object::isSolid(){
	if(solidness == HARD || solidness == SOFT){
		return true;
	} else {
		return false;
	}
}


int Object::setSolidness(Solidness new_solid){
	solidness = new_solid;
	return 0;
}


Solidness Object::getSolidness(){
	return solidness;
}

void Object::setCollisionValue(int cValue){
	collisionValue = cValue;
}

int Object::getCollisionValue(){
	return collisionValue;
}