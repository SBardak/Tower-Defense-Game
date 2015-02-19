/*

BasicTower class
------------
Bsae class for observable objects

*/

#pragma once
#include <list>
#include "IObserver.h"

/*
Base Model for every observable model.
Simply allow to attach, detach and notify observers. 
*/

class BaseModel
{
public:
	BaseModel();
	virtual ~BaseModel();
	virtual void Attach(IObserver* o);
	virtual void Detach(IObserver* o);
	virtual void Notify();
	std::list<IObserver*>* GetObservers();
private:
	std::list<IObserver*> *observers;


protected:
	
};

