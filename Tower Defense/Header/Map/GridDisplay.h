#pragma once

#include "Grid.h"
#include "Observer.h"

class GridDisplay: public Observer {
public:
	GridDisplay(Grid* grid);
	virtual ~GridDisplay();
	void update();

private:
	Grid* grid;
};
