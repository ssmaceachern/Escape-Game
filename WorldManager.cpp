#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "EventStep.h"
#include "ObjectListIterator.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "Event.h"
#include "Position.h"
#include "EventStep.h"
#include "GameManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "Manager.h"
#include "PowerUp.h"
#include "Character.h"
#include "WallBox.h"


WorldManager::WorldManager() {}
WorldManager& WorldManager::getInstance() {
	static WorldManager instance;
	return instance;
}

int WorldManager::startUp() {
	return 0;
}

void WorldManager::shutDown() {
}

int WorldManager::insertObject(Object *p_go) {
	ObjectListIterator j = ObjectListIterator(&updates);
	j.first();
	while(!j.isDone()){
		if(j.currentObject() == p_go){
			return 0;
		}
		j.next();
	}
	return updates.insert(p_go);
}


int WorldManager::markForDelete(Object *p_o) {
	LogManager &lm = LogManager::getInstance();
	ObjectListIterator i = ObjectListIterator(&deletions);
	i.first();
	while (!i.isDone()) {
		if (i.currentObject() == p_o) { 
			return 0;
		}
		i.next();
	}
	deletions.insert(p_o);
	lm.writeLog("deletion member %d", deletions.getCount());
	return 0;
}


int WorldManager::removeObject(Object *p_go) {
	return updates.remove(p_go);
}



void WorldManager::update() {
	LogManager &lm = LogManager::getInstance();
	ObjectListIterator i = ObjectListIterator(&deletions);

	lm.writeLog("deletion member %d", deletions.getCount());
	while (!i.isDone()) {
		delete i.currentObject();
		i.next();
	}
	deletions.clear();
	ObjectListIterator j = ObjectListIterator(&updates);
	lm.writeLog("update member %d", updates.getCount());
	int x,y;
	while(!j.isDone()){
		x = j.currentObject() -> getXVelocityStep();
		y = j.currentObject() -> getYVelocityStep();
		if(x>0||y>0 || x<0 || y<0){
			Position old_pos = j.currentObject() -> getPosition();
			Position new_pos(old_pos.getX() + x, old_pos.getY() + y);
			moveObject(j.currentObject(), new_pos);
		}
		
		j.next();
	}
}

ObjectList WorldManager::getAllObjects(void) {
	return updates;
}

bool WorldManager::isValid(string event_name){
	if(event_name == STEP_EVENT){return false;}
	else { return true;}
}

void WorldManager::draw(void){
	ObjectListIterator i = ObjectListIterator(&updates);
	i.first();
	while(!i.isDone()){
		i.currentObject()->draw();
		i.next();
	}
	LogManager &lm = LogManager::getInstance();
}

ObjectList WorldManager::isCollision(Object *p_o, Position where){
	/*ObjectList collision_list;
	ObjectListIterator i = ObjectListIterator(&updates);
	i.first();
	while(!i.isDone()){
		Object *p_temp_o = i.currentObject();
		if(p_temp_o != p_o){
			if(positionsIntersect(p_temp_o->getPosition(), where) && p_temp_o->isSolid())
				collision_list.insert(p_temp_o);
		}
		i.next();
	}
	return collision_list;*/
}

int WorldManager::moveObject(Object *p_o, Position where){
	bool do_move;
	if(p_o->isSolid()){
		ObjectList list = isCollision(p_o, where);
		
		if(!list.isEmpty()){
			ObjectListIterator i = ObjectListIterator(&list);
			EventCollision c;

			c.setType(COLLISION_EVENT);
			c.setObject1(p_o);
			while(!i.isDone()){

				Object *p_temp_o = i.currentObject();
				c.setObject2(p_temp_o);

				c.setPosition(where);
				p_o-> eventHandler(&c);
				p_temp_o->eventHandler(&c);

				if(p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD){
					do_move = false;
				}
				i.next();
			}

			if(!do_move){
				return -1;
			}
		}
	}
	p_o->setPosition(where);
}

bool WorldManager::checkCollision(Object *p_c, Position nowP){
	GraphicsManager &gm = GraphicsManager::getInstance();
	ObjectListIterator i = ObjectListIterator(&updates);
	i.first();
	//int a = ;
	//int b = ;
	xc = p_c->getPosition().getX();
	yc = p_c->getPosition().getY();
	cvc = p_c->getCollisionValue();
	while(!i.isDone()){
		Object *p_temp_o = i.currentObject();
		if(p_temp_o != p_c && p_temp_o->getType() == "player" && p_c->getType() == "enemy"){
			xe = p_temp_o->getPosition().getX();
			ye = p_temp_o->getPosition().getY();
			if(xc>=(gm.getHorizontal() * 5) / 12 && xc<=(gm.getHorizontal() * 7) / 12)cvc+=3;
			cve = p_temp_o->getCollisionValue();
			if((xc-xe)*(xc-xe) + (yc-ye)*(yc-ye) <= (cvc+cve)*(cvc+cve)){
				Character *p_new_temp = static_cast <Character *> (p_temp_o);
				if(p_new_temp->getPower() == 1 || p_new_temp->getPower() == 2){
					return true;
				}else{
					p_new_temp->playerDie();
				}
			}
		}
		if(p_temp_o != p_c && p_temp_o->getType() == "player" && p_c->getType() == "powerup"){
			xe = p_temp_o->getPosition().getX();
			ye = p_temp_o->getPosition().getY();
			cve = p_temp_o->getCollisionValue();
			if((xc-xe)*(xc-xe) + (yc-ye)*(yc-ye) <= (cvc+cve)*(cvc+cve)){
				PowerUp *p_new_c = static_cast <PowerUp *> (p_c);
				Character *p_new_temp = static_cast <Character *> (p_temp_o);
				int power = p_new_c->getPower();
				p_new_temp->setPower(power);
				if(power == 0){
					GameManager::getInstance().setGameStep(15);
					return true;
				}else return true;
			}
		}
		if(p_temp_o != p_c && p_temp_o->getType() == "WallBox" && p_c->getType() == "player"){
			WallBox *p_temp_e = static_cast <WallBox *> (p_temp_o);
			xe = p_temp_o->getPosition().getX();
			ye = p_temp_o->getPosition().getY();
			if(ye <= yc && yc <= ye + p_temp_e->getHeight() && xc >= xe && xc <= xe+ p_temp_e->getWidth())return true;	
		}
		i.next();
		}
	return false;
	}
