#ifndef __BOUNCER_H__
#define __BOUNCER_H__
#include "Enemy.h"
#include "EventCollision.h"

#define BOUNCER_CHAR '&'

class Bouncer : public Enemy {

 protected:
  void onCollision(EventCollision *p_c);
  int xVelocity;
  int frameCounter;

 public:
  Bouncer(Position pos, int hVelocity);
  ~Bouncer();
  int eventHandler(Event *p_e);
  void draw();
  void step();
  void out();
};

#endif