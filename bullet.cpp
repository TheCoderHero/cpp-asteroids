/******************************************************************************
* File: bullet.cpp
* Description: Implementation of the BULLET class functions.
*****************************************************************************/

#include "bullet.h"

/******************************************************************************
* BULLET::BULLET
* Sets the initial configuration for BULLET objects
*****************************************************************************/
Bullet::Bullet()
{
	setCounter(0);
	setHitPoints(1);
}

/******************************************************************************
* BULLET::DRAW
* Draws a dot at a specific POINT location
*****************************************************************************/
void Bullet::draw() const
{
	drawDot(location);
}

/******************************************************************************
* BULLET::FIRE
* Advances the BULLET object based on the SHIP objects speed and angle
*****************************************************************************/
void Bullet::fire(Point point, float angle, Ship &ship)
{
	setPoint(point);
	Velocity shipSpeed = ship.getVelocity();
	if (shipSpeed.getDx() < 0)
		shipSpeed.setDx(shipSpeed.getDx() * -1);
	if (shipSpeed.getDy() < 0)
		shipSpeed.setDy(shipSpeed.getDy() * -1);
	float dx = (shipSpeed.getDx() + BULLET_SPEED) * ((float)cos(M_PI / 180.0 * (angle + 90)));
	float dy = (shipSpeed.getDy() + BULLET_SPEED) * ((float)sin(M_PI / 180.0 * (angle + 90)));
	speed.setDx(dx);
	speed.setDy(dy);
}