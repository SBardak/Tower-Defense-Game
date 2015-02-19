#include "Scenery.h"

const char Scenery::SCENERY_CHARACTER = '#';

Scenery::Scenery(int y, int x): posY(y), posX(x) {
	tow = nullptr;
}

Scenery::~Scenery(){
	delete tow;
	tow = nullptr;
}

string Scenery::print(){
	string s;
	if (tow != nullptr)
		s = tow->getDisplayChar();
	else
		s = SCENERY_CHARACTER;
	return s;
}

void Scenery::setTower(Tower* t){
	tow = t;
}

Tower* Scenery::getTower() const {
	return tow;
}