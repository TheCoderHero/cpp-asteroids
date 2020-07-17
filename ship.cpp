/******************************************************************************
* File: ship.cpp
* Description: Implementation of the SHIP class functions.
******************************************************************************/

#include "ship.h"
#include "uiDraw.h"

/******************************************************************************
* SHIP::SHIP
* Sets the initial conditions of the SHIP object
******************************************************************************/
Ship ::Ship()
{
	setThrust(false);
	setHitPoints(1);
}

/******************************************************************************
* SHIP::DRAW
* Draws a Ship at the given Point location
******************************************************************************/
void Ship::draw() const
{
	const Point point = location;
	drawShip(point, (int)angle, thrust);
}

/******************************************************************************
* SHIP::MOVE LEFT
* Rotates the Ship to the left
******************************************************************************/
void Ship::moveLeft()
{
	angle += ROTATE_AMOUNT;
}

/******************************************************************************
* SHIP::MOVE RIGHT
* Rotates the Ship to the right
******************************************************************************/
void Ship::moveRight()
{
	angle -= ROTATE_AMOUNT;
}

/******************************************************************************
* SHIP::THRUSTERS
* Moves the Ship forward at the given angle
******************************************************************************/
void Ship::thrusters(Point point, float angle)
{
	setPoint(point);
	float dx = (float)THRUST_AMOUNT * ((float)cos(M_PI / 180.0F * (angle + 90.0F)));
	float dy = (float)THRUST_AMOUNT * ((float)sin(M_PI / 180.0F * (angle + 90.0F)));
	speed.setDx(speed.getDx() + dx);
	speed.setDy(speed.getDy() + dy);
}
