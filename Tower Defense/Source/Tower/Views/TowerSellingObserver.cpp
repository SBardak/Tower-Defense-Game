#include "TowerSellingObserver.h"
#include "Utility.h"


TowerSellingObserver::TowerSellingObserver(TowerManager* tm) : TowerManagementObserver(tm)
{
}


TowerSellingObserver::~TowerSellingObserver()
{
}

void TowerSellingObserver::initController(){

	int res = -1;
	int quitOption = 0;

	do {
		quitOption = this->getTowerManager()->getTowers().size();
		cout << "Which tower do you want to sell (" << quitOption << " to exit): ";
		Utility::getInt(res);

		if (res < quitOption && res >= 0){
			this->getTowerManager()->SellTower(this->getTowerManager()->getTowers()[res]);
		}

	} while (res != quitOption);

}