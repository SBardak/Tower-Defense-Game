#include "StrategyNearestExit.h"
#include "Path.h"


void StrategyNearestExit::findTarget(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange){
	Critter** critters = cm->getCritters();
	Critter* nearestExitCritter = nullptr;

	int towerX, towerY;
	towerX = t->getX();
	towerY = t->getY();
	int critterX, critterY;

	int minDistance = 0;
	int distance = 0;
	int distanceRange = 0;
	int numCritters = cm->getCritterTotalCount();

	Path* critterPath = nullptr;

	
	for (int j = 0; j < numCritters; ++j){
		// IF DEAD SKIP
		if (critters[j] == nullptr || critters[j]->GetState() == CritterState::Dead){
			continue;
		}
			
		critterX = critters[j]->getX() + 1;
		critterY = critters[j]->getY() + 1;

		critterPath = static_cast<Path*>(myGrid->getArr(critterY - 1, critterX - 1));

		// Set values of 1st critter in range
		if (minDistance == 0){
			distanceRange = (abs(towerX - critterX) + abs(towerY - critterY));
			// If range is good
			if (updatedRange >= distanceRange){
				nearestExitCritter = critters[j];

				while (critterPath->getNext() != nullptr){
					critterPath = critterPath->getNext();
					++minDistance;
				}
			}
				
		}
		else{ // Find min distance based on all critters
			distanceRange = (abs(towerX - critterX) + abs(towerY - critterY));
			distance = 0;
			while (critterPath->getNext() != nullptr){
				critterPath = critterPath->getNext();
				++distance;
			}
			if (distance < minDistance && updatedRange >= distanceRange){
				minDistance = distance;
				nearestExitCritter = critters[j];
			}
		}
	} 

	// Sets nearest exit critter if range is good and if there is a critter alive
	if (nearestExitCritter != nullptr){
		t->SetCurrentCritter(nearestExitCritter);
	}
	else
		t->SetCurrentCritter(nullptr);
	
}

string StrategyNearestExit::getName() const {
	return "Nearest to exit";
}