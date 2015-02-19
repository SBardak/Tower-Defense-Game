#include "LevelUpgrade.h"
#include "Error.h"
#include "ErrorManager.h"

const float LevelUpgrade::COST_RATIO = 0.5;
const int LevelUpgrade::MAX_LEVEL = 5;


LevelUpgrade::LevelUpgrade(Tower* t, int addedPower, int addedRange, int addedFireRate) : Upgrade(t), fireRateModifier(addedFireRate), rangeModifier(addedRange), powerModifier(addedPower) {
	costModifier = (int)(Upgrade::GetCurrentLevelUpCost() * COST_RATIO);
	refundModifier = (int)(t->GetCurrentLevelUpCost() * Tower::REFUND_RATIO);
}

LevelUpgrade::~LevelUpgrade()
{
}

int LevelUpgrade::GetRange() const {
	return Upgrade::GetRange() + rangeModifier;
}

int LevelUpgrade::GetPower() const {
	return Upgrade::GetPower() + powerModifier;
}

int LevelUpgrade::GetLevel() const {
	return Upgrade::GetLevel() + 1;
}

int LevelUpgrade::GetCurrentLevelUpCost() const {
	return Upgrade::GetCurrentLevelUpCost() + costModifier;
}

int LevelUpgrade::GetFireRate() const {
	int temp = Upgrade::GetFireRate() + fireRateModifier;
	if (temp < 1)
		temp = 1;
	return temp;
}

bool LevelUpgrade::TryToLevelUp(Tower*& t, int amount) {
	bool canLevel = true;
	if (amount < t->GetCurrentLevelUpCost()){
		Error e("Not enough currency to upgrade");
		ErrorManager::DisplayError(e);
		canLevel = false;
	}
	if (t->GetLevel() == MAX_LEVEL){
		Error e("Cannot level up, tower has reached max level");
		ErrorManager::DisplayError(e);
		canLevel = false;
	}
	
	if (canLevel == true){
		t = new LevelUpgrade(t, 1, 1, -1);
		t->Notify();
		return true;
	}
	else{
		return false;
	}
	
}

int LevelUpgrade::GetCurrentRefundCost() const{
	return Upgrade::GetCurrentRefundCost() + this->refundModifier;
}
