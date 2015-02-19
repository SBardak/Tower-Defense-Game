#pragma once
#include "CritterManager.h"
#include "Tower.h"
#include "Grid.h"
#include <string>


class Strategy{
public: 
	virtual ~Strategy() {};
	virtual void findTarget(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange) = 0;
	virtual string getName() const = 0;
};