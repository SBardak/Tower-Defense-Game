#include "StrategyStrongest.h"


void StrategyStrongest::findTarget(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange){
	Critter** critters = cm->getCritters();
	Critter* strongestCritter = nullptr;

	int towerX, towerY;
	towerX = t->getX();
	towerY = t->getY();
	int critterX, critterY;

	int highestHP = 0;
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
			if (highestHP == 0){
				distanceRange = (abs(towerX - critterX) + abs(towerY - critterY));
				// Only if range is good
				if (updatedRange >= distanceRange){
					highestHP = critters[j]->getHitPoints();
					strongestCritter = critters[j];
				}
			}
			else{ // Find strongest based on all critters
				distanceRange = (abs(towerX - critterX) + abs(towerY - critterY));
				hp = critters[j]->getHitPoints();
				if (hp > highestHP && updatedRange >= distanceRange){
					highestHP = hp;
					strongestCritter = critters[j];
				}
			}
		} 
			
		// Sets strongest critter if range is good and if there is a critter alive
		if (strongestCritter != nullptr){
			t->SetCurrentCritter(strongestCritter);
		}
		else
			t->SetCurrentCritter(nullptr);
}

string StrategyStrongest::getName() const {
	return "Strongest";
}