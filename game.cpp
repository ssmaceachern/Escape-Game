
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "GameManager.h"
#include "LogManager.h"

#include "GameStart.h"


int main(int argc, char *argv[]) {
  LogManager &log_manager = LogManager::getInstance();

  // Start up Game Manager
  GameManager &game_manager = GameManager::getInstance();
  if (game_manager.startUp())  {
    log_manager.writeLog("Error starting game manager!\n");
    game_manager.shutDown();
    exit(1);
  }
  
  new GameStart();
  
  game_manager.run();
}


