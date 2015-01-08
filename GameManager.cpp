#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "GameManager.h"
#include "LogManager.h"
#include "Manager.h"
#include "Clock.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "Position.h"
#include "Character.h"
#include "WallManager.h"
#include "Bouncer.h"
#include "Block.h"
#include "Rounder.h"
#include "ObjectFactory.h"


GameManager::GameManager() {}
GameManager::~GameManager() {}

GameManager& GameManager::getInstance() {
	static GameManager instance;
	return instance;
}

int GameManager::startUp() {
	int status = 0;

	if(status < 0) {
		return status;
	}
		LogManager &lm = LogManager::getInstance();
		lm.startUp();
	
	status = GraphicsManager::getInstance().startUp();
	if(status < 0) {
		lm.writeLog("Error starting GraphicsManager, status=%d", status);
		return status;
	}else{lm.writeLog("Starting GraphicsManager sucessufully, status=%d, ", status);}
	
	status = InputManager::getInstance().startUp();
	if(status < 0) {
		lm.writeLog("Error starting InputManager, status=%d", status);
		return status;
	}else{lm.writeLog("Starting InputManager sucessufully, status=%d, ", status);}

	status = WorldManager::getInstance().startUp();
	if(status < 0) {
		lm.writeLog("Error starting WorldManager, status=%d", status);
		return status;
	} else{lm.writeLog("Starting WorldManager sucessufully, status=%d, ", status);}
	


	if(status >= 0) {
		is_started = true;
		gameStep = 30;
		//run();
	}
	
	
	return status;
}

int GameManager::startUp(bool flush) {
	if(flush){
		LogManager &lm = LogManager::getInstance();
		lm.writeLog("GameManager Starts");
		return 0;
	}
}

void GameManager::shutDown() {
	if(!is_started) {
		return;
	}
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("Shutting down everyting");
	LogManager::getInstance().shutDown();
	WorldManager::getInstance().shutDown();
	GraphicsManager::getInstance().shutDown();
	InputManager::getInstance().shutDown();
	game_over = true;
}

void GameManager::run(int fr_time) {
	//new WallManager();
	//new ObjectFactory;
	
	LogManager &lm = LogManager::getInstance();
	lm.writeLog("started up all!!");
	Clock gameClock;
	long elapsedTime;
	WorldManager &wm = WorldManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	InputManager &im = InputManager::getInstance();
	
	EventStep s;
	s.setType(STEP_EVENT);
	
	while(!game_over) {
		wm.update();
		wm.draw();
		gm.swapBuffers();
		im.getInput();
		
		onEvent(&s);
		elapsedTime = gameClock.split();
		if(elapsedTime < fr_time*1000) {
			//lm.writeLog("usleeped!!%d,", testCountDown);
			usleep(fr_time*1000-elapsedTime);
		}
	}
}

void GameManager::setGameOver() {
	game_over = true;
	shutDown();
}

int getFrameTime() {
	return DEFAULT_FRAME_TIME;
}

bool GameManager::isValid(string event_name){
	if(event_name == STEP_EVENT){return true;}
	else { return false;}
}

int GameManager::getGameStep() {
	return gameStep;
}
void GameManager::setGameStep(int new_step) {
	gameStep = new_step;
	return;
}