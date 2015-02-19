/*

BasicTower class
------------
This is the concrete component of the Tower. In this case, it is the only concrete component. All the special behaviour is defined throught upgrades (decorators) (Splash, effects and level)

*/

#pragma once
#include "MapEntity.h"
#include "Effect.h"
#include "BaseModel.h"
#include "Tower.h"
#include "Strategy.h"
#include <string>

class BasicTower : public MapEntity, public Tower
{
public:
	BasicTower();
	BasicTower(int cost, int range, int power, int initialLevelUpCost, int fireRate, char dispChar, std::string name, Strategy* strategy);
	BasicTower(const BasicTower& orig);
	virtual ~BasicTower();

	bool CanBuy(int);
	int GetCurrentRefundCost() const;
	int GetCurrentLevelUpCost() const;
	int GetLevel() const;
	int GetPower() const;
	int GetRange() const;
	int GetCost() const;
	int GetFireRate() const; 
	int getX() const;
	int getY() const;

	int GetMaxNumOfEffects() const;
	Critter* GetCurrentCritter() const;

	std::string GetName() const { return name; }
	void SetName(std::string);
	void ApplyEffectsAndDamage(Critter&, CritterManager&,int updatedPower);
	bool HasSplash() const;

	void Attach(IObserver* o);
	void Detach(IObserver* o);
	void Notify();

	void SetPosition(int, int);
	char getDisplayChar() const;
	void SetHitChanceCounter(int newHitChanceCounter);

private:

	int cost; //In that case, int is precise enough
	int range;
	int power;
	int level;
	int currentLevelUpCost;
	int currentRefundCost;
	int fireRate;
	int hitChanceCounter;
	std::string name;
	char initialDisplayChar;

	Critter* currentCritter; //Current critter being attacked

	Strategy* strategy;

	void setStrategy(Strategy* newStrategy);
	Strategy* getStrategy() const;
	void executeStrategy(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange);
	virtual bool AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange);
	virtual std::string GetEffects();

protected:
	const int MAX_LEVEL = 5; //Does not need to be public
	const double REFUND_RATIO = 0.8;
	const double LEVEL_RATIO = 1.2;
	const int LEVEL_UP_MODIFIER = 1;

	bool CanTowerHit(int updatedFireRate);

	char GetInitialDisplayChar() const { return this->initialDisplayChar; }
	void SetInitialDisplayChar(char);


	int GetHitChanceCounter() const;
	void SetCurrentRefundCost(int currentRefundCost);

	void SetCurrentCritter(Critter*);
};

