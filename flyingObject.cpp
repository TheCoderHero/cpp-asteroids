/******************************************************************************
* File: flyingObject.cpp
* Description: Implementation of the FLYINGOBJECT class functions.
*****************************************************************************/

#include "flyingObject.h"
#include "uiDraw.h"

/******************************************************************************
* FLYINGOBJECT::FLYINGOBJECT
* Sets the initial conditions for a FLYINGOBJECT object
*****************************************************************************/
FlyingObject::FlyingObject()
{
	location.setX(0.0F);
	location.setY(0.0F);
	speed.setDx(0.0F);
	speed.setDy(0.0F);
	setHitPoints(1);
	setPointValue(0);
	setLife(true);
	setAngle(0.0F);
}

/******************************************************************************
* FLYINGOBJECT::ADVANCE
* Adds a floating number to the X and Y position
*****************************************************************************/
void FlyingObject::advance()
{
	location.addY(speed.getDy());
	location.addX(speed.getDx());
}

/******************************************************************************
* FLYINGOBJECT::KILL
* Sets the object's life to false
*****************************************************************************/
void FlyingObject::kill()
{
	setLife(false);
}

/******************************************************************************
* FLYINGOBJECT::WRAP
* Moves an objects Point location to the other side of the screen
*****************************************************************************/
void FlyingObject::wrap()
{
	Point location = this->getPoint();
	if (location.getX() < -210.0F)
		location.setX(200.0F);
	if (location.getX() > 210.0F)
		location.setX(-200.0F);
	if (location.getY() < -210.0F)
		location.setY(200.0F);
	if (location.getY() > 210.0F)
		location.setY(-200.0F);
	this->setPoint(location);
}

/******************************************************************************
* UFO::UFO
* Sets the initial conditions for the UFO object
*****************************************************************************/
Ufo::Ufo()
{
	//Location
	int yAxis = random(-150, 150);
	location.setX(-210.0F);
	location.setY((float)yAxis);
	//Speed
	speed.setDx(3.0F);
	//Point Value
	setPointValue(10);
	//Life
	setLife(false);
}

/******************************************************************************
* UFO::DRAW
* Draws the UFO object to the screen
*****************************************************************************/
void Ufo::draw() const
{
	drawRect(location, 20, 5, 0);
	drawCircle(location, 8);
}

/******************************************************************************
* UFO::RESET POSITION
* Resets the UFO object's POINT location to the initial conditions
*****************************************************************************/
void Ufo::resetPosition()
{
	int yAxis = random(-150, 150);
	location.setX(-210.0F);
	location.setY((float)yAxis);
}