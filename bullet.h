/*************************************************************
* File: bullet.h
* Author: John Tanner
*
* Description: The bullet class derived from a public Flying Object.
*************************************************************/

#ifndef bullet_h
#define bullet_h

#include "flyingObject.h"
#include "ship.h"
#include "uiDraw.h"

#define BULLET_SPEED 5
#define BULLET_LIFE 40

class Bullet : public FlyingObject
{
private:
	int counter;

public:
	Bullet();

	//SETTER
	void setCounter(int counter) { this->counter = counter; }

	//GETTER
	int getCounter() const { return counter; }

	//GAME FUNCTIONS
	void draw() const;
	void fire(Point point, float angle, Ship &ship);
};

#endif BULLET_H