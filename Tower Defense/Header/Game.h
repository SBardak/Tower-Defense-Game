#pragma once
#include "Grid.h"
#include "Tower.h"
#include "Critter.h"
#include "GridDisplay.h"
#include <fstream>
#include <iostream>
#include <string>
#include "MapEditor.h"
#include "Player.h"
#include "CritterManager.h"
#include "TowerManager.h"
#include "CritterFactory.h"
using namespace std;

class Game {
public:
	Game();
	virtual ~Game();
	void play();
	bool playAgain();
	bool GameOver();
	bool GameWin();
	void startLevel(CritterManager* cm, CritterFactory* cf, int spawnInterval, TowerManager* tm);
	void endLevel();
	bool isDonePlacingTowers();
	void buy_sell_upgrade_menu(Grid* grid);
	void buy_menu(Grid* grid);
	void sell_menu();
	void upgrade_menu();
	void inspect_menu();
	int currentLevel;
	int maxNumLevels;
private:
	static const int STARTINGCURRENCY;
	static const int STARTINGLIVES;
	Grid* myGrid;
	TowerManager* tm;
	CritterManager* cm;
	MapEditor editor;
	Player p;
	
};