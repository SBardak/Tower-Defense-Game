#include "TowerObserver.h"
#include "StrategyNearest.h"
#include "StrategyNearestExit.h"
#include "StrategyStrongest.h"
#include "StrategyWeakest.h"

TowerObserver::TowerObserver(Tower* t)
{
	this->t = t;
	this->t->Attach(this);
}


TowerObserver::~TowerObserver()
{
	this->t->Detach(this);
}

void TowerObserver::displayStats(){
	cout << endl << this->t->GetName() << endl;
	cout << "--------------------------" << endl;
	cout << "PosX : " << this->t->getX() << endl;
	cout << "PosY : " << this->t->getY() << endl;
	cout << "Cost : " << this->t->GetCost() << endl;
	cout << "Power : " << this->t->GetPower() << endl;
	cout << "Range : " << this->t->GetRange() << endl;
	cout << "Turns to attack : " << this->t->GetFireRate() << endl;
	cout << "Level : " << this->t->GetLevel() << endl;
	cout << "Cost to level up : " << this->t->GetCurrentLevelUpCost() << endl;
	cout << "Current refund value : " << this->t->GetCurrentRefundCost() << endl;
	cout << "Targeting strategy: " << this->getTower()->getStrategy()->getName() << endl;
	cout << "Effects: " << this->getTower()->GetEffects() << endl;
	
	cout << endl;
}

void TowerObserver::Update(){
	displayStats();
}

void TowerObserver::UpdateDecoratedTower(Tower* t){
	this->t = t;
}