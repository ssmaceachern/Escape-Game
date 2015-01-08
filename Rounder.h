#ifndef __ROUNDER_H__
#define __ROUNDER_H__
#include "Enemy.h"
#include "EventCollision.h"

#define ROUNDER_CHAR '*'

class Rounder : public Enemy {

 protected:
  void onCollision(EventCollision *p_c);
  int xVelocity;
  int yVelocity;
  int status;
  int yCounter;
  int frameCounter;

 public:
  Rounder(Position pos, int hVelocity, int vVelocity);
  ~Rounder();
  int eventHandler(Event *p_e);
  void draw();
  void step();
  void out();
};

#endif