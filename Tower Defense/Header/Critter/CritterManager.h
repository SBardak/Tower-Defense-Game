#ifndef _CRITTERMANAGER_H_
#define _CRITTERMANAGER_H_
#include "Critter.h"
#include "Grid.h"
#include "Player.h"
#include "CritterObserver.h"
#include <vector>

class CritterManager {
public:
	CritterManager(int y, int x, Player* p);
	virtual ~CritterManager();
	inline int getCritterAliveCount() const { return critterAliveCount; }
	void setCritterAliveCount(int critterAliveCount);
	inline int getCritterSpawnCount() const { return critterSpawnCount; }
	inline int getCritterTotalCount() const { return critterTotalCount; }
	Critter** getCritters() const { return critters; }
	void initializeWave(int x);
	void spawnCritter(Grid *myGrid, int currentLevel);
	void moveCritters(Grid *myGrid);
	void resetCritterID();
	static const int MAXNUMCRITTERS;

private:
	int startX;
	int startY;
	int critterAliveCount;
	int critterSpawnCount;
	int critterTotalCount;
	int critterID;
	
	Critter** critters;
	std::vector<CritterObserver*> *observers;
	Player* p;
};

#endif
