/*

Upgrade class
------------
This is the base decorator for the Tower. Upgrades in general override the cost and refund getters to ajust depending on the number of Upgrades applied to a tower.

*/


#pragma once
#include "Tower.h"
class Upgrade :
	public Tower
{
public:
	Upgrade(Tower*);
	virtual ~Upgrade();
	
	virtual int GetCurrentLevelUpCost() const;
	virtual int GetLevel() const;
	virtual int GetPower() const;
	virtual int GetRange() const;
	virtual int GetFireRate() const;
	virtual int GetCost() const;
	virtual int getX() const;
	virtual int getY() const;
	virtual void ApplyEffectsAndDamage(Critter&, CritterManager&, int updatedPower);
	std::string GetName() const;
	virtual int GetCurrentRefundCost() const;
	virtual Critter* GetCurrentCritter() const;
	virtual  bool HasSplash() const;
	virtual void Attach(IObserver* o);
	virtual void Detach(IObserver* o);
	virtual void Notify();
	virtual void SetPosition(int x, int y);
	virtual char getDisplayChar() const;
	virtual Strategy* getStrategy() const;
	virtual bool CanBuy(int);
	virtual void SetCurrentCritter(Critter* c);
	virtual bool AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange);
	virtual void SetHitChanceCounter(int counter);
	virtual std::string GetEffects();

private:
	

protected:
	Tower* upgradedTower;
	virtual bool CanTowerHit(int updatedFireRate);
	virtual void executeStrategy(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange);
};

