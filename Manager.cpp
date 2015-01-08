
#include "Manager.h"
#include "ObjectList.h"
#include "LogManager.h"
#include <iostream>
#include "Object.h"
#include "ObjectListIterator.h"



Manager::~Manager() {}
Manager::Manager() {}
int Manager::startUp() {
	is_started = true;
	isStarted();
	return 0;
}
bool Manager::isStarted(){
	LogManager &lm = LogManager::getInstance();
	if (!is_started){
	lm .writeLog("Error Startup manager");
	return false;
	} else {
		lm .writeLog("Manager Starts");
		return true;
	}
}

void Manager::shutDown(){
	is_started = false;
}

int Manager::registerInterest(Object *p_go, string event_name){
	if(!isValid(event_name)){return -1;}
	LogManager &lm = LogManager::getInstance();
	for (int i =0; i<= event_list_count; i++){
		if (event[i] == event_name){
			obj_list[i].insert(p_go);
			lm.writeLog("event#%d, event_name is %s, obj#%d, ", i, event_name.c_str(), obj_list[i].getCount());
			return 0;
		}

	}
	if(event_list_count >= MAX_EVENTS){
		lm .writeLog("Event(%s) list is full", event_name.c_str());
		return 0;
	}
	event[event_list_count] = event_name;
	obj_list[event_list_count].insert(p_go);
	lm.writeLog("INSERT:event#%d, event_name is %s, obj#%d, ", event_list_count, event_name.c_str(), obj_list[event_list_count].getCount());
	event_list_count++;
	return event_list_count;
}

int Manager::unregisterInterest(Object *p_go, string event_name){
	if(!isValid(event_name)){return -1;}
	LogManager &lm = LogManager::getInstance();
	int i_count;
	for (int i =0; i<= event_list_count; i++){
		if (event[i] == event_name){
			obj_list[i].remove(p_go);
			i_count = i;
			lm.writeLog("REMOVED:event#%d, event_name is %s, obj#%d, ", i, event_name.c_str(), obj_list[i].getCount());
			if(obj_list[i_count].getCount() <= 0){
				for(int j = i_count; j < event_list_count - 1; j++) {
					obj_list[j] = obj_list[j+1];
					event[j] = event[j+1];
				}
			lm .writeLog("Event(%s) list is empty!", event_name.c_str());
			event_list_count--;
			}
			return 0;
		} else if(i == event_list_count){
			lm.writeLog("Error: no such event name:%s,", event_name.c_str());
			return -1;
		}
	}
/*	if(obj_list[i_count].getCount() <= 0){
		for(int i = i_count; i < event_list_count - 1; i++) {
			obj_list[i] = obj_list[i+1];
			event[i] = event[i+1];
			}
		lm .writeLog("Event(%s) list is empty", event_name.c_str());
		event_list_count--;
		return 0;
		}
	
	return event_list_count;*/
}

void Manager::onEvent(Event *p_event){
	LogManager &lm = LogManager::getInstance();
	//lm.writeLog("Still Running(8)");
	for (int i =0; i<= event_list_count; i++){
		//lm.writeLog("Still Running(9)");
		if(event[i] == p_event->getType()){
			//lm.writeLog("Still Running(10)---event:%s,", event[i].c_str());
			ObjectListIterator obj_i = ObjectListIterator(&obj_list[i]);
			//lm.writeLog("Still Running(11)----listcount:%d,", obj_list[i].getCount());
			obj_i.first();
			//lm.writeLog("Still Running(12)");
			while(!obj_i.isDone()){
				//lm.writeLog("Still Running(13)");
				obj_i.currentObject()->eventHandler(p_event);
				//lm.writeLog("Still Running(17)");
				obj_i.next();
				//lm.writeLog("Still Running(18)");
			}
		}
	}
}

bool Manager::isValid(string event_name){
	return false;
}