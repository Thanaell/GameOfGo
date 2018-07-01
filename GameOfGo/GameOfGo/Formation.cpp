#include "Board.h"
#include "Stone.h"
#include "Formation.h"

void Formation::update(){
	liberties = 0;
	for (auto it : stones) {
		it.get()->updateLiberties();
		liberties += it->getLiberties();
	}
	if (liberties == 0) {
		isKilled = true;
		std::vector<std::pair<int, int>> oldStones; //vecteur temporaire pour permettre l'updtae
		for (auto it : stones) {
			oldStones.push_back({ it->getX(),it->getY() });
			board.removeFromMap(it.get());
		}
		//on update les formations des pierres adjacentes aux pierres supprimées
		for (auto it : oldStones) {
			if (board.getStone(it.first -1, it.second) != nullptr) {
				board.getStone(it.first - 1, it.second)->updateFormation();
			}
			if (board.getStone(it.first + 1, it.second) != nullptr) {
				board.getStone(it.first + 1, it.second)->updateFormation();
			}
			if (board.getStone(it.first, it.second - 1) != nullptr) {
				board.getStone(it.first, it.second - 1)->updateFormation();
			}
			if (board.getStone(it.first, it.second + 1) != nullptr) {
				board.getStone(it.first, it.second + 1)->updateFormation();
			}
		}
	}

}

void Formation::addStoneNoUpdate(std::shared_ptr<Stone> stone)
{
	stones.push_back(stone);
}

int Formation::getLiberties()
{
	return liberties;
}

std::vector<std::shared_ptr<Stone>> Formation::getStones()
{
	return stones;
}

bool Formation::getIsKilled()
{
	return isKilled;;
}


Formation::Formation(Board & myBoard): board(myBoard),isKilled(false)
{
}


Formation::Formation(std::shared_ptr<Stone> stone) : board(stone->getBoard()), liberties(stone->getLiberties()),isKilled(false){
	stones.push_back(stone);
}