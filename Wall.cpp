#include <stdlib.h>
#include <time.h>

#include "Wall.h"
#include "LogManager.h"
#include "WorldManager.h"
//#include "GraphicsManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "WallManager.h"

Wall::Wall(Position pos, int wallColorNum){
	LogManager &lm = LogManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	timerCount = 0;
	//Make it a collidable object
	setType("Wall");
	setSolidness(HARD);
	
	//Allow for WallManager to set the Position
	setPosition(pos);
	setYVelocity(0.5f);
	//Set the wall character to a random color
	srand(time(NULL));
	colorNum = wallColorNum;
	lm.writeLog("Random color is: %d", colorNum);
	
	//Register for Step Event
	registerInterest(STEP_EVENT);
	registerInterest(OUT_EVENT);
}

//Draw the Wall Object
void Wall::draw(){
	LogManager &lm = LogManager::getInstance();
	GraphicsManager &graph_mgr = GraphicsManager::getInstance();
	graph_mgr.drawCh(getPosition(), WALL_CHAR, colorNum);
}

//Detect for Step Events and Out Events
//Step Events: Move Down
//Out Events: markForDelete
int Wall::eventHandler(Event *p_e){

	if (p_e->getType() == STEP_EVENT) {
    step();
    return 1;
  }
  
	if (p_e->getType() == OUT_EVENT) {
    	if(getPosition().getY() >=  GraphicsManager::getInstance().getVertical())out();
    return 1;
  }
  
  // if we get here, we have ignored this event
  return 0;
}

void Wall::out(){
	//LogManager &lm = LogManager::getInstance();
	//lm.writeLog("Wall Deleted\n");

	WorldManager &wm = WorldManager::getInstance();
	wm.markForDelete(this);
	delete this;
}

void Wall::step(){
	//setPosition(Position(getPosition().getX(), getPosition().getY() + 1));
/*	if(timerCount == wm.getTimer()){

		timerCount = 0;
		if(getPosition().getY() >= gm.getVertical())registerInterest(OUT_EVENT);
	}*/
}


