#include "ObjectList.h"
#include "Object.h"
#include "ObjectListIterator.h"
#include "LogManager.h"



ObjectList::~ObjectList() {}
ObjectList::ObjectList() {
	count = 0;
}

int ObjectList::insert(Object *p_o) {
	if(isFull()) {
		return MAX_OBJECTS;
	}
	if(count==100||count==300||count==499){
		LogManager &lm = LogManager::getInstance();
		lm.writeLog("Inserted Object %d.", count);
	}
	list[count] = p_o;
	count++;
	return 0;
}

int ObjectList::remove(Object *p_o) {
	LogManager &lm = LogManager::getInstance();
	if(isEmpty()) {
		return 0;
	}


	for(int i = 0; i < count; i++) {
		if(list[i] == p_o) {
			for (int j=i; j< count - 1; j++) {
				list[j] = list[j+1];
			}
			count--;
			lm.writeLog("Removing object then count = %d.", count);
			return 1;
		}
	}
	lm.writeLog("Error: Error: no such object to be removed in the list");
	return -1;
}


bool ObjectList::isEmpty() {
	if(count <= 0) {
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("ObjectList is empty.");
	return true;
	} else {
		return false;
	}
}

bool ObjectList::isFull() {
	if(count >= MAX_OBJECTS) {
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("ObjectList is full.");
	return true;
	} else {
		return false;
	}
}

int ObjectList::getCount(void) {
	return count;
}

void ObjectList::clear() {
	count = 0;
}