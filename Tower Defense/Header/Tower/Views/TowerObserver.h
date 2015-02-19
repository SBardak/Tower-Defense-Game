/*

BaseTowerObserver class
-----------------------
Basic view for the tower. Used to inspect.


*/

#pragma once
#include "IObserver.h"
#include "Tower.h"
class TowerObserver : public IObserver
{
public:
	TowerObserver(Tower*);
	virtual ~TowerObserver();

	virtual void displayStats();

	
	virtual void Update();

	void UpdateDecoratedTower(Tower*);

private:
	Tower* t;

protected:
	Tower* const getTower() const { return this->t; }

};

