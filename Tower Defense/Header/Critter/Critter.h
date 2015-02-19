#ifndef CRITTER_H
#define CRITTER_H
#include <iostream>
#include "MapEntity.h"
using std::cout;
using std::cin;
using std::endl;

enum class EffectType {
	None, Slow,
};

enum class CritterType {
	None, Type1, Type2, Type3, Type4, Type5
};

enum class CritterState {
	Alive, Dead
};

class Critter : public MapEntity {
private:
	int id;
	int hitPoints;
	int speed;
	int level;
	int reward;
	int xPosition;
	int yPosition;
	CritterState state;
	EffectType currentEffectType;

public:
	Critter() : id(0), hitPoints(10), speed(1), level(1), reward(1), xPosition(0), yPosition(0) { };

	Critter(int newId, int newHitPoints, int newSpeed, int lvl, int reward, int xSpawn, int ySpawn) :
		id(newId), hitPoints(newHitPoints), speed(newSpeed), level(lvl), reward(reward), xPosition(xSpawn), yPosition(ySpawn) { };

	virtual ~Critter();

	void ApplyDamage(int);
	CritterState GetState() const;
	void SetState(CritterState state);

	// Various accessors and mutators
	inline int getID() const{ return id; }
	inline int getLevel() const { return level; }
	inline int getHitPoints() const { return hitPoints; }
	inline int getSpeed() const { return speed; }
	inline int getReward()const { return reward; }
	inline int getX() const { return xPosition; }
	inline int getY() const { return yPosition; }
	inline void setX(int x) { xPosition = x; }
	inline void setY(int y) { yPosition = y; }
	inline void setLevel(int num) { level = num; }
	inline void setReward(int num) { reward = num; }
	inline void setHitPoints(int num) { hitPoints = num; }

	void displayStats();

	void SetEffectType(EffectType);
	EffectType GetEffectType() const { return this->currentEffectType; }
	int GetSpeed() const { return this->speed; }
	void SetSpeed(int);
};

#endif