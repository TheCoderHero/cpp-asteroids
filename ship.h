/******************************************************************************
* File: ship.h
* Author: John Tanner
*
* Description: The Ship class handles all of the actions for the SHIP object
******************************************************************************/

#ifndef ship_h
#define ship_h

#include "flyingObject.h"

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5



//SHIP CLASS
class Ship : public FlyingObject
{
private:
	//SHIP VARIABLE
	bool thrust;
public:
	//CONSTUCTOR
	Ship();

	//SETTERS
	void setThrust(bool thrust) { this->thrust = thrust; }

	//GETTERS
	bool getthrust() const { return thrust; }

	//GAME FUNCTIONS
	void draw() const;
	void moveLeft();
	void moveRight();
	void thrusters(Point point, float angle);
};

#endif /* ship_h */
