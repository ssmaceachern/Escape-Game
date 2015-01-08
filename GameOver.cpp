#include "GameOver.h"

#include "LogManager.h"
#include "GameStart.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"

GameOver::GameOver(){
	time_to_live = 30;
	
	// put in center of screen
  GraphicsManager &gr_manager = GraphicsManager::getInstance();
  Position pos(gr_manager.getHorizontal() / 2, gr_manager.getVertical() / 2);
  setPosition(pos);
	
	registerInterest(STEP_EVENT);
}

GameOver::~GameOver(){
	new GameStart;
	
}

int GameOver::eventHandler(Event *p_e){
	//LogManager &lm = LogManager::getInstance();
	GameManager &game_manager = GameManager::getInstance();
	
	if (p_e->getType() == STEP_EVENT) {
    step();
    return 1;
  }
	
	return 0;
}

void GameOver::step(){
	time_to_live--;
	if(time_to_live <= 0){
		WorldManager &wm = WorldManager::getInstance();
		wm.markForDelete(this);
		
		//new GameStart();
		GameManager &game_manager = GameManager::getInstance();
		game_manager.setGameOver();
	}
}

void GameOver::draw(){
GraphicsManager &gr_manager = GraphicsManager::getInstance();

gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()-3), gln1, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()-2), gln2, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()-1), gln3, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()), gln4, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()+1), gln5, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()+2), gln6, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()+3), gln7, CENTER_JUSTIFIED, COLOR_RED);
}
