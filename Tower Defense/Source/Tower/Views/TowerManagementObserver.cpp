#include "TowerManagementObserver.h"
#include "Utility.h"

TowerManagementObserver::TowerManagementObserver(TowerManager* tm){
	towerMan = tm;
	tm->Attach(this);
}


TowerManagementObserver::~TowerManagementObserver()
{
	this->towerMan->Detach(this);
}

void TowerManagementObserver::display(){
	cout << *const_cast<Grid*>((this->towerMan->getMap()));

	cout << "Player's currency : " << this->towerMan->getPlayer()->getCurrency() << endl << endl;

	std::vector<Tower*> towers = this->towerMan->getTowers();

	if (towers.empty()){
		cout << "There are no towers on the field at the moment..." << endl << endl;
	}
	else{
		cout << "Current Towers on the field :" << endl << endl;
		int index = 0;
		for (std::vector<Tower*>::iterator i = towers.begin(); i != towers.end(); ++i, ++index){
			cout << index << ". " << towers[index]->GetName() << ", X : " << towers[index]->getX() << ", Y : " << towers[index]->getY() << ", Level : " << towers[index]->GetLevel() << ", Refund Value : " << towers[index]->GetCurrentRefundCost() << ", Level up : " << towers[index]->GetCurrentLevelUpCost() << endl;
		}
		cout << endl;
	}
}

void TowerManagementObserver::Update(){
	display();
}

void TowerManagementObserver::initController(){
	int res = -1;
	int quitOption = 0;

	do {
		quitOption = this->getTowerManager()->getTowers().size();
		cout << "Which tower do you want to inspect : (" << quitOption << " to exit): ";
		Utility::getInt(res);

		if (res < quitOption && res >= 0){
			this->getTowerManager()->Inspect(res);
			Update(); //Simply to redisplay the view since we're in console, the old output becomes hidden.
		}

	} while (res != quitOption);
}
