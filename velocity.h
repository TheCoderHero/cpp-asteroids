/******************************************************************************
* File: velocity.h
* Author: John Tanner
*
* Description: The Velocity class handles speeds for all objects in the game
******************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float x;
	float y;
public:

	//Default Constructor
	Velocity() : x(0.0F), y(0.0F) {}
	Velocity(float x, float y);

	//Setters
	void setDx(float x) { this->x = x; }
	void setDy(float y) { this->y = y; }

	//Getters
	float getDx() const { return x; }
	float getDy() const { return y; }

};

#endif VELOCITY_H
