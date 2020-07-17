/******************************************************************************
* File: rocks.h
* Author: John Tanner
*
* Description: The Rock class is a base class for use with 3 other Rock Type
*	           objects (BIG ROCK, MEDIUM ROCK, SMALL ROCK). This file defines
*			   all of the functions to handle the ROCK actions.
******************************************************************************/

#ifndef rocks_h
#define rocks_h

#include "flyingObject.h"
#include <vector>
using namespace std;

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10


//ROCK CLASS
class Rock : public FlyingObject
{
private:
	//GAME VARIABLE
	int size;
public:
	//CONSTRUCTOR
	Rock() : FlyingObject() {}

	//SETTERS
	void setSize(int size) { this->size = size; }

	//GETTERS
	int getSize() { return size; }

	//GAME FUNCTION
	int randomAxis();

	//VIRTUAL FUNCTIONS
	virtual void rotate() = 0;
	virtual void breakRocks(vector<Rock*> & rock) = 0;
};

//BIG ROCK CLASS
class BigRock : public Rock
{
public:
	//CONSTRUCTOR
	BigRock();

	//GAME FUNCTIONS
	void draw() const;
	void rotate();
	void breakRocks(vector<Rock*> &rock);
};

//MEDIUM ROCK CLASS
class MediumRock : public Rock
{
public:
	//CONSTRUCTOR
	MediumRock();

	//GAME FUNCTIONS
	void draw() const;
	void rotate();
	void breakRocks(vector<Rock*> &rock);
};

//SMALL ROCK CLASS
class SmallRock : public Rock
{
public:
	//CONSTRUCTOR
	SmallRock();

	//GAME FUNCTIONS
	void draw() const;
	void rotate();
	void breakRocks(vector<Rock*> &rock);
};

#endif rocks_h