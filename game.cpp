/******************************************************************************
 * File: game.cpp
 * Description: Implementation of the Game class functions.
 *****************************************************************************/

#include "game.h"
#include "uiDraw.h"

 /******************************************************************************
 * GAME::GAME
 * Set's the initial conditions for the game
 *****************************************************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br)
{
	// Set up the initial conditions of the game
	score  = 0;
	frames = 0;
	createRocks(rocks);
}

/******************************************************************************
* GAME::~GAME
* Deletes the allocated memory from the GAME class
*****************************************************************************/
Game :: ~Game()
{
	//Delete the Rock pointers
	int finalSize = rocks.size();
	for (int x = 0; x < finalSize; x++)
	{
 		delete rocks[x];
		rocks[x] = NULL;
	}
}

/******************************************************************************
* GAME::ADVANCE
* Handles advance function calls for all objects
*****************************************************************************/
void Game::advance()
{
	advanceBullets();
	advanceShip();
	advanceRocks(rocks);
	frames++;
	
	//Every 200 frames a UFO appears for BONUS points
	if (frames / 200 == 1 && !ufo.getLife())
	{
		ufo.resetPosition();
		ufo.setLife(true);
		frames = 0;
	}
	if (ufo.getLife())
	{
		advanceUFO();
		frames = 0;
	}
	handleCollisions(rocks);
	cleanUpZombies();
}

/******************************************************************************
* GAME::ADVANCE BULLETS
* Handles the BULLET object actions
*****************************************************************************/
void Game::advanceBullets()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		//If the bullet is alive...
		if (bullets[i].getLife())
		{
			//Call it's advance function
			bullets[i].advance();
			//Increase the bullet counter by 1 per frame
			bullets[i].setCounter(bullets[i].getCounter() + 1);
			//Handle screen wrap
			bullets[i].wrap();
		}
		//If the bullet's counter is greater than 40...
		if (bullets[i].getCounter() > BULLET_LIFE)
			//Kill it
			bullets[i].kill();
	}
}

/******************************************************************************
* GAME::ADVANCE SHIP
* Handles the SHIP object actions
*****************************************************************************/
void Game::advanceShip()
{
	//If the ship is alive...
	if (ship.getLife())
	{
		//Call it's advance function
		ship.advance();
		//Handle screen wrap
		ship.wrap();
	}
}

/******************************************************************************
* GAME::ADVANCE ROCKS
* Handles the ROCK object actions
*****************************************************************************/
void Game::advanceRocks(vector<Rock*> &rocks)
{
	for (vector<Rock*> ::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		//If the rock is alive...
		if ((*it)->getLife())
		{
			//Call it's advance function
			(*it)->advance();
			//Handle screen wrap
			(*it)->wrap();
			//Rotate the rock
			(*it)->rotate();
			//Draw it
			(*it)->draw();
		}
	}
}

/******************************************************************************
* GAME::ADVANCE UFO
* Handles the UFO object actions
*****************************************************************************/
void Game::advanceUFO()
{
	ufo.advance();
	Point location = ufo.getPoint();
	//If the UFO's location is off the screen...
	if (location.getX() > 210)
	{
		//Kill the UFO
		ufo.kill();
		//Reset it's position to the left side
		ufo.resetPosition();
	}
}

/******************************************************************************
* GAME::CREATE ROCKS
* Creates 5 initial BIGROCKS for the game
*****************************************************************************/
void Game::createRocks(vector <Rock*> &rocks)
{
	//Create the intial 5 BIG ROCKS
	Rock* newRock = NULL;
	while (rocks.size() < 5)
	{
		newRock = new BigRock();
		rocks.push_back(newRock);
		newRock = NULL;
	}
	//Delete the pointer to free memory
	delete newRock;
  newRock = NULL;
}

/******************************************************************************
* GAME::HANDLE COLLISIONS
* Handles all object interactions in the game
*****************************************************************************/
void Game::handleCollisions(vector<Rock*> &rocks)
{
	// BULLET COLLISION DETECTION
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		//If a bullet is alive...
		if (bullets[i].getLife())
		{
			//BULLET -> ROCK
			int vectorSize = rocks.size();
			for(int x = 0; x < vectorSize; x++)
			{
				//If the Rock* is alive...
				if (rocks[x]->getLife())
				{
					//If the bullet comes close enough to it...
					if(getClosestDistance(bullets[i], *rocks[x]) < rocks[x]->getSize())
					{
						//Increase the score by the Rock* point value
						score += rocks[x]->getPointValue();
						//Break the Rock into smaller rocks
						rocks[x]->breakRocks(rocks);
						//Kill the current rock
						rocks[x]->kill();
						//Kill the bullet
						bullets[i].kill();
					}
				}
			}

			//BULLET -> UFO
			//If the UFO is alive...
			if (ufo.getLife())
			{
				//If the bullet comes close enough to it...
				if(getClosestDistance(ufo, bullets[i]) < 10.0F)
				{
					//Increase the score by the UFO's point value
					score += ufo.getPointValue();
					//Kill the UFO
					ufo.kill();
					//Kill the bullet
					bullets[i].kill();
				}
			}
		}
	}

	//SHIP COLLISSION DETECTION
	// FOR SHIP -> ROCK
	for (vector<Rock*> ::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		//If the Rock* is alive...
		if ((*it)->getLife())
		{
			//If the ship gets too close to the Rock*...
			if(getClosestDistance(*(*it), ship) < (*it)->getSize())
			{
				//Kill the Ship
				ship.kill();
				//Kill the Rock
				(*it)->kill();
			}
		}
	}

	// FOR SHIP -> UFO
	if (ufo.getLife())
	{
		//If the ship gets too close to the UFO
		if (getClosestDistance(ufo, ship) < 10.0F)
		{
			//Kill the Ship
			ship.kill();
			//Kill the UFO
			ufo.kill();
		}
	}
}

/******************************************************************************
* GAME::CLEAN UP ZOMBIES
* Deletes all allocated memory for BULLET objects
******************************************************************************/
void Game::cleanUpZombies()
{
	// Look for dead bullets
	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		if (!bullet.getLife())
			bulletIt = bullets.erase(bulletIt);
		else
			bulletIt++;
	}
}

/******************************************************************************
* GAME::HANDLE INPUT
* Handles user interaction with the keyboard
******************************************************************************/
void Game::handleInput(const Interface & ui)
{
	// Change the direction of the ship
	if (ui.isLeft())
	{
		ship.moveLeft();
	}

	if (ui.isRight())
	{
		ship.moveRight();
	}

	if (ui.isUp())
	{
		float newAngle = ship.getAngle();
		Point location = ship.getPoint();
		ship.setThrust(true);
		ship.thrusters(location, newAngle);
	}
	else if (!ui.isUp())
		ship.setThrust(false);

	// Check for "Spacebar
	if (ui.isSpace())
	{
		Bullet newBullet;
		if (ship.getLife())
		{
			newBullet.fire(ship.getPoint(), ship.getAngle(), ship);
			bullets.push_back(newBullet);
		}
	}
}

/******************************************************************************
* GAME::DRAW
* Draws all objects onto the screen at the given Point locations
******************************************************************************/
void Game::draw(const Interface & ui)
{
	//Draw the UFO if it's alive
	if(ufo.getLife())
		ufo.draw();

	//Draw the Ship if it's alive
	if (ship.getLife())
		ship.draw();

	//Draw the bullets, if they are alive
	for (unsigned int i = 0; i < bullets.size(); i++)
		if (bullets[i].getLife())
			bullets[i].draw();

	//Put the score on the screen
	Point scoreLocation;
	scoreLocation.setX(topLeft.getX() + 5);
	scoreLocation.setY(topLeft.getY() - 5);

	drawNumber(scoreLocation, score);
}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                   obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                   obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}