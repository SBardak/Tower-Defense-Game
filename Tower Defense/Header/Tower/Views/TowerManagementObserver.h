/*

TowerLevelUpObserver class
-----------------------
Base view for the TowerManager. The controller is not seperated into another because it is not enough complex. The controller manages the view and model to provide leveling up capabilities to a user.

*/

#pragma once
#include "IObserver.h"
#include "TowerManager.h"
#include "Grid.h"
class TowerManagementObserver : public IObserver
{
public:
	TowerManagementObserver(TowerManager* tm);
	virtual ~TowerManagementObserver();

	void Update();
	void display();
	
	virtual void initController() ;

private:
	TowerManager* towerMan;

protected:

	TowerManager* getTowerManager() const { return this->towerMan; }
};

