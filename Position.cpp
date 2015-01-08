#include "Position.h"


Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int init_x, int init_y) {
	setX(init_x);
	setY(init_y);
}

int Position::getX() {
	return x;
}

void Position::setX(int new_x) {
	x = new_x;
}

int Position::getY() {
	return y;
}

void Position::setY(int new_y) {
	y = new_y;
}

void Position::setXY(int new_x, int new_y) {
	setX(new_x);
	setY(new_y);
}