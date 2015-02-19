/*

EffectUpgrade class
------------
This is the concrete decprator for the tower. It basically overrides attack logic to apply the effect on the attacked critter.

*/

#pragma once
#include "Upgrade.h"
#include "Effect.h"

class EffectUpgrade : public Upgrade
{
public:
	EffectUpgrade(Tower* t, Effect* e);
	virtual ~EffectUpgrade();

	static const int ADDED_PRICE = 150;

	bool AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange);

	void ApplyEffectsAndDamage(Critter&, CritterManager&, int updatedPower);

	std::string GetEffects();

	int GetCurrentRefundCost() const;

	int GetCost() const;
private:
	Effect* effect;

};

