#pragma once
#include "SFML/Graphics.hpp"
#include "StoneColor.h"
class Stone;
class Board;

class Formation {
	bool isKilled;
	int liberties; //ces libertés ne sont pas forcément celles comptées par un humain (celles dans les angles comptent double, par exemple)
	Board& board;
	std::vector<std::shared_ptr<Stone>> stones;
public:
	//permet de réunir des formations existantes en une seule (doit accepter et ignorer les nullptr)
	//avec une map pour éviter les doublons
	Formation(Board& myBoard);
	Formation(std::shared_ptr<Stone> stone); //permet de créer une formation avec une seule pierre dedans
	void update();
	void addStoneNoUpdate(std::shared_ptr<Stone>);
	int getLiberties();
	void removeLast();
	std::vector<std::shared_ptr<Stone>> getStones();
	bool getIsKilled();
};