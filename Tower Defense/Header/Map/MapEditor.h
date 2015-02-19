#pragma once
#include "Grid.h"
#include "Tower.h"
#include "Critter.h"
#include "GridDisplay.h"
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

class MapEditor {
public:
	virtual ~MapEditor() {};
	bool file_exists (const string& fileName);
	bool isValidMapSize(int x, int y);
	bool isValidMapName(string mapName);
	Grid* editAndSaveMap();
	Grid* createAndSaveMap();
	Grid* loadMap();
	Grid* saveMap(Grid* myGrid);
	void choseEditOrNew();
};