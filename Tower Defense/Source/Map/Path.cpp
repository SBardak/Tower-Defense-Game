#include "Path.h"
#include "CritterManager.h"

Path::Path(int y, int x): posY(y), posX(x){
	crit = new Critter*[CritterManager::MAXNUMCRITTERS];

	for (int i = 0; i < CritterManager::MAXNUMCRITTERS; ++i){
		crit[i] = nullptr;
	}
}

Path::~Path(){
	delete [] crit;
	crit = nullptr;
}

string Path::print(){
	string s = " ";
	for (int i = 0; i < CritterManager::MAXNUMCRITTERS; ++i){
		if (crit[i] != nullptr){
			if (crit[i]->GetState() == CritterState::Alive){
				s = "C";
				break;
			}
		}
	}
	return s;
}

void Path::setPrev(Path* prev){
	this->prev = prev;
}

void Path::setNext(Path* next){
	this->next = next;
}

Path* Path::getPrev() const {
	return prev;
}

Path* Path::getNext() const{
	return next;
}

void Path::setCritter(Critter* c){
	for (int i = 0; i < CritterManager::MAXNUMCRITTERS; ++i){
		if (crit[i] == nullptr){
			crit[i] = c;
			break;
		}
	}
}

void Path::removeCritter(){ 
	for (int i = 0; i < CritterManager::MAXNUMCRITTERS; ++i){
		if (crit[i] != nullptr){
			if (crit[i]->GetState() == CritterState::Alive){
				crit[i] = nullptr;
				break;
			}
		}
	}
}

Critter** Path::getCritter() const {
	return crit;
}

