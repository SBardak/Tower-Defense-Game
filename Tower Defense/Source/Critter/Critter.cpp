#include "Critter.h"

Critter::~Critter(){

};

void Critter::ApplyDamage(int dmgAmount){
	
	this->hitPoints -= dmgAmount;
	if (this->hitPoints <= 0){
		this->state = CritterState::Dead;
	}
	Notify();
}

CritterState Critter::GetState() const {
	return state;
}

void Critter::SetState(CritterState state){
	this->state = state;
}

void Critter::SetEffectType(EffectType et){
	this->currentEffectType = et;
}

void Critter::SetSpeed(int sp){
	this->speed = sp;
	if (this->speed < 1){
		this->speed = 1;
	}
	else
		Notify();
}