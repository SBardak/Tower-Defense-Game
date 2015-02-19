#include "Start.h"
#include "CritterManager.h"

Start::Start(int y, int x): super(y,x) {
	
}

Start::~Start(){
	Path::~Path();
}

string Start::print(){
	string s = "S";
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

