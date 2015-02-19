#include "TowerLevelUpObserver.h"
#include "Utility.h"


TowerLevelUpObserver::TowerLevelUpObserver(TowerManager* tm) : TowerManagementObserver(tm)
{
}


TowerLevelUpObserver::~TowerLevelUpObserver()
{
}

void TowerLevelUpObserver::initController(){

	int res = -1;
	int quitOption = 0;

	do {
		quitOption = this->getTowerManager()->getTowers().size();
		cout << "Which tower do you want to level up (" << quitOption << " to exit): ";
		Utility::getInt(res);

		if (res < quitOption && res >= 0){
			this->getTowerManager()->LevelUpTower(res);
		}

	} while (res != quitOption);

}
