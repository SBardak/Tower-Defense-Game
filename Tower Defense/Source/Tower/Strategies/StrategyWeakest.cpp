#include "StrategyWeakest.h"


void StrategyWeakest::findTarget(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange){
	Critter** critters = cm->getCritters();
	Critter* weakestCritter = nullptr;

	int towerX, towerY;
	towerX = t->getX();
	towerY = t->getY();
	int critterX, critterY;

	int lowestHP = 0;
	int hp = 0;
	int distanceRange = 0;
	int numCritters = cm->getCritterTotalCount();

	
		for (int j = 0; j < numCritters; ++j){
			// IF DEAD SKIP
			if (critters[j] == nullptr || critters[j]->GetState() == CritterState::Dead){
				continue;
			}
			critterX = critters[j]->getX() + 1;
			critterY = critters[j]->getY() + 1;

			// Set values to 1st critter
			if (lowestHP == 0){
				distanceRange = (abs(towerX - critterX) + abs(towerY - critterY));
				// Only if range is good
				if (updatedRange >= distanceRange){
					lowestHP = critters[j]->getHitPoints();
					weakestCritter = critters[j];
				}
			}
			else{ // Find weakest based on all critters
				distanceRange = (abs(towerX - critterX) + abs(towerY - critterY));
				hp = critters[j]->getHitPoints();
				if (hp < lowestHP && updatedRange >= distanceRange){
					lowestHP = hp;
					weakestCritter = critters[j];
				}
			}
		} 

		// Sets weakest critter if range is good and if there is a critter alive
		if (weakestCritter != nullptr){
			t->SetCurrentCritter(weakestCritter);
		}
		else
			t->SetCurrentCritter(nullptr);
}

string StrategyWeakest::getName() const {
	return "Weakest";
}