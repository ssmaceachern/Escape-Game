
#include "Object.h"
#include "EventKeyboard.h"
#include "EventCollision.h"

class Character : public Object {

 protected:
  int inAir;
  int jumpDirection;
  int xVelocity;
  int yVelocity;
  int comboJump;
  int comboCount;
  int moveCount;
  int power;
  int powerCounter;
  void kbd(EventKeyboard *keyboard_event);
  void move(int dy);
  void jump(int dx);
  void step();
  void onCollision(EventCollision *p_c);
 public:
  Character();
  ~Character();
  int eventHandler(Event *p_e);
  void draw();
  void setPower(int new_power);
  int getPower();
  void playerDie();
};

