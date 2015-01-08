
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Block.h"

Block::Block(bool onRight, float yVelocity) : Enemy(Position()){
  LogManager &lm = LogManager::getInstance();
  GraphicsManager &gm = GraphicsManager::getInstance();
  registerInterest(COLLISION_EVENT);
  registerInterest(STEP_EVENT);
  registerInterest(OUT_EVENT);
  setYVelocity(yVelocity);
  setType("enemy");
  onLeft = !onRight;
  if(onRight)
  setPosition(Position(((gm.getHorizontal() * 2) / 3)-1, -10));
  else setPosition(Position((gm.getHorizontal() /3)+1, -10));
  setCollisionValue(2);
}

Block::~Block() {
	unregisterInterest(STEP_EVENT);
	unregisterInterest(OUT_EVENT);
	unregisterInterest(COLLISION_EVENT);
	WorldManager &wm = WorldManager::getInstance();
	wm.removeObject(this);
}


int Block::eventHandler(Event *p_e) {
  
  if (p_e->getType() == OUT_EVENT){
	out();
	return 1;
  }

  if (p_e->getType() == COLLISION_EVENT){
	  EventCollision *p_c = static_cast <EventCollision *> (p_e);
	  onCollision(p_c);
	  return 1;
  }
 

  if (p_e->getType() == STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}


void Block::onCollision(EventCollision *p_c){
	/*Enemy::onCollision(p_c);

	LogManager &lm = LogManager::getInstance();
	if (((p_c -> getObject1() -> getType()) == "Wall") || 
      ((p_c -> getObject2() -> getType()) == "Wall")) {
		//xVelocity = -xVelocity;
		//setXVelocity(xVelocity);
		lm.writeLog("Block velocity = %f", xVelocity);
  }*/
}


void Block::out(){
	Enemy::out();
}


void Block::draw(){
	GraphicsManager &gm = GraphicsManager::getInstance();
	int x,y;
	x = this->getPosition().getX();
	y = this->getPosition().getY();
	char c = '|';
	char l = '/';
	char r = '\\';
	if(!onLeft){
		gm.drawCh(Position(x,y), c, COLOR_RED);
		gm.drawCh(Position(x,y-1), c, COLOR_RED);
		gm.drawCh(Position(x-3,y-1), c, COLOR_RED);
		gm.drawCh(Position(x-3,y), c, COLOR_RED);
		gm.drawCh(Position(x-1,y), r, COLOR_RED);
		gm.drawCh(Position(x-1,y-1), l, COLOR_RED);
		gm.drawCh(Position(x-2,y-1), r, COLOR_RED);
		gm.drawCh(Position(x-2,y), l, COLOR_RED);
	}else{
		gm.drawCh(Position(x,y), c, COLOR_RED);
		gm.drawCh(Position(x,y-1), c, COLOR_RED);
		gm.drawCh(Position(x+3,y-1), c, COLOR_RED);
		gm.drawCh(Position(x+3,y), c, COLOR_RED);
		gm.drawCh(Position(x+1,y), l, COLOR_RED);
		gm.drawCh(Position(x+1,y-1), r, COLOR_RED);
		gm.drawCh(Position(x+2,y-1), l, COLOR_RED);
		gm.drawCh(Position(x+2,y), r, COLOR_RED);
	}


}