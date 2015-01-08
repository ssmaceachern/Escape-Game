#include <ncurses.h>
#include <curses.h>
#include "InputManager.h"
#include "Event.h"
#include "GraphicsManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "LogManager.h"



InputManager::InputManager() {
	is_started = false;
}


InputManager& InputManager::getInstance() {
	static InputManager instance;
	return instance;
}

int InputManager::startUp() {
	LogManager &lm = LogManager::getInstance();

	if(is_started)
		return 0;

	int status[6];

	status[0] = keypad(stdscr, TRUE);
	

	status[1] = cbreak();

	status[2] = nodelay(stdscr, TRUE);

	status[3] = nonl();

	status[4] = noecho();
	
	mmask_t mask = BUTTON1_CLICKED | BUTTON3_CLICKED | BUTTON1_DOUBLE_CLICKED | BUTTON3_DOUBLE_CLICKED;
	status[5] = mousemask(mask, NULL);
	for (int i = 0; i <= 5; i++){
		if (status[i] < 0 || status[i] == ERR){
			return -1;
		}
	}	
	is_started = true;
	return 0;
}

void InputManager::shutDown() {
	if(!is_started)
		return;
	
	is_started = false;
}


void InputManager::getInput() {
	LogManager &lm = LogManager::getInstance();
	int c;
	MEVENT m_event;
	while(1) {
		c = getch();
		if(c == ERR) {
			break;
		}
		else if(c == KEY_MOUSE && getmouse(&m_event) == OK) {
					MouseActionList action;

					if(m_event.bstate & BUTTON1_CLICKED){
						lm.writeLog("Left clicked......");
						action = LEFT_BUTTON_CLICK;
					}else if(m_event.bstate & BUTTON3_CLICKED){
						lm.writeLog("Right clicked......");
						action = RIGHT_BUTTON_CLICK;
					}else if(m_event.bstate & BUTTON1_DOUBLE_CLICKED){
						lm.writeLog("Left double clicked......");
						action = LEFT_BUTTON_DOUBLECLICK;
					}else if(m_event.bstate & BUTTON3_DOUBLE_CLICKED){
						lm.writeLog("Right double clicked......");
						action = RIGHT_BUTTON_DOUBLECLICK;
					}else
						return;
			
					EventMouse em;
					em.setType(MOUSE_EVENT);
					em.setMouseX(m_event.x);
					em.setMouseY(m_event.y);
					em.setMouseAction(action);
					lm.writeLog("MouseX = %d, MouseY = %d, ", em.getMouseX(), em.getMouseY());
					onEvent(&em);
					return;
		}
		else {
			int result;
			switch(c)
			{
				case KEY_LEFT:
				result = 'a';
				break;
				case KEY_RIGHT:
				result = 'd';
			    break;
				case KEY_DOWN:
				result = 's';
				break;
				case KEY_UP:
				result = 'w';
				break;
				case 'q':
				result = 'q';
				break;
				default:
				break;
			}

			EventKeyboard ek;
			ek.setType(KEYBOARD_EVENT);
			ek.setKey(c);
			onEvent(&ek);
			return;
		}
	}
}


bool InputManager::isValid(string event_name){
	if(event_name == KEYBOARD_EVENT || event_name == MOUSE_EVENT)
		return true;
	else 
		return false;
}
