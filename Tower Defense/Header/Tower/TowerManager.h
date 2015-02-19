/*

TowerManager class
--------------------
Class to manage the current towers on the map (buying, selling, upgrade, etc.).

*/

#ifndef TOWERMANAGER_H
#define	TOWERMANAGER_H

#include "Strategy.h"
#include "Tower.h"
#include "Grid.h"
#include "TowerObserver.h"
#include "Player.h"
#include "CritterManager.h"
#include <vector>

enum class TowerTypes {
	Basic, Slowing, Splash, None
};

class TowerManager : public BaseModel {
public:
	TowerManager(Grid* const, Player* const, CritterManager* cm);
    TowerManager(const TowerManager& orig);
    virtual ~TowerManager();

	std::vector<Tower*> getTowers() const { return *towers; }
	std::vector<TowerObserver*>* const getTowerObservers() const { return observers; }
	const Grid* getMap() const { return this->map; }
	const Player* getPlayer() const { return this->player; }
    
	int BuyTower(TowerTypes, Grid*, int x = 1, int y = 1);
	bool CanBuyTower(TowerTypes);
    bool SellTower(Tower*);
	bool LevelUpTower(int index);
	void Inspect(int index);

	const Tower* const GetBasicTower() const { return this->basicTower; }
	const Tower* const GetSplashTower() const { return this->splashTower; }
	const Tower* const GetFrezingTower() const { return this->slowTower; }

	int getNumOfTowers() const;
    
private:
	CritterManager* cm;
    std::vector<Tower*> *towers;
	std::vector<TowerObserver*> *observers;
    
    Tower* basicTower;
    Tower* splashTower;
    Tower* slowTower;
	
	Grid* const map;
	Player* const player;
    int Contains(Tower*);

	int numOfTowers;

	Tower* createBasicTower();
	Tower* createSlowTower();
	Tower* createSplashTower();

};

#endif	/* TOWERMANAGER_H */

