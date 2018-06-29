#pragma once
#include "Board.h"
class Game
{
public:
	Game();
	void run();
private:
	StoneColor colorToPlay;
	Board myBoard;
	sf::RenderWindow window;
	void processEvents();
	void render();
};