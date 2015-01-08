#include "GameStart.h"

#include "EventKeyboard.h"
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"	// for COLOR_YELLOW
#include "LogManager.h"
#include "WorldManager.h"

//include game source code
#include "Position.h"
#include "Character.h"
//#include "WallManager.h"
#include "Bouncer.h"
#include "Block.h"
#include "Rounder.h"
//#include "ObjectFactory.h"
#include "Points.h"

GameStart::GameStart(){
	setType("GameStart");
	
	// put in center of screen
  GraphicsManager &gr_manager = GraphicsManager::getInstance();
  Position pos(gr_manager.getHorizontal() / 2, gr_manager.getVertical() / 2);
  setPosition(pos);
  
  /*wall_manager = NULL;
  obj_factory = NULL;
  
  WorldManager &wm = WorldManager::getInstance();
  if(wall_manager->isOn == true){
  	wm.markForDelete(wall_manager);
  }
  
  if(obj_factory->isOn ==  true){
  	wm.markForDelete(obj_factory);
  }*/
  
  gameStart = false;

  // register for "keyboard" event
  registerInterest(KEYBOARD_EVENT);
}

int GameStart::eventHandler(Event *p_e){
	LogManager &lm = LogManager::getInstance();
	GameManager &game_manager = GameManager::getInstance();
	
	lm.writeLog("GAMESTART HAS BEEN CREATED");
	
	if(p_e->getType() == KEYBOARD_EVENT){
		EventKeyboard *p_k = (EventKeyboard *) p_e;
		switch(p_k->getKey()){
			case 'q':
			game_manager.setGameOver();
			break;
			case 'p':
			start();
			default:
			break;
		}
		return 1;
	}
	
	return 0;
}

void GameStart::start(){
	GameManager &game_manager = GameManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	
	wall_manager = new WallManager();
	obj_factory = new ObjectFactory();
	
	new Points();
	//gameStart = true;
	
	wm.markForDelete(this);
	//game_manager.run();
}

void GameStart::step(){

}

void GameStart::draw(){
GraphicsManager &gr_manager = GraphicsManager::getInstance();
//GameManager &gm_manager = GameManager::getInstance();
if(!gameStart){
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()-3), ln1, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()-2), ln2, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()-1), ln3, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()), ln4, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()+1), ln5, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()+2), ln6, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()+3), ln7, CENTER_JUSTIFIED, COLOR_RED);
gr_manager.drawString(Position(getPosition().getX(), getPosition().getY()+5), "Press P to Play, Press Q to Quit", CENTER_JUSTIFIED, COLOR_RED);
}

}
