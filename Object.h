//
// The base game world object
//

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

#include "Event.h"           // Objects can handle events.
#include "Position.h"        // Objects need a location.

#define MAX_OBJ_EVENTS 100   // Max events Object can be interested in.

using std::string;           // Introduce "string" into namespace

enum Solidness {
  HARD,      // Object causes collisions and impedes.
  SOFT,      // Object causes collision, but doesn't impede.
  SPECTRAL    // Object doesn't cause collisions.
};
 
class Object {

 private:
  int event_count;            // Keep track of interested events.
  string event_name[MAX_OBJ_EVENTS]; // Event names.
  Position pos;               // Position in the game world.
  string type;                // User-defined identification.
  int altitude;               // 0 to MAX_ALTITUDE (lower drawn first).
  Solidness solidness;        // Solidness state of object.
  float x_velocity;           // Horizontal speed in spaces per game step.
  float x_velocity_countdown; // Countdown to horizontal movement.
  float y_velocity;           // Vertical speed in spaces per game step.
  float y_velocity_countdown; // Countdown to vertical movement.
  int collisionValue;

 public:
  Object();

  // Destroy object, unregistering for any interested events.
  virtual ~Object();

  // Set object altitude, with checks for range [0, MAX_ALTITUDE].
  // Return 0 if ok, else -1.
  int setAltitude(int new_altitude);
   
  // Return object altitude.
  int getAltitude();
   
  // Set x velocity.
  void setXVelocity(float new_x_velocity);

  // Get x velocity.
  float getXVelocity();

  // Set y velocity.
  void setYVelocity(float new_y_velocity);

  // Get y velocity.
  float getYVelocity();

  // Perform 1 step of velocity in horizontal direction.
  // Return horizontal distance moved this step.
  int getXVelocityStep();

  // Perform 1 step of velocity in vertical direction.
  // Return vertical distance moved this step.
  int getYVelocityStep();

  // Set type identifier of object.
  void setType(string new_type);

  // Get type identifier of object.
  string getType();

  // Set Position of object.
  void setPosition(Position new_pos);

  // Get Position of object.
  Position getPosition();

  // Handle event (default is to ignore everything).
  // Return 0 if ignored, else 1.
  virtual int eventHandler(Event *p_event);

  // Register for interest in event.  
  // Keeps track of manager and event.  
  // Return 0 if ok, else -1.
  int registerInterest(string event);

  // Unregister for interest in event.  
  // Return 0 if ok, else -1.
  int unregisterInterest(string event);

  // Draw single sprite frame.
  // Drawing accounts for: centering, slowdown, advancing Sprite Frame
  virtual void draw();
  bool isSolid();

  int setSolidness(Solidness new_solid);

  Solidness getSolidness();

  void setCollisionValue(int cValue);
  int getCollisionValue();

};

#endif // __OBJECT_H__
