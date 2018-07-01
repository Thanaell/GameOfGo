#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include "Stone.h"
 class Board
{
	//position du ko, à -1 -1 s'il n'y en a pas
	int kox;
	int koy;
	float margeSize;
	float caseSize;
	sf::Texture texture;
	sf::Sprite background;
	std::map<std::pair<int, int>, std::shared_ptr<Stone>> stoneMap;
public:
	float getCaseSize();
	Board();
	void draw(sf::RenderWindow& window);
	void putStone(std::shared_ptr<Stone>);
	Stone* getStone(int x, int y);
	void removeFromMap(Stone* stone);
	int getkoX();
	int getkoY();
	void setkoPosition(int x, int y);
	

};