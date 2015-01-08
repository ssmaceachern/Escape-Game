
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Rounder.h"


Rounder::Rounder(Position pos, int hVelocity, int vVelocity) : Enemy(pos) {
  LogManager &lm = LogManager::getInstance();
  GraphicsManager &gm = GraphicsManager::getInstance();
  registerInterest(COLLISION_EVENT);
  registerInterest(STEP_EVENT);
  registerInterest(OUT_EVENT);
  setType("enemy");
  setYVelocity(0.5f);
  xVelocity = hVelocity;
  yVelocity = vVelocity;
  setPosition(pos);
  status = 0;
  yCounter = 0;
  setCollisionValue(2);
  frameCounter = 0;
}

Rounder::~Rounder() {
	unregisterInterest(STEP_EVENT);
	unregisterInterest(OUT_EVENT);
	unregisterInterest(COLLISION_EVENT);
	WorldManager &wm = WorldManager::getInstance();
	wm.removeObject(this);
}


int Rounder::eventHandler(Event *p_e) {
  
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


void Rounder::onCollision(EventCollision *p_c){
	/*Enemy::onCollision(p_c);

	LogManager &lm = LogManager::getInstance();
	if (((p_c -> getObject1() -> getType()) == "Wall") || 
      ((p_c -> getObject2() -> getType()) == "Wall")) {
		//xVelocity = -xVelocity;
		//setXVelocity(xVelocity);
		lm.writeLog("Rounder velocity = %f", xVelocity);
  }*/
}

void Rounder::step() {
	LogManager &lm = LogManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	if(status == 0 || status == 2){
		if(getPosition().getX() >= ((gm.getHorizontal() * 2) / 3)-4 || getPosition().getX() <= (gm.getHorizontal() /3)+4){
			xVelocity = -1 * xVelocity;
			status++;
		}
	}
	if(status >= 3 || status == 1){
		yCounter++;
		if(yCounter >= 10){
			yVelocity = -1 * yVelocity;
			status++;
			yCounter = 0;
			if(status >= 4)status =0;
		}
	}
	Enemy::step();
	if(status >= 3){
		Position new_pos = Enemy::moveDY(yVelocity);
		setPosition(new_pos);
		return;
	} 
	if(status >= 2){
		Position new_pos = Enemy::moveDX(xVelocity);
		setPosition(new_pos);
		return;
	} 
	if(status >= 1){
		Position new_pos = Enemy::moveDY(yVelocity);
		setPosition(new_pos);
		return;
	} 
	if(status >= 0){
		Position new_pos = Enemy::moveDX(xVelocity);
		setPosition(new_pos);
		return;
	}
	
}

void Rounder::out(){
	Enemy::out();
}


void Rounder::draw(){
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