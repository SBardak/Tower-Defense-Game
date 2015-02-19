/*

TowerBuyObserver class
-----------------------
View for the TowerManager. The controller is not seperated into another because it is not enough complex. The controller manages the view and model to provide buying capabilities to a user.

*/

#pragma once
#include "TowerManagementObserver.h"
#include "TowerManager.h"
class TowerBuyObserver : public TowerManagementObserver
{
public:
	TowerBuyObserver(TowerManager*);
	virtual ~TowerBuyObserver();

	TowerTypes displayTypeMenu();
	void initController(Grid* grid);

	void Update();
};

