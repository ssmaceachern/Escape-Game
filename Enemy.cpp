
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Enemy.h"

Enemy::Enemy(Position pos) {
	setType("Enemy");
  LogManager &lm = LogManager::getInstance();
  GraphicsManager &gm = GraphicsManager::getInstance();
  setSolidness(HARD);

  registerInterest(COLLISION_EVENT);
  registerInterest(STEP_EVENT);
  registerInterest(OUT_EVENT);
  setPosition(pos);
  //stepCounter = 0;
}

Enemy::~Enemy() {
	unregisterInterest(STEP_EVENT);
	unregisterInterest(OUT_EVENT);
	unregisterInterest(COLLISION_EVENT);
}


int Enemy::eventHandler(Event *p_e) {
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
	lm.writeLog("Enemy is doing step!!!");
    return 1;
  }

  return 0;
}


void Enemy::out(){
	GraphicsManager &gm = GraphicsManager::getInstance();
	if(getPosition().getY() > gm.getVertical()){
		WorldManager &wm = WorldManager::getInstance();
		wm.markForDelete(this);
	}
}

void Enemy::onCollision(EventCollision *p_c){
	if (((p_c -> getObject1() -> getType()) == "player") || 
      ((p_c -> getObject2() -> getType()) == "player")) {
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c -> getObject1());
		world_manager.markForDelete(p_c -> getObject2());
  }
}

void Enemy::step() {
	//if(WorldManager::getInstance().checkCollision(this, getPosition()))GameManager::getInstance().setGameOver();
	if(WorldManager::getInstance().checkCollision(this, getPosition()))WorldManager::getInstance().markForDelete(this);

}

void Enemy::draw(){}

Position Enemy::moveDX(int dx) {
  WorldManager &world_manager = WorldManager::getInstance();
  GraphicsManager &gm = GraphicsManager::getInstance();
  Position new_pos(getPosition().getX() + dx, getPosition().getY());
  return new_pos;
  /*if ((new_pos.getY() > gm.getHorizontal()) && 
      (new_pos.getY() < gm.getVertical()))
    world_manager.moveObject(this, new_pos);*/
}

Position Enemy::moveDY(int dy) {
  GraphicsManager &gm = GraphicsManager::getInstance();
  WorldManager &world_manager = WorldManager::getInstance();
  Position new_pos(getPosition().getX(), getPosition().getY() + dy);
  return new_pos;
 /* if ((new_pos.getY() > gm.getHorizontal()) && 
      (new_pos.getY() < gm.getVertical()))
    world_manager.moveObject(this, new_pos);*/
}


