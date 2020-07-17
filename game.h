/******************************************************************************
* File: game.h
* Author: John Tanner
*
* Description: The Game class handles all of the actions of the Asteroids game.
*			   It creates objects and handles interaction between the player
*			   and the program.
******************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <limits>
#include <algorithm>
#include <vector>
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"
using namespace std;

class Game
{
public:
	//Constructor
	Game(Point tl, Point br);
	//Destructor
	~Game();

	//Game Logic Functions
	void handleInput(const Interface & ui);
	void advance();
	void draw(const Interface & ui);

private:
	//Screen Coordinates
	Point topLeft;
	Point bottomRight;

	//Game Variables
	int score;
	int frames;

	//Game Objects
	Ufo ufo;
	Ship ship;
	vector <Bullet> bullets;
	vector <Rock*> rocks;

	//Advance Objects on Screen
	void advanceBullets();
	void advanceShip();
	void advanceRocks(vector <Rock*> &rocks);
	void advanceUFO();

	//Game Logic Functions
	void createRocks(vector <Rock*> &rocks);
	void handleCollisions(vector<Rock*> &rocks);
	void cleanUpZombies();
	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
};

#endif /* GAME_H */
