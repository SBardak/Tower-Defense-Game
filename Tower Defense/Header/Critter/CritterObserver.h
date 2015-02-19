#pragma once
#include "IObserver.h"
#include "Critter.h"
class CritterObserver : public IObserver
{
public:
	CritterObserver(Critter*);
	virtual ~CritterObserver();

	virtual void displayStats();

	virtual void Update();

private:
	Critter* c;

protected:
	Critter* const getTower() const { return this->c; }

};
