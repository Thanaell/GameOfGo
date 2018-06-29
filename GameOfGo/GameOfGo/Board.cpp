#pragma once
#include "Board.h"
#include <iostream>

float Board::getCaseSize() {
	return caseSize;
}
void Board::draw(sf::RenderWindow& window) {
	window.draw(background);
	for (auto it : stoneMap) {
		it.second->draw(margeSize,caseSize,window);
	}
}

void Board::putStone(Stone* stone) {
	stoneMap.insert(std::pair<std::pair<int, int>, std::shared_ptr<Stone>>{std::pair<int, int>{stone->getX(),stone->getY()}, std::shared_ptr<Stone>(stone)});
}

Stone * Board::getStone(int x, int y)
{
	if (stoneMap.find(std::pair<int, int>{x, y}) != stoneMap.end()) {
		return stoneMap.find(std::pair<int, int>{x, y})->second.get();
	}
	return nullptr;
}

//le faire directement avec un shared_pointer ?
void Board::removeFromMap(Stone * stone){
	stoneMap.erase(std::pair<int, int>{stone->getX(), stone->getY()});
}

Board::Board(): margeSize(28.f),caseSize(46.f){
	if (!texture.loadFromFile("../background.png")) {
		std::cout << "erreur chargement image";
	}
	background.setTexture(texture);
	background.setScale(sf::Vector2f(2.0f, 2.f)); 
}