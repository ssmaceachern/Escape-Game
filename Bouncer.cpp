
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Bouncer.h"

Bouncer::Bouncer(Position pos, int hVelocity) : Enemy(pos) {
  LogManager &lm = LogManager::getInstance();
  GraphicsManager &gm = GraphicsManager::getInstance();
  registerInterest(COLLISION_EVENT);
  registerInterest(STEP_EVENT);
  registerInterest(OUT_EVENT);
  setYVelocity(0.5f);
  setType("enemy");
  xVelocity = hVelocity;
  setPosition(pos);
  setCollisionValue(2);
  frameCounter = 0;
}

Bouncer::~Bouncer() {
	unregisterInterest(STEP_EVENT);
	unregisterInterest(OUT_EVENT);
	unregisterInterest(COLLISION_EVENT);
	WorldManager &wm = WorldManager::getInstance();
	wm.removeObject(this);
}


int Bouncer::eventHandler(Event *p_e) {
  
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


void Bouncer::onCollision(EventCollision *p_c){
	/*Enemy::onCollision(p_c);

	LogManager &lm = LogManager::getInstance();
	if (((p_c -> getObject1() -> getType()) == "Wall") || 
      ((p_c -> getObject2() -> getType()) == "Wall")) {
		//xVelocity = -xVelocity;
		//setXVelocity(xVelocity);
		lm.writeLog("Bouncer velocity = %f", xVelocity);
  }*/
}

void Bouncer::step() {
	LogManager &lm = LogManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	if(getPosition().getX() >= ((gm.getHorizontal() * 2) / 3)-3 || getPosition().getX() <= (gm.getHorizontal() /3)+3){
		xVelocity = -1 * xVelocity;
	}
	Enemy::step();
	Position new_pos = Enemy::moveDX(xVelocity);
	setPosition(new_pos);
}

void Bouncer::out(){
	Enemy::out();
}


void Bouncer::draw(){
	frameCounter++;
	GraphicsManager &gm = GraphicsManager::getInstance();
	int x,y;
	x = this->getPosition().getX();
	y = this->getPosition().getY();
	char c = 'X';
	char l = '/';
	char r = '\\';
	char l1 = '|';
	char r1 = '-';
	if(frameCounter >= 16){
		gm.drawCh(Position(x,y), c, COLOR_RED);
		gm.drawCh(Position(x+1,y+1), r, COLOR_RED);
		gm.drawCh(Position(x-1,y-1), r, COLOR_RED);
		gm.drawCh(Position(x+1,y-1), l, COLOR_RED);
		gm.drawCh(Position(x-1,y+1), l, COLOR_RED);
		frameCounter = 0;
	}else{
		gm.drawCh(Position(x,y), c, COLOR_RED);
		gm.drawCh(Position(x+1,y), r1, COLOR_RED);
		gm.drawCh(Position(x-1,y), r1, COLOR_RED);
		gm.drawCh(Position(x,y-1), l1, COLOR_RED);
		gm.drawCh(Position(x,y+1), l1, COLOR_RED);
	}

}