/******************************************************************************
* File: flyingObject.h
* Author: John Tanner
*
* Description: The Flying Object class is a base class for all 
*			   flying objects in the game
******************************************************************************/

#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"

#define M_PI 3.14

class FlyingObject
{
protected:
	//OBJECT VARIABLES
	Point location;
	Velocity speed;
	int hitPoints;
	int pointValue;
	bool life;
	float angle;

public:
	//CONSTRUCTOR
	FlyingObject();

	//SETTERS
	void setPoint(Point location)      { this->location = location;     }
	void setVelocity(Velocity speed)   { this->speed = speed;           }
	void setHitPoints(int hitPoints)   { this->hitPoints = hitPoints;   }
	void setPointValue(int pointValue) { this->pointValue = pointValue; }
	void setLife(bool life)            { this->life = life;             }
	void setAngle(float angle)         { this->angle = angle;           }

	//GETTERS
	Point getPoint()       const { return location;   }
	Velocity getVelocity() const { return speed;      }
	int getHitPoints()     const { return hitPoints;  }
	int getPointValue()    const { return pointValue; }
	bool getLife()         const { return life;       }
	float getAngle()       const { return angle;      }

	//GAME FUNCTIONS
	void wrap();
	void advance();
	void kill();

	//VIRTUAL FUNCTIONS
	virtual void draw() const = 0;
};

/***************************************
* UFO CLASS
***************************************/
class Ufo : public FlyingObject
{
public:
	//CONSTRUCTOR
	Ufo();

	//GAME FUNCTIONS
	void resetPosition();
	void draw() const;
};

#endif /* flyingObject_h */
