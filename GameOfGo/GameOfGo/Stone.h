#pragma once
#include "SFML/Graphics.hpp"
#include "StoneColor.h"

class Board;
class Formation;

class Stone {
	sf::CircleShape myShape;
	StoneColor myColor;
	int x;
	int y;
	int liberties;
	Board& board;
	std::shared_ptr<Formation> formation;
public:
	static bool createStone(int x, int y, StoneColor color, Board& myBoard);
	Stone(int xx, int yy, StoneColor color, Board& myBoard);
	void draw(float marge, float sizeCase, sf::RenderWindow& window);
	int getX();
	int getY();
	void updateFormation();
	void updateLiberties();
	Board& getBoard();
	int getLiberties();
	void setFormation(std::shared_ptr<Formation>);

};