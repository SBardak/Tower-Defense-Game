#include "SplashUpgrade.h"


SplashUpgrade::SplashUpgrade(Tower* t, int range) :Upgrade(t)
{
	if (range < 0)
		this->splashRange = 0;
	else
		this->splashRange = range;
}


SplashUpgrade::~SplashUpgrade()
{
}

//If the tower attacks a critter, it'll find the critters in the splash range and distribute the damage
bool SplashUpgrade::AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange){
	bool res = false;
	if (Upgrade::CanTowerHit(updatedFireRate)) {
		Upgrade::executeStrategy(this, cm, myGrid, updatedRange); // Sets currentCritter depending on strategy (or nullptr if none in range)
		if (this->GetCurrentCritter() != nullptr){
			Critter** critters = cm->getCritters();
			int currentCritX = this->GetCurrentCritter()->getX();
			int currentCritY = this->GetCurrentCritter()->getY();
			for (int i = 0; i < cm->getCritterTotalCount(); i++){
				if (critters[i] != nullptr && critters[i]->GetState() != CritterState::Dead){ // Only apply splash to alive critters
					int critX = critters[i]->getX();
					int critY = critters[i]->getY();
					int distance = abs(currentCritX - critX) + abs(currentCritY - critY);
					if (distance <= splashRange){ // Check if splash range is good between the 2 critters
						this->ApplyEffectsAndDamage(*critters[i], *cm, updatedPower);
						res = true;
						if (critters[i]->GetState() == CritterState::Dead){
							cm->setCritterAliveCount(cm->getCritterAliveCount() - 1);
							p->addCurrency(critters[i]->getReward());
						}
					}
				}
			}
		}
		else
		{
			cout << "No critters in range" << endl;
			return res;
		}
	}
	else{
		cout << "Cannot attack yet" << endl;
		return res;
	}
	return res;
}


bool SplashUpgrade::HasSplash() const {
	return true;
}

bool SplashUpgrade::TryToApplySplash(Tower*& t, int range){
	if (!t->HasSplash()){
		t = new SplashUpgrade(t, range);
		return true;
	}
	return false;
}

int SplashUpgrade::GetCost()const{
	return Upgrade::GetCost() + ADDED_PRICE;
}

int SplashUpgrade::GetCurrentRefundCost() const{
	return Upgrade::GetCurrentRefundCost() + (int)(ADDED_PRICE * Tower::REFUND_RATIO);
}

std::string SplashUpgrade::GetEffects(){
	return Upgrade::GetEffects() + " Splash";
}