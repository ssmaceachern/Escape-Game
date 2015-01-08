
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "PowerUp.h"
#include <stdlib.h>
#include <time.h>

PowerUp::PowerUp() {
  LogManager &lm = LogManager::getInstance();
  GraphicsManager &gm = GraphicsManager::getInstance();

  registerInterest(COLLISION_EVENT);
  registerInterest(STEP_EVENT);
  registerInterest(OUT_EVENT);
  setYVelocity(1.0f);
  rand = random() %10 -4;
  setPosition(Position((gm.getHorizontal()/2) + rand, -30));
  setType("powerup");
  rand = random()%3;
  if(!rand)color=COLOR_YELLOW;
  if(rand==1)color=COLOR_GREEN;
  if(rand==2)color=COLOR_MAGENTA;
  setCollisionValue(3);
  stepCounter = 0;
  dead = false;
}

PowerUp::~PowerUp() {
	unregisterInterest(STEP_EVENT);
	unregisterInterest(OUT_EVENT);
	unregisterInterest(COLLISION_EVENT);
}


int PowerUp::eventHandler(Event *p_e) {
	LogManager &lm = LogManager::getInstance();
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


void PowerUp::out(){
	GraphicsManager &gm = GraphicsManager::getInstance();
	if(getPosition().getY() > gm.getVertical()){
		WorldManager &wm = WorldManager::getInstance();
		wm.markForDelete(this);
	}
}

void PowerUp::onCollision(EventCollision *p_c){
	if (((p_c -> getObject1() -> getType()) == "player") || 
      ((p_c -> getObject2() -> getType()) == "player")) {
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c -> getObject1());
		world_manager.markForDelete(p_c -> getObject2());
  }
}

void PowerUp::step() {
	if(dead)drawE();
	if(WorldManager::getInstance().checkCollision(this, getPosition())){
		dead = true;
		stepCounter = 0;
	}
}

void PowerUp::draw(){
	if(dead)return;
	stepCounter++;
	GraphicsManager &gm = GraphicsManager::getInstance();
	int x,y;
	x = this->getPosition().getX();
	y = this->getPosition().getY();
	char c[3];
	c[0]= '2';
	c[1]= 'X';
	c[2]= 'S';
	char s = '|';
	char t = '_';
	if(stepCounter >= 32){
		stepCounter = 0;
	}else {
		if(rand == 0){
				gm.drawCh(Position(x,y), c[rand], color);
				gm.drawCh(Position(x+1,y), s, color);
				gm.drawCh(Position(x-1,y), s, color);
				gm.drawCh(Position(x,y-1), t, color);
		} else if(rand == 1){
				gm.drawCh(Position(x,y), c[rand], color);
				gm.drawCh(Position(x+1,y), s, color);
				gm.drawCh(Position(x-1,y), s, color);
				gm.drawCh(Position(x,y-1), t, color);
		} if(rand == 2){
				gm.drawCh(Position(x,y), c[rand], color);
				gm.drawCh(Position(x+1,y), s, color);
				gm.drawCh(Position(x-1,y), s, color);
				gm.drawCh(Position(x,y-1), t, color);
		}
	}

}

int PowerUp::getPower(){
	return rand;
}

void PowerUp::drawE(){
	GraphicsManager &gm = GraphicsManager::getInstance();
	stepCounter++;
	int x,y;
	x = this->getPosition().getX();
	y = this->getPosition().getY();
	char h = '*';
	char d = '.';
	if(stepCounter >= 20){
		WorldManager::getInstance().markForDelete(this);
		return;
	}
	if(stepCounter >= 15){
		gm.drawCh(Position(x+2,y-1), h, color);
		gm.drawCh(Position(x+2,y-1), h, color);
		gm.drawCh(Position(x-2,y), h, color);
		return;
	}
	if(stepCounter >= 10){
		gm.drawCh(Position(x+1,y+1), h, color);
		gm.drawCh(Position(x-1,y+1), h, color);
		gm.drawCh(Position(x-2,y), d, color);
		gm.drawCh(Position(x+2,y), h, color);
		gm.drawCh(Position(x+1,y-1), d, color);
		gm.drawCh(Position(x-1,y-1), h, color);
		return;
	}
	if(stepCounter >= 5){
		gm.drawCh(Position(x+1,y+1), h, color);
		gm.drawCh(Position(x-1,y-1), h, color);
		gm.drawCh(Position(x,y), d, color);
		gm.drawCh(Position(x+1,y-1), h, color);
		gm.drawCh(Position(x-1,y+1), d, color);
		gm.drawCh(Position(x,y-1), h, color);
		gm.drawCh(Position(x,y+1), h, color);
		gm.drawCh(Position(x-1,y), h, color);
		gm.drawCh(Position(x+1,y), h, color);
		return;
	}
	gm.drawCh(Position(x,y), h, color);
	gm.drawCh(Position(x+1,y), h, color);
	gm.drawCh(Position(x-1,y), h, color);
	gm.drawCh(Position(x,y+1), h, color);
	gm.drawCh(Position(x,y-1), h, color);
}
				