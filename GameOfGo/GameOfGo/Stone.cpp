
#include "Stone.h"
#include "Board.h"
#include <iostream>
#include "Formation.h"
#include <map>
#include <set>

int Stone::getX() {
	return x;
}

int Stone::getY() {
	return y;
}

void Stone::updateFormation(){
	formation->update();
}

void Stone::updateLiberties(){
	liberties = 0;
	if (board.getStone(x - 1,y ) == nullptr) liberties++;
	if (board.getStone(x + 1, y) == nullptr) liberties++;
	if (board.getStone(x , y-1) == nullptr) liberties++;
	if (board.getStone(x , y+1) == nullptr) liberties++;
	//r�duction du nombre de libert�s en fonction du nombre de bords adjacents
	int nbSides = 0;
	if (x - 1 == -1 || x + 1 == 19) nbSides++;
	if (y - 1 == -1 || y + 1 == 19) nbSides++;
	liberties -= nbSides;
}

Board & Stone::getBoard()
{
	return board;
}

int Stone::getLiberties()
{
	return liberties;
}

void Stone::setFormation(std::shared_ptr<Formation> myFormation){
	formation = myFormation;
}

//TODO: gestion des kos
bool Stone::createStone(int x, int y, StoneColor color, Board& myBoard) {
	int kox = myBoard.getkoX();
	int koy = myBoard.getkoY();
	bool isKoUpdated = false;
	bool isStonePlaced = false;

	//on se d�barasse tout de suite du cas o� on clique sur une pierre d�j� existante, en dehors du plateau, ou sur le ko
	if (myBoard.getStone(x, y) != nullptr) return isStonePlaced;
	if (x < 0 || y < 0 || x>18 || y>18) return isStonePlaced;
	if (x == kox && y == koy) return isStonePlaced;

	//cr�ation de la nouvelle pierre
	std::shared_ptr<Stone> myStone=std::make_shared<Stone>(Stone(x, y, color, myBoard));

	//on cr�e un vecteur temporaire contenant les 4 pierres voisines (nullptr si pas de pierre)
	std::vector<Stone*> neighbours;
	neighbours.push_back(myBoard.getStone(x - 1, y));
	neighbours.push_back(myBoard.getStone(x + 1, y));
	neighbours.push_back(myBoard.getStone(x, y-1));
	neighbours.push_back(myBoard.getStone(x , y+1));
	
	int libertes = 0;
	int neighboursSame = 0;

	//calcul des libert�s et du nombre de voisins de la m�me couleur
	for (auto it : neighbours) {
		if (it != nullptr) {
			if (it->myColor == color) {
				neighboursSame++;
			}
		}
		else {
			libertes++;
		}
	}
	//r�duction du nombre de libert�s en fonction du nombre de bords adjacents
	int nbSides = 0;
	if (x - 1 == -1 || x + 1 == 19) nbSides++;
	if (y - 1 == -1 || y + 1 == 19) nbSides++;
	libertes -= nbSides;
	myStone->liberties = libertes;
	
	//gestion des formations
	std::set<std::shared_ptr<Formation>> oldFormations;
	std::set <std::shared_ptr<Formation>> oldFormationsCopy;
		for (auto it : neighbours) {
			if (it != nullptr && it->myColor == color) {
				oldFormations.insert(it->formation);
			}
		}
		//copie
		for (auto it : oldFormations) {
			std::shared_ptr<Formation> myFormation(new Formation(myBoard));
			for (auto stone : it->getStones()) {
				std::shared_ptr<Stone> newStone(new Stone(stone->x, stone->y, stone->myColor, myBoard));
				myFormation->addStoneNoUpdate(newStone);
			}
			oldFormationsCopy.insert(myFormation);
		}

		std::shared_ptr<Formation> newFormation(new Formation(myBoard));
		for (auto it : oldFormations) {
			for (auto oldStone : it->getStones()) {
				newFormation->addStoneNoUpdate(oldStone);
				oldStone->formation = newFormation;
			}
		}
		myStone->formation = newFormation;
		myStone->formation->addStoneNoUpdate(myStone);
		myBoard.putStone(myStone);
	//update global
	for (auto it : neighbours) {
		if (it != nullptr) {
			it->updateFormation();
		}
	}
	myStone->formation->update();

	//impossibilit� de placer une pierre � un endroit qui tue la formation
	if (myStone->formation->getIsKilled()==false) {
		isStonePlaced = true;
		}
	if (!isStonePlaced) {
		myBoard.removeFromMap(myStone.get());
		//on reforme les formations ant�rieures (r�cup�rer le set oldFormations original, et recr�er les formations supprim�es)
		for (auto it : oldFormationsCopy) {
			for (auto stoneToCreate: it->getStones()) {
				stoneToCreate->formation = it;
				myBoard.putStone(stoneToCreate);			
			}
		}
	}
	else {
		//d�terminer s'il y a un ko et changer le bool�en isKoUpdated en cons�quence
		//il y a un ko en x,y si la seule pierre enlev�e �tait en x y
		//d�terminer quelle est l'unique pierre enlev�e (s'il y en a une)
		//on compare les nouveaux voisins aux anciens, le ko est celui qui est � nullptr
		std::vector<Stone*> newNeighbours;
		newNeighbours.push_back(myBoard.getStone(x - 1, y));
		newNeighbours.push_back(myBoard.getStone(x + 1, y));
		newNeighbours.push_back(myBoard.getStone(x, y - 1));
		newNeighbours.push_back(myBoard.getStone(x, y + 1));
		int nbRemoved = 0;
		for (int i = 0; i < newNeighbours.size(); i++) {
			if (neighbours[i] != nullptr && neighbours[i]->formation->getStones().size() == 1 && newNeighbours[i] == nullptr ) {
				nbRemoved++;
				kox = neighbours[i]->x;
				koy = neighbours[i]->y;
			}
		}
		//si on a enlev� qu'un seul voisin, et que sa formation �tait de taille 1
		if (nbRemoved == 1){
			isKoUpdated = true;
		}
	}
		//si on a pos� une pierre sans g�n�rer de nouveau ko, on reset le ko en -1 -1
	if (!isKoUpdated) {
		kox = -1;
		koy = -1;
	}
	myBoard.setkoPosition(kox, koy);
	return isStonePlaced;
}

Stone::Stone(int xx, int yy, StoneColor color, Board& myBoard): x(xx), y(yy), myColor(color), board(myBoard) {
	switch (myColor) {
	case BLACK:
		myShape.setFillColor(sf::Color::Black);
		break;
	case WHITE:
		myShape.setFillColor(sf::Color::White);
		break;
	}
}

void Stone::draw(float marge, float sizeCase, sf::RenderWindow& window) {
	myShape.setPosition(sf::Vector2f(marge + x * sizeCase -sizeCase/2,marge +y*sizeCase-sizeCase/2));
	myShape.setRadius(sizeCase *0.48);
	window.draw(myShape);
}