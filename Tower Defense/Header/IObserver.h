#pragma once
/*
Observer interface. Should be inherited from any concrete Observer class.
*/

class IObserver
{
public:
	virtual ~IObserver();
	virtual void Update() = 0;

protected:
	IObserver();

};

