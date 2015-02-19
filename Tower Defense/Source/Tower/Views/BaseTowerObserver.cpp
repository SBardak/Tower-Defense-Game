#include "BaseTowerObserver.h"
#include "StrategyNearest.h"
#include "StrategyNearestExit.h"
#include "StrategyStrongest.h"
#include "StrategyWeakest.h"

BaseTowerObserver::BaseTowerObserver(Tower* t) : TowerObserver(t)
{
}


BaseTowerObserver::~BaseTowerObserver()
{

}

void BaseTowerObserver::displayStats(){
	cout << endl << this->getTower()->GetName() << endl;
	cout << "--------------------------" << endl;
	cout << "Cost : " << this->getTower()->GetCost() << endl;
	cout << "Power : " << this->getTower()->GetPower() << endl;
	cout << "Range : " << this->getTower()->GetRange() << endl;
	cout << "Turns to attack : " << this->getTower()->GetFireRate() << endl;
	cout << "Level : " << this->getTower()->GetLevel() << endl;
	cout << "Cost to level up : " << this->getTower()->GetCurrentLevelUpCost() << endl;
	cout << "Targeting strategy: " << this->getTower()->getStrategy()->getName() << endl;
	cout << "Effects: " << this->getTower()->GetEffects() << endl;
	
	cout << endl;
	cout << endl;
}
