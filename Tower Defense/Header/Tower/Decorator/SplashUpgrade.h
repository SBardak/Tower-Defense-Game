/*

SplashUpgrade class
------------
This is a concrete decorator for the tower. It basically overrides the attack logic of the decorated tower to attack multiple critter (splash).

*/

#pragma once
#include "Upgrade.h"

class SplashUpgrade : public Upgrade
{
public:
	
	virtual ~SplashUpgrade();

	static const int ADDED_PRICE = 250;

	//void ApplyEffectsAndDamage(Critter&, CritterManager&);
	bool HasSplash() const;

	static bool TryToApplySplash(Tower*& t, int range);
	

	int GetCurrentRefundCost() const;
	bool AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange);
	int GetCost() const;
	std::string GetEffects();

private:

	SplashUpgrade(Tower* t, int range);

	int splashRange;
};

