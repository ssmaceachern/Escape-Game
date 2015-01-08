#ifndef __WALLBOX_H__
#define __WALLBOX_H__
#include "Enemy.h"
#include "EventCollision.h"

#define WALLBOX_CHAR 'V'

class WallBox : public Enemy {

 protected:
  void onCollision(EventCollision *p_c);
  int width;
  int height;

 public:
  WallBox(int new_height, float yVelocity);
  ~WallBox();
  int eventHandler(Event *p_e);
  void draw();
  void out();
  int getHeight();
  int getWidth();
};

#endif