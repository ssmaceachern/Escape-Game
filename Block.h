#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "Enemy.h"
#include "EventCollision.h"

#define BLOCK_CHAR 'V'

class Block : public Enemy {

 protected:
  void onCollision(EventCollision *p_c);
  int xVelocity;
  bool onLeft;

 public:
  Block(bool onRight, float yVelocity);
  ~Block();
  int eventHandler(Event *p_e);
  void draw();
  void out();
};

#endif