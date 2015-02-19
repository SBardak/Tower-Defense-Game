#include "CritterManager.h"
#include "Game.h"

const int CritterManager::MAXNUMCRITTERS = 25;

CritterManager::CritterManager(int y, int x, Player* p){
	startX = x;
	startY = y;
	critterAliveCount = 0;
	critterSpawnCount = 0;
	critterTotalCount = 0;
	critterID = 0;
	critters = new Critter*[CritterManager::MAXNUMCRITTERS];
	this->p = p;

	for (int i = 0; i < CritterManager::MAXNUMCRITTERS; ++i){
		critters[i] = nullptr;
	}

	this->observers = new std::vector<CritterObserver*>();
}

CritterManager::~CritterManager(){
	for (int i = 0; i < MAXNUMCRITTERS; ++i){
		delete critters[i];
	}
	delete critters;
}

void CritterManager::resetCritterID(){
	critterID = 0;
}

void CritterManager::setCritterAliveCount(int critterAliveCount){
	this->critterAliveCount = critterAliveCount;
}

void CritterManager::initializeWave(int x){
	critterSpawnCount = x;
	critterAliveCount = x;
	critterTotalCount = x;
}

void CritterManager::spawnCritter(Grid* myGrid, int currentLevel) {
	Critter* c = new Critter(++critterID, currentLevel * 10, currentLevel, currentLevel, currentLevel * 50, startX, startY); 
	this->observers->push_back(new CritterObserver(c));
	myGrid->setCritter(startY + 1, startX + 1, c);
	critters[critterTotalCount - critterSpawnCount] = c;
	--critterSpawnCount;
}

void CritterManager::moveCritters(Grid* myGrid) {
	int x;
	if (critterSpawnCount > 0)
		x = critterTotalCount - critterSpawnCount;
	else
		x = critterTotalCount;

	// For all critters in manager
	for (int i = 0; i < x; ++i){ 
		// If critter is alive (set current (x,y) to path.getNext() (x,y))
		if (critters[i]->getHitPoints() > 0){ 
			int x = critters[i]->getX();
			int y = critters[i]->getY();

			Path* temp = static_cast<Path*>(myGrid->getArr(y, x));
			temp->removeCritter();

			int nextX, nextY;

			// Move by the critter's speed
			for (int j = 0; j < critters[i]->getSpeed(); ++j){
				// Check if we reached the end
				if (temp->getNext() != nullptr) {
					nextX = temp->getNext()->getX();
					nextY = temp->getNext()->getY();
					temp = temp->getNext();
					
				}
				else {  // Critter reached the end cell
					temp = nullptr;
					critters[i]->setHitPoints(0);
					critters[i]->SetState(CritterState::Dead);
					--critterAliveCount;
					p->decrementLives();
					break;
				}
			}
			// Set critter to its final position (have to re-check if it reached the end)
			if (temp != nullptr) {
				temp->setCritter(critters[i]);
				critters[i]->setX(nextX);
				critters[i]->setY(nextY);
			}
		}
	}	
}