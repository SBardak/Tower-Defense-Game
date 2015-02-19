#ifndef _PATH_H_
#define _PATH_H_
#include <iostream>
#include "MapObject.h"
#include "Critter.h"

class Grid;

using namespace std;

class Path : public MapObject{
public:
	Path(int y, int x);
	virtual ~Path();
	inline virtual string getType() const { return "Path"; }
	virtual string print();
	void setPrev(Path* prev);
	void setNext(Path* next);
	Path* getPrev() const;
	Path* getNext() const;
	inline int getX() const { return posX; }
	inline int getY() const { return posY; }
	void setCritter(Critter* c);
	void removeCritter();
	Critter** getCritter() const;

protected:
	int posX;
	int posY;
	Path* prev;
	Path* next;
	Critter** crit;
};

#endif _PATH_H_