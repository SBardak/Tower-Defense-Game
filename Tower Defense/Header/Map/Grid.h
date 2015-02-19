#ifndef _GRID_H_
#define _GRID_H_
#include <iostream>
#include "MapObject.h"
#include "Path.h"
#include "Start.h"
#include "End.h"
#include "Observable.h"
using namespace std;

class Tower;

class Grid: public Observable {
public:
	Grid(string file);
	Grid(int row, int col);
	virtual ~Grid();
	void setRow(int row);
	void setCol(int col);
	inline int getRow() const { return row; }
	inline int getCol() const { return col; }
	void printLegend() const;
	void printValidPaths(Path* current);
	bool isValid(int y, int x);
	bool isDeadEnd(Path* current);
	bool isNextValid(int y, int x, Path* current);
	bool isNextEnd(Path* current);
	bool isCorner(int y, int x);
	bool isBorder(int y, int x);
	bool isTopLeftCorner(int y, int x); 
	bool isTopRightCorner(int y, int x); 
	bool isBottomLeftCorner(int y, int x);
	bool isBottomRightCorner(int y, int x);
	bool isTopBorder(int y, int x);
	bool isRightBorder(int y, int x);
	bool isBottomBorder(int y, int x);
	bool isLeftBorder(int y, int x);
	bool isNorth(int y, int x, Path* current);
	bool isEast(int y, int x, Path* current);
	bool isSouth(int y, int x, Path* current);
	bool isWest(int y, int x, Path* current);
	bool isOccupied(int y, int x);
	bool isTouchingPath(int y, int x, Path* current);
	bool isPath(int y, int x);
	void editMap();
	void editLoadedMap();
	void saveMap(string file);
	void linkMap(string file);
	void linkMap();
	void start();
	void setStart(int y, int x);
	int getStartX() const;
	int getStartY() const;
	void end();
	void setEnd(int y, int x);
	void path();
	void setPath(int y, int x);
	void scenery();
	void setScenery(int y, int x);
	bool setTower(int y, int x, int type);
	bool setTower(int y, int x, Tower* t);
	void setCritter(int y, int x, Critter* critter);
	void deleteCritters();
	void moveCritters();
	MapObject* getArr(int y, int x) const;
	void resetPath();
	int verifyMap();
	
	friend ostream& operator<<(ostream& os, Grid& grid);


private:
	MapObject*** arr;
	int row;
	int col;
	Start* startingCell;
	End* endingCell;
	
};

#endif _GRID_H_


