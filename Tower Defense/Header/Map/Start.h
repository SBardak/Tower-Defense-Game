#ifndef _START_H_
#define _START_H_
#include <iostream>
#include "Path.h"
using namespace std;

class Start : public Path{
public:
	Start(int y, int x);
	virtual ~Start();
	inline virtual string getType() const { return "Start"; }
	virtual string print();
	inline int getX() const { return super::getX(); }
	inline int getY() const { return super::getY(); }

private:
	typedef Path super;
};

#endif _START_H_