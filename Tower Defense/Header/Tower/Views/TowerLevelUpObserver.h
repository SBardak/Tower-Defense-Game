/*

TowerLevelUpObserver class
-----------------------
View for the TowerManager. The controller is not seperated into another because it is not enough complex. The controller manages the view and model to provide leveling up capabilities to a user.

*/

#pragma once
#include "TowerManagementObserver.h"
#include "TowerManager.h"

class TowerLevelUpObserver : public TowerManagementObserver
{
public:
	TowerLevelUpObserver(TowerManager* tm);
	virtual ~TowerLevelUpObserver();

	void initController();

private:
};

