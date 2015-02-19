#ifndef _SCENERY_H_
#define _SCENERY_H_
#include <iostream>
#include "MapObject.h"
#include "Tower.h"
using namespace std;

class Scenery : public MapObject {
public:
	Scenery(int y, int x);
	virtual ~Scenery();
	inline virtual string getType() const { return "Scenery"; }
	virtual string print();
	void setTower(Tower* t);
	Tower* getTower() const;   

	static const char SCENERY_CHARACTER;

private:
	int posX;
	int posY;
	Tower* tow;
};

#endif _SCENERY_H_