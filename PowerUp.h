#ifndef __POWERUP_H__
#define __POWERUP_H__
#include "Object.h"
#include "EventCollision.h"
#include "Position.h"

class PowerUp : public Object {

 protected:
 void onCollision(EventCollision *p_c);
 void step();
 void out();
 int stepCounter;
 int rand;
 bool dead;
 void drawE();
 int color;
 public:
  PowerUp();
  ~PowerUp();
  int eventHandler(Event *p_e);
  void draw();
  int getPower();
};

#endif