/*

Tower class
------------
This is the component of the decorator. It is the abstract representation of a tower in general.

*/


#ifndef TOWER_H
#define	TOWER_H
#include "CritterManager.h"
#include "Critter.h"
#include <string>

class Strategy;

class Tower : public BaseModel{
public:

	virtual ~Tower() {};

	const static double REFUND_RATIO;

	virtual int GetCurrentLevelUpCost() const = 0;
	virtual int GetLevel() const = 0;
	virtual int GetPower() const = 0;
	virtual int GetRange() const = 0;
	virtual int GetFireRate() const = 0;
	virtual int GetCost() const = 0;
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual void ApplyEffectsAndDamage(Critter&, CritterManager&, int updatedPower) = 0;
	virtual std::string GetName() const = 0;
	virtual int GetCurrentRefundCost() const = 0;
	virtual Critter* GetCurrentCritter() const = 0;
	virtual bool HasSplash() const = 0;
	virtual void SetPosition(int x, int y) = 0;
	virtual char getDisplayChar() const = 0;
	virtual Strategy* getStrategy() const = 0;
	virtual bool CanBuy(int) = 0;
	virtual void SetCurrentCritter(Critter* c) = 0;
	virtual bool AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange) = 0;
	virtual void SetHitChanceCounter(int counter) = 0;
	virtual std::string GetEffects() = 0;
	virtual bool CanTowerHit(int updatedFireRate) = 0;
	virtual void executeStrategy(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange) = 0;
};

#endif	/* TOWER_H */

