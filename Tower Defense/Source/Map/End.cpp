#include "End.h"
#include "CritterManager.h"


End::End(int y, int x): super(y,x){
	
}

End::~End(){
	Path::~Path();
}

string End::print(){
	string s = "E";
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

