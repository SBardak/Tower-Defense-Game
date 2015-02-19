/*

TowerSellingObserver class
-----------------------
View for the TowerManager. The controller is not seperated into another because it is not enough complex. The controller manages the view and model to provide selling capabilities to a user.

*/

#pragma once
#include "TowerManagementObserver.h"
#include "TowerManager.h"

class TowerSellingObserver : public TowerManagementObserver
{
public:
	TowerSellingObserver(TowerManager* tm);
	virtual ~TowerSellingObserver();

	void initController();

private:
	
};

