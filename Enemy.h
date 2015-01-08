#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Object.h"
#include "EventCollision.h"
#include "Position.h"

class Enemy : public Object {

 protected:
  virtual void onCollision(EventCollision *p_c);
  virtual void step();
  virtual void out();
  int stepCounter;
 public:
  Enemy(Position pos);
  ~Enemy();
  virtual int eventHandler(Event *p_e);
  virtual void draw();
  Position moveDX(int dx);
  Position moveDY(int dy);
};

#endif