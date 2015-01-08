#
# Makefile for saucer shoot game using Dragonfly
#
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
# 'make' to build executable
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#   DEBUG can be set to -DDEBUG to enable various debug flags
#

CC= g++ 
#PLATFORM= -DCYGWIN		# uncomment for cygwin
#PLATFORM= -DMACOS  		# uncomment for macos
LDFLAGS= -lncurses -lrt	# uncomment linux/cygwin
#LDFLAGS= -lncurses 		# uncomment for macos
INCPATH= include		# path to engine includes
#ENG= lib/libdragonfly.a	# dragonfly engine
ENGSRC= Manager.cpp \
         LogManager.cpp \
         Event.cpp \
         EventStep.cpp \
         Position.cpp \
         Clock.cpp \
         GameManager.cpp \
         Object.cpp \
         ObjectList.cpp \
		 ObjectListIterator.cpp \
		 WorldManager.cpp \
		 GraphicsManager.cpp \
		 EventKeyboard.cpp \
		 EventMouse.cpp \
		 InputManager.cpp \
		 EventCollision.cpp \
		 utility.cpp \
		 Character.cpp \
		 Wall.cpp \
		 WallManager.cpp \
		 Enemy.cpp \
		 Bouncer.cpp \
		 Block.cpp \
		 Rounder.cpp \
		 ObjectFactory.cpp \
		 PowerUp.cpp \
		 GameStart.cpp \
		 GameOver.cpp \
		 Points.cpp \
		 WallBox.cpp

GAME= game.cpp
EXECUTABLE= game		
OBJECTS= $(ENGSRC:.cpp=.o)

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(ENGSRC) 
	$(CC) $(GAME) $(OBJECTS) $(PLATFORM) -pg -o $@ -I$(INCPATH) $(LDFLAGS) 

.cpp.o: 
	$(CC) -c -g -pg $(DEBUG) -I$(INCPATH) -lm $(PLATFORM) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE


