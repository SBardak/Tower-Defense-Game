/*

BaseTowerObserver class
-----------------------
Basic view for the tower. Used for buying.


*/

#pragma once
#include "IObserver.h"
#include "Tower.h"
#include "TowerObserver.h"
class BaseTowerObserver : public TowerObserver 
{
public:
	BaseTowerObserver(Tower*);
	virtual ~BaseTowerObserver();

	void displayStats();
	

};

