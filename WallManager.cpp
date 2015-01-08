#include "WallManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include <stdlib.h>
#include <time.h>

WallManager::WallManager(){
	LogManager &lm = LogManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	a = Position(gm.getHorizontal() /3 , 0);
	b = Position((gm.getHorizontal() * 2) / 3, 0);
	timer = 1;
	timerCount = 0;
	stepCounter =  0;
	registerInterest(STEP_EVENT);
	lm.writeLog("Wall manager starts succesfully!!!! ax= %d, bx = %d",a.getX(), b.getX());
	wallCounter = 0;
	isOn = true;
}

void WallManager::createWall(){
	new Wall(a, colorNum);
	new Wall(b, colorNum);
	stepCounter = 0;
	/*timerCount++;
	if (timerCount == timer){
		new Wall(a);
		new Wall(b);
		timerCount = 0;
	}*/
}

int WallManager::eventHandler(Event *p_e){
	if (p_e->getType() == STEP_EVENT) {
		stepCounter++;
		if(stepCounter >= 2){
			createWall();
			wallCounter++;
			if(wallCounter >= 50){
				colorNum = random() % 6;
				wallCounter = 0;
			}
			return 1;
		}
    
	}

  // if we get here, we have ignored this event
  return 0;
}

Position WallManager::getPositionA(){
	return a;
}


Position WallManager::getPositionB(){
	return b;
}

void WallManager::setTimer(int new_timer){
	timer = new_timer;
	return;
}

int WallManager::getTimer(){
	return timer;
}


