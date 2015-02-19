#include "CritterObserver.h"


CritterObserver::CritterObserver(Critter* c)
{
	this->c = c;
	this->c->Attach(this);
}


CritterObserver::~CritterObserver()
{
	this->c->Detach(this);
}

void CritterObserver::displayStats(){
	if (this->c->getHitPoints() > 0)
		cout << "Critter " << this->c->getID() << ": (" << this->c->getX() + 1 << ", " << this->c->getY() + 1
		<< ") HP: " << this->c->getHitPoints() << "  Speed: " << this->c->getSpeed()
		<< " Level: " << this->c->getLevel() << " Reward: " << this->c->getReward() << endl;
	else
		cout << "Critter " << this->c->getID() << " is dead! Earned $" << this->c->getReward()  << endl;
}

void CritterObserver::Update(){
	displayStats();
}