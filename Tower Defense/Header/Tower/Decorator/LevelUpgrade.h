/*

LevelUpgrade class
------------
This is a concrete decorator for the tower. It basically overrides the basic stats getters of the decorated Tower depending on the state of the LevelUpgrade (modifier member variable).

*/

#pragma once
#include "Upgrade.h"

class LevelUpgrade : public Upgrade
{
public:
	LevelUpgrade(Tower*);
	virtual ~LevelUpgrade();

	const static float COST_RATIO;
	const static int MAX_LEVEL;

	int GetCurrentLevelUpCost() const;
	int GetCurrentRefundCost() const;
	int GetLevel() const;
	int GetPower() const;
	int GetRange() const;
	int GetFireRate() const;

	//Using a private constructor, we can then limit the amount of levels on  a Tower.
	static bool TryToLevelUp(Tower*& t, int amount);

private:
	LevelUpgrade(Tower* t, int addedPower, int addedRange, int addedFireRate);

	int powerModifier;
	int rangeModifier;
	int costModifier;
	int fireRateModifier;
	int refundModifier;
};

