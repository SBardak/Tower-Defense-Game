#include <stdlib.h>
#include "MapEntity.h"

MapEntity::MapEntity() {
    this->x = 0;
    this->y = 0;
}

MapEntity::MapEntity(const MapEntity& orig) {
    this->x = orig.x;
    this->y = orig.y;
	this->displayChar = orig.displayChar;
}

MapEntity::~MapEntity() {
    this->x = -1;
    this->y = -1;
}

bool MapEntity::isInRange(MapEntity me, int range) const{
    
    bool inXRange = false;
    bool inYRange = false;
    int xDiff;
    int yDiff;
    
    xDiff = abs(this->x - me.x);
    yDiff = abs(this->y - me.y);
    
    inXRange = !(xDiff > range);
    inYRange = !(yDiff > range);
    
    return inXRange && inYRange;
    
}

void MapEntity::SetPosition(int x, int y){
    if (x < 0)
        this->x = 0;
    else
        this->x = x;
    if (y < 0)
        this->y = 0;
    else
        this->y = y;

	Notify();
}

void MapEntity::setDisplayChar(char dc){
	this->displayChar = dc;
	Notify();
}

