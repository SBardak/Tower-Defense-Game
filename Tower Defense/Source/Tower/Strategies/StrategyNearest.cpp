#include "StrategyNearest.h"

void StrategyNearest::findTarget(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange){
	Critter** critters = cm->getCritters();
	Critter* nearestCritter = nullptr;
	
	int towerX, towerY;
	towerX = t->getX();
	towerY = t->getY();
	int critterX, critterY;

	int minDistance = 0;
	int distance = 0;
	int numCritters = cm->getCritterTotalCount();  

	for (int j = 0; j < numCritters; ++j){
		// IF DEAD SKIP
		if (critters[j] == nullptr || critters[j]->GetState() == CritterState::Dead){
			continue;
		}
		critterX = critters[j]->getX() + 1;
		critterY = critters[j]->getY() + 1;

		// Set values to 1st critter
		if (minDistance == 0){
			minDistance = (abs(towerX - critterX) + abs(towerY - critterY));
			if (updatedRange >= minDistance)
				nearestCritter = critters[j];
		}
		else{ // Find min distance based on all critters
			distance = (abs(towerX - critterX) + abs(towerY - critterY));
			if (distance < minDistance && t->GetRange() >= distance){
				minDistance = distance;
				nearestCritter = critters[j];
			}
		}
	}
	
	// Set nearest critter if range is good and if there is a critter alive
	if (nearestCritter != nullptr)
		t->SetCurrentCritter(nearestCritter);
	else
		t->SetCurrentCritter(nullptr);
		
}

string StrategyNearest::getName() const {
	return "Nearest to tower";
}