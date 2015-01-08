#ifndef __OBJECTFACTORY_H__
#define __OBJECTFACTORY_H__
#include "Object.h"
#include "EventCollision.h"
#include "Position.h"

class ObjectFactory : public Object {

 protected:
  void step();
  int stepCounter;
  bool isCreated;
  void newBlock();
  void newRounder();
  void newBouncer();
  void newWallBox();
  int rand2;
  int rand3;
 public:
  ObjectFactory();
  ~ObjectFactory();
  int eventHandler(Event *p_e);
};

#endif