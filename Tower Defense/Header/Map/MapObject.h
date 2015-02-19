#ifndef _MAPOBJECT_H_
#define _MAPOBJECT_H_
#include <iostream>
#include "Observable.h"
using namespace std;

// Pure Abstract class
class MapObject {
public:
	inline virtual string getType() const = 0;
	virtual string print() = 0;
};

#endif _ELEMENT_H_