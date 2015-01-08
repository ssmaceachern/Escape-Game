#ifndef WALL_H
#define WALL_H

#include "Object.h"
#include "Event.h"
#include "Position.h"
#include "GraphicsManager.h"

#define WALL_CHAR '@'

class Wall : public Object {

	public:
		void out();
		Wall(Position pos, int wallColorNum);
		void draw();

	
	private:
		void step();
		int eventHandler(Event *p_e);
		int colorNum;
		int timerCount;
		bool firstHit;
};

#endif
