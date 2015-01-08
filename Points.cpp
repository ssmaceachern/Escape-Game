#include "Points.h"

#include "LogManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"

string Points::NumberToString (int n)
  {
     ostringstream ss;
     ss << n;
     return ss.str();
  }

Points::Points(){
	score = 0;
	stepCounter = 0;
	doubleCounter = 0;
	registerInterest(STEP_EVENT);
}

int Points::eventHandler(Event *p_e){
	
	
	if (p_e->getType() == STEP_EVENT) {
    step();
    return 1;
  }
	
	return 0;
}

void Points::step(){
	GameManager &gm = GameManager::getInstance();
	stepCounter++;
	if(stepCounter >= gm.getGameStep()){
		score++;
		stepCounter = 0;
	}
	if(doubleCounter >= 300){
		doubleCounter = 0;
		gm.setGameStep(30);
	}else if(gm.getGameStep() == 15)doubleCounter++;
}

void Points::draw(){
	GraphicsManager &gm = GraphicsManager::getInstance();
	int color;
	if(doubleCounter > 0)color=COLOR_YELLOW;
	else color=COLOR_DEFAULT;
	gm.drawString(Position((gm.getHorizontal() * 3) / 4, 9),  "SCORE", CENTER_JUSTIFIED, color);
	gm.drawString(Position((gm.getHorizontal() * 3) / 4, 10), "|     " + NumberToString(score) + "    |", CENTER_JUSTIFIED, color);
	
	//GraphicsManager &gr_manager = GraphicsManager::getInstance();

	//gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()-3), gln1, CENTER_JUSTIFIED, COLOR_RED);
}
