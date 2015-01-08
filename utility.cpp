
#include <stdlib.h>		


#include "utility.h"
#include "Position.h"
#include "Object.h"



/*char *getTimeString() {
	Static char time_str[30];

	time_t time;
	time(&time);
	struct tm *p_time = localtime(time);

	sprintf(time_str, "%02d:%02d:%02d", p_time -> tm_hour, p_time -> tm_min, p_time -> tm_sec);
	return time_str;
}*/

bool positionsIntersect(Position p1, Position p2){
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY()){
		return true;
	}else{
		return false;
	}
}