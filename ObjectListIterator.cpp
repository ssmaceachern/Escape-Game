
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"



ObjectListIterator::ObjectListIterator(){}
ObjectListIterator::~ObjectListIterator(){}
ObjectListIterator::ObjectListIterator(const ObjectList *p_l) {
	p_list = p_l;
	first();
}


void ObjectListIterator::first() {
	index = 0;
}

void ObjectListIterator::next() {
	index++;
}

bool ObjectListIterator::isDone() {
	return index == (p_list -> count);
}

Object* ObjectListIterator::currentObject() {
	return p_list -> list[index];
}

