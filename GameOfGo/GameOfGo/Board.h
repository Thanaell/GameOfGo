#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include "Stone.h"
 class Board
{
	float margeSize;
	float caseSize;
	sf::Texture texture;
	sf::Sprite background;
	std::map<std::pair<int, int>, std::shared_ptr<Stone>> stoneMap;
public:
	float getCaseSize();
	Board();
	void draw(sf::RenderWindow& window);
	void putStone(Stone* stone);
	Stone* getStone(int x, int y);
	void removeFromMap(Stone* stone);

};