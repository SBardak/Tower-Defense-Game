#include "EffectUpgrade.h"


EffectUpgrade::EffectUpgrade(Tower* t, Effect* e) : Upgrade(t), effect(e)
{
}


EffectUpgrade::~EffectUpgrade()
{
	delete this->effect;
}

bool EffectUpgrade::AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange){
	if (Upgrade::AttackCritter(cm,p,myGrid, updatedFireRate, updatedPower, updatedRange)){
		if (this->GetCurrentCritter() != 0){
			this->effect->ApplyEffect(*this->GetCurrentCritter());
		}	
		return true;
	}
	return false;
}

void EffectUpgrade::ApplyEffectsAndDamage(Critter& c, CritterManager& cm, int updatedPower){
	Upgrade::ApplyEffectsAndDamage(c, cm, updatedPower);
	this->effect->ApplyEffect(c);
}

std::string EffectUpgrade::GetEffects(){
	return Upgrade::GetEffects() + this->effect->GetName();
}

int EffectUpgrade::GetCost() const{
	return Upgrade::GetCost() + 150;
}

int EffectUpgrade::GetCurrentRefundCost() const{
	return Upgrade::GetCurrentRefundCost() + (int)(ADDED_PRICE * Tower::REFUND_RATIO);
}
