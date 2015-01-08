# Escape-Game

PLATFORM : CYGWIN
HOW TO COMPILE: Enter "make" in the cygwin terminal.
HOW TO RUN: "./game" After following the instructions for HOW TO COMPILE.

The game source revolves around the WallManager and ObjectFactory Objects. Once the game starts up, it leads the player to the Menu Screen. Once the player has pressed the 'P' key, the game begins and creates the two objects. 
The WallManager is responsible for creating the walls that descend from the top of the screen. 

The Wall Objects are responsible for deleting themselves when they move off-screen to free up memory for the next wall object to be created. 

The ObjectFactory is responsible for spawning the Character and the Enemies. 

The Enemies are generated with random values for speed and position so the game retains a fresh and arcade feel. 
The Character object responds to keyboard input and mainly clings to the walls upon collision. The wall jump mechanic is made possible by checking the keyboard input and making the appropriate jumps in response. The character has three different types of jumps: High Jumps, Regular Jumps, and Low Jumps, each allowing the player to reach different parts of the game world in any set of circumstances.

Upon Player Death, the character plays a death animation and the game procedes to the GameOver object which displays the text "Game Over" on the screen and then prompty ends the game.

The score is implemented via a an object which updates the score once every 30 steps. The score is static throughout with the exception of when the player acquires a power-up.

Power-Ups add special functionality to the game. The yellow power-up allows the player to receive double points over a period of time. The purple power-up grants the player invincibility. The green power-up allows the players to collide with the enemies without dying, essentially "eating" them.

Another feature that we added were the "WallBoxes" that appear in the middle of the game world. These objects act as walls but cause the player's death when collided with on the top or bottom. This is made clear by the difference in characters. The Wallboxes are there to provide more variety to the game rather than have the player simple jump between opposite walls constantly.

In addition, we also added pseudo-sprite animations. All of the animations seen in the game are built into the game code. This can be seen when the player collides with walls, when the player collides with power-ups, and through the enemy's default animations.

As a final touch, we've included cheat codes into the game. The "Z", "X", "C", "V" keys allow the player to shift between forms instantaneously with "V" allowing the player to revert to the original state.
