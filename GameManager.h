///
/// The game manager
///

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <time.h>                     ///< For time_t.
#include "Manager.h"

#define DRAGONFLY_VERSION 2.4
 
#define DEFAULT_FRAME_TIME 33         ///< In milliseconds (33 ms == 30 fps).

class GameManager : public Manager {

 private:
  GameManager();                      ///< Private since a singleton.
  GameManager (GameManager const&);   ///< Don't allow copy.
  void operator=(GameManager const&); ///< Don't allow assignment.
  bool game_over;                     ///< True -> game loop should stop.
  int frame_time;                     ///< Target time per game loop, in millisec.
  bool is_started;
  int gameStep;

 public:
  ~GameManager();

  /// Get the singleton instance of the GameManager.
  static GameManager &getInstance();

  /// Startup all GameManager services.
  int startUp();

  /// Startup all GameManager services.
  /// If flush is true, call fflush() after each write (default false).
  int startUp(bool flush);


  /// Shut down GameManager services.
  void shutDown();

  bool isValid(string event_name);

  // Shut down GameManager services.

  /// Run the game loop.
  /// fr_time is time between frames.
  void run(int fr_time=DEFAULT_FRAME_TIME);

  /// Indicate game is over, which will stop game loop.
  void setGameOver();


  /// Return frame time.  
  /// Frame time is target time for each game loop, in milliseconds.
  int getFrameTime();
  int getGameStep();
  void setGameStep(int new_step);
};

#endif // __GAME_MANAGER_H__
