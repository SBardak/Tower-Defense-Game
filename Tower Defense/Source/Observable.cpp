#include "Observable.h"
#include <iostream>

const int Observable::maxObservers = 10;

Observable::Observable() {
	observers = new Observer*[maxObservers];
			for (int i = 0; i < maxObservers; ++i)
				observers[i] = NULL;
			numObservers = 0;
}

Observable::~Observable() {
	delete[] observers;
}

void Observable::addObserver(Observer* obs) {
	if (numObservers == maxObservers) return;
	//check if already in
	for (int i = 0; i < maxObservers; ++i) {
		if (observers[i]==obs) {
			return;
		}
	}
	observers[numObservers] = obs;
	++numObservers;
}

void Observable::removeObserver(Observer* o) {
	for (int i = 0; i < 10; ++i)
		if (observers[i] == o){
			observers[i] = nullptr;
			break;
		}
}

void Observable::notify() const {
	for (int i = 0; i < numObservers; ++i) 
			observers[i]->update();
}
