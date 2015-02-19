#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "Observer.h"

class Observable {
public:
	Observable();
	virtual ~Observable();
	void addObserver(Observer* obs);
	void removeObserver (Observer* obs);
protected:
	void notify() const;
private:
	Observer** observers;
	static const int maxObservers;
	int numObservers;
};

#endif /* OBSERVABLE_H_ */