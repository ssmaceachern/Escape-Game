#include "Wall.h"
#include "Object.h"
#include "Event.h"
#include "Position.h"

class WallManager : public Object {

	public:
		WallManager();
		Position getPositionA();
		Position getPositionB();
		void setTimer(int new_timer);
		int getTimer();
		bool isOn;
	private:
		Position a, b;
		void createWall();
		int eventHandler(Event *p_e);
		int timer;
		int timerCount;
		int stepCounter;
		int wallCounter;
		int colorNum;
};
