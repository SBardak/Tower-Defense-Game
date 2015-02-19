#ifndef CRITTER_FACTORY_H
#define CRITTER_FACTORY_H
#include "Critter.h"
#include "CritterManager.h"
#include "Grid.h"

class CritterFactory {

public: 
	CritterFactory(CritterManager* cm, Grid* grid) { this->cm = cm;  this->grid = grid; };
	virtual ~CritterFactory() {};
	void createCritter(int waveLevel);

private:
	CritterManager* cm;
	Grid* grid;
};

#endif