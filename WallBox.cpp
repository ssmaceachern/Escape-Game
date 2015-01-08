
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "WallBox.h"

WallBox::WallBox(int new_height, float yVelocity) : Enemy(Position()){
  LogManager &lm = LogManager::getInstance();
  GraphicsManager &gm = GraphicsManager::getInstance();
  registerInterest(COLLISION_EVENT);
  registerInterest(STEP_EVENT);
  registerInterest(OUT_EVENT);
  setYVelocity(yVelocity);
  setType("WallBox");
  width = ((gm.getHorizontal() * 7) / 12) - ((gm.getHorizontal() * 5) / 12) - 2;
  height = new_height;
  setPosition(Position(((gm.getHorizontal() * 5) / 12)+1, -30));
  setCollisionValue(2);
}

WallBox::~WallBox() {
	unregisterInterest(STEP_EVENT);
	unregisterInterest(OUT_EVENT);
	unregisterInterest(COLLISION_EVENT);
	WorldManager &wm = WorldManager::getInstance();
	wm.removeObject(this);
}


int WallBox::eventHandler(Event *p_e) {
  
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


void WallBox::onCollision(EventCollision *p_c){
	/*Enemy::onCollision(p_c);

	LogManager &lm = LogManager::getInstance();
	if (((p_c -> getObject1() -> getType()) == "Wall") || 
      ((p_c -> getObject2() -> getType()) == "Wall")) {
		//xVelocity = -xVelocity;
		//setXVelocity(xVelocity);
		lm.writeLog("WallBox velocity = %f", xVelocity);
  }*/
}


void WallBox::out(){
	Enemy::out();
}


void WallBox::draw(){
	GraphicsManager &gm = GraphicsManager::getInstance();
	int x,y;
	x = this->getPosition().getX();
	y = this->getPosition().getY();
	char s = 'H';
	char t = 'A';
	char b = 'V';
	for (int i = 1; i <= width; i++){
		gm.drawCh(Position(x+i,y), t, COLOR_RED);
		gm.drawCh(Position(x+i,y + height), b, COLOR_RED);
	}
	for (int i = 1; i <= height-1; i++){
		gm.drawCh(Position(x,y+i), s, COLOR_YELLOW);
		gm.drawCh(Position(x+width,y+i), s, COLOR_YELLOW);
	}


}


int WallBox::getHeight(){
	return height;
}

int WallBox::getWidth(){
	return width;
}