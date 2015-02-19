#ifndef _END_H_
#define _END_H_
#include <iostream>
#include "Path.h"
using namespace std;

class End : public Path{
public:
	End(int y, int x);
	virtual ~End();
	inline virtual string getType() const { return "End"; }
	virtual string print();
	inline int getX() const { return super::getX(); }
	inline int getY() const { return super::getY(); }
	
private:
	typedef Path super;
};

#endif _END_H_