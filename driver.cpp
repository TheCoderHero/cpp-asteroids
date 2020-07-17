#include "game.h"

void callBack(const Interface *pUI, void *p);

int main(int argc, char ** argv)
{
   Point topLeft(-200, 200);
   Point bottomRight(200, -200);
   
   Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
   Game game(topLeft, bottomRight);
   ui.run(callBack, &game);
   
   return 0;
}

void callBack(const Interface *pUI, void *p)
{
	Game *pGame = (Game *)p;

	pGame->advance();
	pGame->handleInput(*pUI);
	pGame->draw(*pUI);
}
