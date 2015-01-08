
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ObjectFactory.h"
#include "WallManager.h"
#include "Bouncer.h"
#include "Block.h"
#include "Rounder.h"
#include "Character.h"
#include "WallBox.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "PowerUp.h"

ObjectFactory::ObjectFactory() {
  registerInterest(STEP_EVENT);
  stepCounter = -300;
  isCreated = false;
}

ObjectFactory::~ObjectFactory() {
	unregisterInterest(STEP_EVENT);
}


int ObjectFactory::eventHandler(Event *p_e) {

  if (p_e->getType() == STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}



void ObjectFactory::step() {
	stepCounter++;
	if(stepCounter > -10 && stepCounter == 0){
		if(!isCreated){
			new Character;
			stepCounter = stepCounter + 10;
			isCreated = true;
			return;
		}
	}
	if(stepCounter >= 120 && stepCounter <= 125){
		rand2 = random() % 2;
		if(rand2)newBlock();
		else if(random() %2)newBouncer();
		else newRounder();
		new WallBox(20, 0.5f);
		new PowerUp();
		return;
	}
	if(stepCounter >= 200 && stepCounter <= 205){
		rand2 = random() % 2;
		if(rand2)newBlock();
		rand2 = random() % 2;
		if(rand2)newBouncer();
		else newRounder();
		return;
	}
	if(stepCounter >= 280 && stepCounter <= 285){
		rand2 = random() % 2;
		if(rand2)newBlock();
		if(!random()%4)newWallBox();
		rand2 = random() % 2;
		if(rand2)newBouncer();
		else newRounder();
		return;
	}
	if(stepCounter >= 360 && stepCounter <= 365){
		rand2 = random() % 2;
		if(rand2)newBlock();
		rand2 = random() % 2;
		if(rand2)newBouncer();
		else newRounder();
		return;
	}
	if(stepCounter >= 420 && stepCounter <= 425){
		rand2 = random() % 4;
		if(!rand2)newWallBox();
		else stepCounter=0;
		return;
	}
}

void ObjectFactory::newBlock(){
		rand2 = random() % 2;
		rand3 = random() % 3 + 1;
		new Block(rand2, (float)0.5 * rand3);
		stepCounter += 6;
		return;
}

void ObjectFactory::newRounder(){
		GraphicsManager &gm = GraphicsManager::getInstance();
		rand3 = random() % 3 + 1;
		rand2 = random() % 2 + 1;
		new Rounder(Position((gm.getHorizontal() /3)+10,-30), rand3, rand2);
		stepCounter += 6;
		return;
}

void ObjectFactory::newBouncer(){
		GraphicsManager &gm = GraphicsManager::getInstance();
		rand3 = random() % 3 + 1;
		new Bouncer(Position((gm.getHorizontal() /3)+10,-30), rand3);
		stepCounter += 6;
		return;
}

void ObjectFactory::newWallBox(){
		GraphicsManager &gm = GraphicsManager::getInstance();
		rand3 = random() % 3 + 1;
		new WallBox(rand3*7,0.5f);
		stepCounter = 0;
		return;
}