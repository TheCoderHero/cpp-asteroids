/******************************************************************************
* File: bullet.cpp
* Description: Implementation of the BULLET class functions.
*****************************************************************************/

#include "rocks.h"
#include "uiDraw.h"

/******************************************************************************
* ROCK::RANDOM AXIS
* Used to set the initial Point location of the Asteroids
*****************************************************************************/
int Rock::randomAxis()
{
	int axis;
	do
	{
		axis = random(-200, 200);
	} while (axis > -100 && axis < 100);
	return axis;
}

/******************************************************************************
* BIGROCK::BIGROCK
* Sets the initial conditions of a BIGROCK object
*****************************************************************************/
BigRock::BigRock()
{
	location.setX((float)randomAxis());
	location.setY((float)randomAxis());
	int angleA = random(-360, 360);
	int angleB = random(-360, 360);
	speed.setDx((float)(cos(3.14 / 180.0 * angleA)));
	speed.setDy((float)(sin(3.14 / 180.0 * angleB)));
	setPointValue(10);
	setSize(BIG_ROCK_SIZE);
}

/******************************************************************************
* BIGROCK::DRAW
* Draws a Large Asteroid at the Point location
*****************************************************************************/
void BigRock::draw() const
{
	drawLargeAsteroid(location, (int)angle);
}

/******************************************************************************
* BIGROCK::ROTATE
* Adds a value to the angle to hndle the rotation of the rock
*****************************************************************************/
void BigRock::rotate()
{
	angle += BIG_ROCK_SPIN;
}

/******************************************************************************
* BIGROCK::BREAK ROCKS
* When the Asteroid is hit, 2 MEDIUMROCK objects are created and 1 SMALLROCK
* object is created and conditions are set for them.
******************************************************************************/
void BigRock::breakRocks(vector<Rock*> &rock)
{
	Rock* newRock = NULL;
	Velocity* newSpeed = NULL;
	newRock = new MediumRock();
	newRock->setPoint(this->getPoint());
	newSpeed = new Velocity(this->speed.getDx(), (this->speed.getDy() + 1.0F));
	newRock->setVelocity(*newSpeed);
	rock.push_back(newRock);
	newRock = NULL;
	newSpeed = NULL;
	newRock = new MediumRock();
	newRock->setPoint(this->getPoint());
	newSpeed = new Velocity(this->speed.getDx(), (this->speed.getDy() - 1.0F));
	newRock->setVelocity(*newSpeed);
	rock.push_back(newRock);
	newRock = NULL;
	newSpeed = NULL;
	newRock = new SmallRock();
	newRock->setPoint(this->getPoint());
	newSpeed = new Velocity((this->speed.getDx() + 1.0F), this->speed.getDy());
	newRock->setVelocity(*newSpeed);
	rock.push_back(newRock);
	newRock = NULL;
	newSpeed = NULL;
	delete newRock;
	delete newSpeed;
}

/******************************************************************************
* MEDIUMROCK::MEDIUMROCK
* Sets the initial conditions of a MEDIUMROCK object
*****************************************************************************/
MediumRock::MediumRock()
{
	setSize(MEDIUM_ROCK_SIZE);
	setPointValue(15);
}

/******************************************************************************
* MEDIUMROCK::DRAW
* Draws a Medium Asteroid at the given Point location
*****************************************************************************/
void MediumRock::draw() const
{
	drawMediumAsteroid(location, (int)angle);
}

/******************************************************************************
* MEDIUMROCK::ROTATE
* Adds a value to the angle to hndle the rotation of the rock
*****************************************************************************/
void MediumRock::rotate()
{
	angle += MEDIUM_ROCK_SPIN;
}

/******************************************************************************
* MEDIUMROCK::BREAK ROCKS
* When the Asteroid is hit, 2 SMALLROCK objects are created and conditions are
* set for them.
******************************************************************************/
void MediumRock::breakRocks(vector<Rock*> &rock)
{
	Rock* newRock = NULL;
	Velocity* newSpeed = NULL;
	newRock = new SmallRock();
	newRock->setPoint(this->getPoint());
	newSpeed = new Velocity((this->speed.getDx() + 3.0F), this->speed.getDy());
	newRock->setVelocity(*newSpeed);
	rock.push_back(newRock);
	newRock = NULL;
	newSpeed = NULL;
	newRock = new SmallRock();
	newRock->setPoint(this->getPoint());
	newSpeed = new Velocity((this->speed.getDx() - 3.0F), this->speed.getDy());
	newRock->setVelocity(*newSpeed);
	rock.push_back(newRock);
	newRock = NULL;
	newSpeed = NULL;
	delete newRock;
	delete newSpeed;
}

/******************************************************************************
* SMALLROCK::SMALLROCK
* Sets the initial conditions of the SMALLROCK object
******************************************************************************/
SmallRock::SmallRock()
{
	setSize(SMALL_ROCK_SIZE);
	setPointValue(20);
}

/******************************************************************************
* SMALLROCK::DRAW
* Draws a Small Asteroid on the screen at the Point location
******************************************************************************/
void SmallRock::draw() const
{
	drawSmallAsteroid(location, (int)angle);
}

/******************************************************************************
* SMALLROCK::BREAK ROCKS
* When a small rock is hit, this funciton kills the rock
******************************************************************************/
void SmallRock::breakRocks(vector<Rock*> &rock)
{
	kill();
}

/******************************************************************************
* SMALLROCK::ROTATE
* Adds a value to the angle to hndle the rotation of the rock
******************************************************************************/
void SmallRock::rotate()
{
	angle += SMALL_ROCK_SPIN;
}