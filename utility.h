//
// Utility functions to support Dragonfly and its games.
//
// Functions here do not use any attributes of any classes, so
// can stand alone.
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

// System includes
#include <sstream>		// for intToString()

// Engine includes
#include "Object.h"
#include "Position.h"

// Function prototypes
// Return true if two positions intersect.
bool positionsIntersect(Position p1, Position p2);

/* Returns pretty-formatted time as char * string.
char* getTimeString();	    

/* Convert world position to view position.
Position worldToView(Position world_pos);

// Convert view position to world position.
Position viewToWorld(Position view_pos);

// Convert integer to string, returning string.
string intToString(int number);*/

#endif // __UTILITY_H__
