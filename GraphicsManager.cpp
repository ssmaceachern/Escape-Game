#include <string>
#include <ncurses.h>
#include <curses.h>
#include "LogManager.h"
#include "GraphicsManager.h"
#include "Position.h"
#include "Manager.h"

using std::string;


GraphicsManager::GraphicsManager() {
	is_started = false;
}

GraphicsManager& GraphicsManager::getInstance() {
	static GraphicsManager instance;
	return instance;
}

int GraphicsManager::startUp() {
	int status[4];
	if(!is_started) {
		initscr();
		curs_set(0);
		buffer = newwin(0,0,0,0);
		status[0] = clearok(buffer, TRUE);
		status[1] = leaveok(buffer, TRUE);
		if(has_colors() == TRUE) {
			start_color();
		}
		status[2] = getmaxyx(stdscr, max_y, max_x);
		is_started = true;
		init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
		init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
		init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
		init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
		init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
		init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
		status[3] = wattron(buffer,A_BOLD);
	}
	for (int i = 0; i <= 3; i++){
		if (status[i] < 0 || status[i] == ERR){
			is_started = false;
			return -1;
		}
	}
	return 0;
}

void GraphicsManager::shutDown() {
	if(is_started) {
		endwin();
		is_started = false;
	}
}


int GraphicsManager::drawCh(Position pos, char ch, int color) {
	int status[2];
	status[0] = wattron(buffer, COLOR_PAIR(color));
	mvwaddch(buffer, pos.getY(), pos.getX(), ch);
	status[1] = wattroff(buffer, COLOR_PAIR(color));
	for (int i = 0; i <= 1; i++){
		if (status[i] < 0 || status[i] == ERR){
			return -1;
		}
	}
	return 0;
}

int GraphicsManager::drawString(Position world_pos, string str, Justification just, int color){
	Position starting_pos = world_pos;
	switch(just){
	case CENTER_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size()/2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size()/2);
		break;
	case LEFT_JUSTIFIED:
	default:
		break;
	}
	for (int i = 0; i <= (str.size() - 1);i++){
		Position temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}
	return 0;
}


int GraphicsManager::getHorizontal() {
	return max_x;
}

int GraphicsManager::getVertical() {
	return max_y;
}

int GraphicsManager::swapBuffers(){
	int status[2];
	status[0] = wrefresh(buffer);
	status[1] = werase(buffer);
	for (int i = 0; i <= 1; i++){
		if (status[i] < 0 || status[i] == ERR){
			return -1;
		}
	}
	return 0;
}

WINDOW* GraphicsManager::getBuffer(){
	return buffer;
}

int GraphicsManager::colorNumFromStr(string colorStr) {
	if(colorStr == "white") {
		return COLOR_WHITE;
	}
	if(colorStr == "yellow") {
		return COLOR_YELLOW;
	}
	if(colorStr == "magenta") {
		return COLOR_MAGENTA;
	}
	if(colorStr == "blue") {
		return COLOR_BLUE;
	}
	if(colorStr == "green") {
		return COLOR_GREEN;
	}
	if(colorStr == "red") {
		return COLOR_RED;
	}
	if(colorStr == "cyan") {
		return COLOR_CYAN;
	}
	return -1;
}
