
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Character.h"
#include "GameManager.h"
#include "Wall.h"
#include "GameOver.h"
#include <math.h>

Character::Character() {
  GraphicsManager &gm = GraphicsManager::getInstance();
  LogManager &lm = LogManager::getInstance();
  registerInterest(KEYBOARD_EVENT);
  registerInterest(STEP_EVENT);
  inAir = 2;
  jumpDirection = -1;
  xVelocity = -5;
  yVelocity = -7;
  Position pos(gm.getHorizontal()/2,gm.getVertical()/2);
  setPosition(pos);
  comboJump = 0;
  moveCount = 0;
  setType("player");
  setCollisionValue(1);
  power = -1;
  powerCounter = 0;
}

Character::~Character() {
	unregisterInterest(STEP_EVENT);
	//unregisterInterest(OUT_EVENT);
	unregisterInterest(KEYBOARD_EVENT);
	new GameOver();
}


int Character::eventHandler(Event *p_e) {
  if (p_e->getType() == OUT_EVENT){}
  if (p_e->getType() == KEYBOARD_EVENT) {
    EventKeyboard *p_keyboard_event = static_cast <EventKeyboard *> (p_e);
	if(p_keyboard_event->getKey() == 'q')GameManager::getInstance().setGameOver();
    kbd(p_keyboard_event);
    return 1;
  }

  if (p_e->getType() == STEP_EVENT) {
	
    step();
    return 1;
  }

  return 0;
}

void Character::kbd(EventKeyboard *p_keyboard_event) {
  WorldManager &world_manager = WorldManager::getInstance();
  LogManager &lm = LogManager::getInstance();
  if(inAir == 0){
	  switch(p_keyboard_event->getKey()) {
	  case KEY_UP:
		comboJump = 0;
		comboJump = comboJump + 1;
		move(-1);
		break;
	  case KEY_DOWN:
		comboJump = 0;
		comboJump = comboJump + 2;
		move(+1);
		break;
	  case KEY_LEFT:
		comboJump = comboJump + 10;
		jump(-1);
		break;
	  case KEY_RIGHT:
		comboJump = comboJump + 20;
		jump(+1);
		break;
	  case 'z':
		  power = 0;
		  break;
	  case 'x':
		  power = 1;
		  break;
	  case 'c':
		  power = 2;
		  break;
	  case 'v':
		  power = -1;
		  break;//test power

	  };
	  return;
  }
}

void Character::move(int dy) {
	if(inAir == 0){
		//yVelocity = yVelocity + dy;
	}
}


void Character::jump(int dx) {
	if(jumpDirection != dx){
		if(comboJump == 11 || comboJump == 21){
			yVelocity -= 8;

		}
		if(comboJump == 12 || comboJump == 22){
			yVelocity += 1;

		}
		if(comboJump == 10 || comboJump == 20){
			yVelocity -= 6;

		}
		if(inAir == 0 || inAir == 3){
			inAir = 1;
			jumpDirection = dx;
		
		}
	}
	return;
}

void Character::step() {
	GraphicsManager &gm = GraphicsManager::getInstance();
	if(getPosition().getY() > gm.getVertical()){//getPosition().getY() <= 0 || 
		WorldManager::getInstance().markForDelete(this);
	}
	LogManager &lm = LogManager::getInstance();
	int x,y;
	x = getPosition().getX();
	y = getPosition().getY();
	if(power == 0 || power){
		powerCounter++;
		if(powerCounter>=310){
			powerCounter = 0;
			power = -1;
		}
	}
	if(power == 2 && inAir != 3){
		inAir = 3;
		setType("super");
		xVelocity = 1;
		return;
	} else if(power == 2 && inAir == 3){
		if(!fmod(powerCounter,30))xVelocity = -xVelocity;
		setPosition(Position(x + xVelocity, y));
		if(powerCounter >= 300){
			powerCounter = 0;
			power = -1;
			inAir = 1;
			comboCount = 0;
			comboJump = 0;
			yVelocity = -5;
			jump(-jumpDirection);
		}
		return;
	}


	if(inAir == 4 && jumpDirection != 0){
		yVelocity = -5;
		jumpDirection = 0;
	}


	if(inAir == 4 && jumpDirection == 0){
		yVelocity += 1;
		setPosition(Position(x, y + yVelocity));
		return;
	}

	comboCount++;
	moveCount++;
	if(inAir == 0){
		if(getType()!="player")setType("player");
		if(moveCount >= 2){
			setPosition(Position(x + xVelocity, y + yVelocity));
			moveCount = 0;
		}
		if (comboCount >= 5){
			comboCount = 0;
			comboJump = 0;
		}
		return;
	}
	if(inAir == 2){
		setPosition(Position(x + xVelocity, y + yVelocity));
		yVelocity = yVelocity + 1;
	}
	if(inAir == 1){
		if(jumpDirection == -1)xVelocity = -10;
		if(jumpDirection == 1)xVelocity = 10;
		setPosition(Position(x + xVelocity, y + yVelocity));
		yVelocity = yVelocity + 1;
	}
	if(WorldManager::getInstance().checkCollision(this, getPosition())){
		int boxXL = (gm.getHorizontal() * 5) / 12;
		int boxXR = (gm.getHorizontal() * 7) / 12;
		if(jumpDirection == 1 && getPosition().getX() - boxXL<= 11){
			inAir = 0;
			yVelocity = 1;
			xVelocity = 0;
			comboJump = 0;
			comboCount = 0;
			setPosition(Position(boxXL, getPosition().getY()));
			return;
		} else if(jumpDirection == -1 && boxXR - getPosition().getX() <= 11){
			inAir = 0;
			yVelocity = 1;
			xVelocity = 0;
			comboJump = 0;
			comboCount = 0;
			setPosition(Position(boxXR, getPosition().getY()));
			return;
		} else{
			inAir = 4;
			//WorldManager::getInstance().markForDelete(this);
			//GameManager::getInstance().setGameOver();
		}
	}

	if(getPosition().getX() <= (gm.getHorizontal() /3)+1){
		inAir = 0;
		yVelocity = 1;
		xVelocity = 0;
		comboJump = 0;
		comboCount = 0;
		setPosition(Position((gm.getHorizontal() /3)+1, getPosition().getY()));
		return;
	}else if(getPosition().getX() >= ((gm.getHorizontal() * 2) / 3)-1){
			inAir = 0;
			yVelocity = 1;
			xVelocity = 0;
			comboJump = 0;
			comboCount = 0;
			setPosition(Position(((gm.getHorizontal() * 2) / 3)-1, getPosition().getY()));
			return;
	}

}

void Character::draw(){
	LogManager &lm = LogManager::getInstance();
	GraphicsManager &gm = GraphicsManager::getInstance();
	int x,y,color;
	x = this->getPosition().getX();
	y = this->getPosition().getY();
	char c = 'O';
	char l = '/';
	char r = '\\';
	if(inAir == 1|| inAir == 0 || inAir ==2)color = COLOR_BLUE;
	if(power == 2)color = COLOR_MAGENTA;
	if(power == 1)color = COLOR_GREEN;
	if(power == 0)color = COLOR_YELLOW;
	if(inAir == 4)color = COLOR_CYAN;
	if(inAir && power != 2){
		gm.drawCh(Position(x+1,y), r, color);
		gm.drawCh(Position(x,y), c, color);
		gm.drawCh(Position(x-1,y), l, color);
		gm.drawCh(Position(x+1,y+1), r, color);
		gm.drawCh(Position(x,y+1), c, color);
		gm.drawCh(Position(x-1,y+1), l, color);
	}else if(power == 2){
		gm.drawCh(Position(x+1,y), r, color);
		gm.drawCh(Position(x,y), c, color);
		gm.drawCh(Position(x-1,y), l, color);
		gm.drawCh(Position(x+1,y+1), r, color);
		gm.drawCh(Position(x,y+1), c, color);
		gm.drawCh(Position(x-1,y+1), l, color);
		for(int i = 2; i < ((gm.getHorizontal() * 2) / 3)-x;i++)gm.drawCh(Position(x+i,y), '-', color);
		for(int i = 2; i < x-(gm.getHorizontal() / 3);i++)gm.drawCh(Position(x-i,y), '-', color);
	}else if(jumpDirection == 1){
		gm.drawCh(Position(x,y+1), r, color);
		gm.drawCh(Position(x,y), c, color);
		gm.drawCh(Position(x,y-1), l, color);
	} else{
		gm.drawCh(Position(x,y-1), r, color);
		gm.drawCh(Position(x,y), c, color);
		gm.drawCh(Position(x,y+1), l, color);
	}
}

void Character::setPower(int new_power){
	power = new_power;
	return;
}

int Character::getPower(){
	return power;
}

void Character::playerDie(){
	inAir = 4;
}