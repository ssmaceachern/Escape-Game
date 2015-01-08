///
/// The game world manager
///

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__


#include "Manager.h"
#include "ObjectList.h"
#include "Position.h"
#include "utility.h"
#include "EventCollision.h"

class WorldManager : public Manager {

 private:
  WorldManager();               ///< Private since a singleton.
  WorldManager (WorldManager const&);  ///< Don't allow copy.
  void operator=(WorldManager const&); ///< Don't allow assignment.
  ObjectList updates;         ///< List of all Objects to update.
  ObjectList deletions;         ///< List of all Objects to delete.
  int xc,yc,xe,ye,cvc,cve; //Check Collision Variables

 public:
  /// Get the one and only instance of the WorldManager.
  static WorldManager &getInstance();

  /// Startup game world (initialize everthing to empty).
  /// Return 0.
  int startUp();

  /// Shutdown game world.
  void shutDown();
  bool isValid(string event_name);
  /// Add Object to world.
  /// Return 0 if ok, else -1.
  int insertObject(Object *p_go);

  /// Remove Object from world.
  /// Return 0 if ok, else -1.
  int removeObject(Object *p_go);

  /// Return list of all Objects in world.
  /// Return NULL if list is empty.
  ObjectList getAllObjects(void);

  /// Indicate object is to be deleted at end of current game loop.
  /// Return 0 if ok, else -1.
  int markForDelete(Object *p_o);

  /// Update world.
  /// Update positions of Objects based on their velocities.
  /// Update SceneGraph for those marked for updates.
  /// Lastly, delete Objects marked for deletion.
  void update();
  // Drawall Objects in view.
  // Draw bottom up, from -MAX_ALTITUDE to MAX_ALTITUDE
  void draw();

  // Move Object. 
  // If no collision with solid, move ok else don't move object.
  // If p_go is Spectral, move ok.
  // If move ok, adjust screen if following this Object.
  // Return 0 if move ok, else -1 if collision with solid.
  int moveObject(Object *p_o, Position where);

  // Return list of Objects collided with at Position 'where'.
  // Collisions only with solid Objects.
  // Does not consider if p_go is solid or not.
  ObjectList isCollision(Object *p_o, Position where);
  bool checkCollision(Object *p_c, Position nowP);

};
 
#endif // __WORLD_MANAGER_H__
