#include "Grid.h"
#include "MapObject.h"
#include "Tower.h"
#include "Critter.h"
#include "Start.h"
#include "End.h"
#include "Path.h"
#include "Scenery.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Utility.h"
#include "TowerManager.h"
#include "TowerSellingObserver.h"

using namespace std;


Grid::Grid(string file) {
	linkMap(file);
}

//Constructor to create specified grid, and initialize all cells to nulltpr
Grid::Grid(int row, int col): row(row), col(col){
	arr = new MapObject**[row];
	for (int i = 0; i < row; i++)
    arr[i] = new MapObject*[col];

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			arr[i][j] = nullptr;
}

void Grid::setStart(int y, int x){
	arr[y-1][x-1] = new Start(y-1, x-1);
	startingCell = static_cast<Start*>(arr[y-1][x-1]);
	notify();
}

int Grid::getStartX() const {
	return startingCell->getX();
}

int Grid::getStartY() const {
	return startingCell->getY();
}

void Grid::setEnd(int y, int x){
	arr[y-1][x-1] = new End(y-1, x-1);
	endingCell = static_cast<End*>(arr[y-1][x-1]);
	notify();
}

void Grid::setPath(int y, int x){
	arr[y-1][x-1] = new Path(y-1, x-1);
	notify();
}

void Grid::setScenery(int y, int x){
	arr[y-1][x-1] = new Scenery(y-1, x-1);
	notify();
}

bool Grid::setTower(int y, int x, int type){
	if (arr[y-1][x-1]->getType() == "Scenery"){
		notify();
		return true;
	} else {
		cout << "Can only create towers on Scenery cells!" << endl;
		return false;
	}
}

void Grid::setCritter(int y, int x, Critter* critter){
	if (arr[y-1][x-1]->getType() == "Path" || arr[y-1][x-1]->getType() == "Start" || arr[y-1][x-1]->getType() == "End"){
		static_cast<Path*>(arr[y-1][x-1])->setCritter(critter);
	} else {
		cout << "Critters can only walk on path!" << endl;   
	}
}


MapObject* Grid::getArr(int y, int x) const{
	return arr[y][x];
}

Grid::~Grid(){
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			delete arr[i][j];

	for (int i = 0; i < row; i++)
		delete arr[i];

	delete arr;
}

void Grid::setRow(int height){
	this->row = height;
}

void Grid::setCol(int width){
	this->col = width;
}

//Checks if the tile contains anything
bool Grid::isOccupied(int y, int x){
	return (arr[y-1][x-1] != nullptr);
}

bool Grid::isPath(int y, int x){
	if (!isOccupied(y,x))
		return false;
	else
		return (arr[y-1][x-1]->getType() == "Path");
}

bool Grid::isTouchingPath(int y, int x, Path* current){
	// Array positions
	int currentX = current->getX();
	int currentY = current->getY();
	int arrayY = y - 1;
	int arrayX = x - 1;

	
	// If the (x,y) values is to the North of current
	if (isNorth(arrayY, arrayX, current)){
		// West
		if (isOccupied(y, x-1))
			if (isPath(y, x-1))
				return true;
		// North
		if (isOccupied(y-1, x))
			if (isPath(y-1, x))
				return true;
		// East
		if (isOccupied(y, x+1))
			if (isPath(y, x+1))
				return true;
		return false;
	}else if (isEast(arrayY, arrayX, current)){
		// North
		if (isOccupied(y-1, x))
			if (isPath(y-1, x))
				return true;
		// East
		if (isOccupied(y, x+1))
			if (isPath(y, x+1))
				return true;
		// South
		if (isOccupied(y+1, x))
			if (isPath(y+1, x))
				return true;
		return false;
	}else if (isSouth(arrayY, arrayX, current)){
		// East
		if (isOccupied(y, x+1))
			if (isPath(y, x+1))
				return true;
		// South
		if (isOccupied(y+1, x))
			if (isPath(y+1, x))
				return true;
		// West
		if (isOccupied(y, x-1))
			if (isPath(y, x-1))
				return true;
		return false;
	}else if (isWest(arrayY, arrayX, current)){
		// South
		if (isOccupied(y+1, x))
			if (isPath(y+1, x))
				return true;
		// West
		if (isOccupied(y, x-1))
			if (isPath(y, x-1))
				return true;
		// North
		if (isOccupied(y-1, x))
			if (isPath(y-1, x))
				return true;
		return false;
	}
	// should not reach here
	return false;
}

//Validate input between (1 to row) and (1 to col) inclusive for choosing grid cells
bool Grid::isValid(int y, int x){
	return (x >= 1 && x <= this->getCol() && y >= 1 && y <= this->getRow());
	
}

bool Grid::isTopLeftCorner(int y, int x){
	return (y == 0 && x == 0);
}

bool Grid::isTopRightCorner(int y, int x){
	return (y == 0 && x == col - 1);
}

bool Grid::isBottomLeftCorner(int y, int x){
	return (x == 0 && y == row - 1);
}

bool Grid::isBottomRightCorner(int y, int x){
	return (x == col - 1 && y == row - 1);
}

//Checks if cell is Top border (not including corner cells)
bool Grid::isTopBorder(int y, int x){
	return (y == 0 && x != 0 && x != col - 1);
}
//Checks if cell is Right border (not including corner cells)
bool Grid::isRightBorder(int y, int x){
	return (x == col - 1 && y != 0  && y != row - 1);
}
//Checks if cell is Bottom border (not including corner cells)
bool Grid::isBottomBorder(int y, int x){
	return (y == row - 1 && x != 0 && x != col - 1);
}
//Checks if cell is Left border (not including corner cells)
bool Grid::isLeftBorder(int y, int x){
	return (x == 0 && y != 0 && y !=  row - 1);
}
//Checks if cell is on any border (not including corner cells)
bool Grid::isBorder(int y, int x){
	return (isTopBorder(y,x) || isRightBorder(y,x) || isBottomBorder(y,x) || isLeftBorder(y,x));
}

bool Grid::isCorner(int y, int x){
	return (isTopLeftCorner(y,x) || isTopRightCorner(y,x) || isBottomLeftCorner(y,x) || isBottomRightCorner(y,x));
}
// Comparing if (x,y) is to the North of Current
bool Grid::isNorth(int y, int x, Path* current){
	return (x == current->getX() && y == current->getY() - 1);
}
// Comparing if (x,y) is to the East of Current
bool Grid::isEast(int y, int x, Path* current){
	return (x == current->getX() + 1 && y == current->getY());
}
// Comparing if (x,y) is to the South of Current
bool Grid::isSouth(int y, int x, Path* current){
	return (x == current->getX() && y == current->getY() + 1);
}
// Comparing if (x,y) is to the West of Current
bool Grid::isWest(int y, int x, Path* current){
	return (x == current->getX() - 1 && y == current->getY());
}

// Comparing if (x,y) is a valid user input compared to Current 
// Can go up, down, left, right, based on location
bool Grid::isNextValid(int y, int x, Path* current){
	int currentX = current->getX();
	int currentY = current->getY();

	if (isTopBorder(currentY, currentX))
		return (isSouth(y, x, current)/*isWest(y, x, current) ||  || isEast(y, x, current)*/);
	else if (isRightBorder(currentY, currentX))
		return (isWest(y, x, current) /*isNorth(y, x, current) ||  || isSouth(y, x, current)*/);
	else if (isBottomBorder(currentY, currentX))
		return (isNorth(y, x, current) /*isWest(y, x, current) ||  || isEast(y, x, current)*/);
	else if (isLeftBorder(currentY, currentX))
		return (isEast(y, x, current) /*isNorth(y, x, current) ||  || isSouth(y, x, current)*/);
	else {
		return ((isNorth(y, x, current) || isEast(y, x, current) || isSouth(y, x, current) || isWest(y, x, current)) && !isBorder(y, x) && !isTouchingPath(y+1,x+1, current));
	}
}

// Checks if any adjacent cells of the Current cell are the End cell (up, down, left, right)
bool Grid::isNextEnd(Path* current){
	int currentX = current->getX();
	int currentY = current->getY();
	string end = "End";

	if (isTopLeftCorner(currentY, currentX)){
		if (arr[currentY][currentX+1] != nullptr){ // East
			if (arr[currentY][currentX+1]->getType() == end)
				return true;	
		}
		if (arr[currentY+1][currentX] != nullptr){  // South
			if (arr[currentY+1][currentX]->getType() == end)
				return true;
		}
			return false;
	}else if (isTopRightCorner(currentY, currentX)) {
		if (arr[currentY+1][currentX] != nullptr){ // South
			if (arr[currentY+1][currentX]->getType() == end)
				return true;
		}
		if (arr[currentY][currentX-1] != nullptr){ // West
			if (arr[currentY][currentX-1]->getType() == end)
				return true;
		}
			return false;
	}else if (isBottomLeftCorner(currentY, currentX)){
		  if (arr[currentY-1][currentX] != nullptr){  // North
			if (arr[currentY-1][currentX]->getType() == end)
				return true;
		}
		 if (arr[currentY][currentX+1] != nullptr){ // East
			if (arr[currentY][currentX+1]->getType() == end)
				return true;
		}
			return false;
	}else if (isBottomRightCorner(currentY, currentX)){
		  if (arr[currentY-1][currentX] != nullptr){  // North
			if (arr[currentY-1][currentX]->getType() == end)
				return true;
		}
		 if (arr[currentY][currentX-1] != nullptr){ // West
			if (arr[currentY][currentX-1]->getType() == end)
				return true;
		}
			return false;
	}else if (isTopBorder(currentY, currentX)){
		if (arr[currentY][currentX+1] != nullptr){ // East
			if (arr[currentY][currentX+1]->getType() == end)
				return true;
		}
		if (arr[currentY+1][currentX] != nullptr){ // South
			if (arr[currentY+1][currentX]->getType() == end)
				return true;
		}
		if (arr[currentY][currentX-1] != nullptr){ // West
			if (arr[currentY][currentX-1]->getType() == end)
				return true;
		}
			return false;
	}else if (isRightBorder(currentY, currentX)){
		  if (arr[currentY-1][currentX] != nullptr){  // North
			if (arr[currentY-1][currentX]->getType() == end)
				return true;
		}
		  if (arr[currentY+1][currentX] != nullptr){ // South
			if (arr[currentY+1][currentX]->getType() == end)
				return true;
		}
		  if (arr[currentY][currentX-1] != nullptr){ // West
			if (arr[currentY][currentX-1]->getType() == end)
				return true;
		}
			return false;
	}else if (isBottomBorder(currentY, currentX)){
		  if (arr[currentY-1][currentX] != nullptr){  // North
			if (arr[currentY-1][currentX]->getType() == end)
				return true;
		}
		  if (arr[currentY][currentX+1] != nullptr){ // East
			if (arr[currentY][currentX+1]->getType() == end)
				return true;
		}
		  if (arr[currentY][currentX-1] != nullptr){ // West
			if (arr[currentY][currentX-1]->getType() == end)
				return true;
		}
			return false;
	}else if (isLeftBorder(currentY, currentX)){
		  if (arr[currentY-1][currentX] != nullptr){  // North
			if (arr[currentY-1][currentX]->getType() == end)
				return true;
		}
		  if (arr[currentY][currentX+1] != nullptr){ // East
			if (arr[currentY][currentX+1]->getType() == end)
				return true;
		}
		  if (arr[currentY+1][currentX] != nullptr){ // South
			if (arr[currentY+1][currentX]->getType() == end)
				return true;
		}
			return false;
	}else {
		 if (arr[currentY-1][currentX] != nullptr){  // North
			if (arr[currentY-1][currentX]->getType() == end)
				return true;
		}
		 if (arr[currentY][currentX+1] != nullptr){ // East
			if (arr[currentY][currentX+1]->getType() == end)
				return true;
		}
		 if (arr[currentY+1][currentX] != nullptr){ // South
			if (arr[currentY+1][currentX]->getType() == end)
				return true;
		}
		 if (arr[currentY][currentX-1] != nullptr){ // West
			if (arr[currentY][currentX-1]->getType() == end)
				return true;
		}
		
		 return false;
	}	
}

// Prints all the valid paths for the user (Anything that is not occupied)
void Grid::printValidPaths(Path* current){
	// Get current x and y (add 1 to turn array indices into grid locations)
	int currentX = current->getX() + 1;
	int currentY = current->getY() + 1;
	string s = "Valid Path (x,y) coordinates are: ";
	string noPaths = "There are no valid paths, please start over!";
	bool a = true;
	bool b = true;
	bool c = true;
	bool d = true;
	cout << s; 

	if (isTopBorder(currentY-1, currentX-1)){ // West, South, East
		if (!isOccupied(currentY+1, currentX)){
			b = false;
			cout << " (" << currentX << "," << currentY + 1 << ")";
		}
		if (b)
			cout << noPaths << endl;
	}else if (isRightBorder(currentY-1, currentX-1)){ // North, West, South
		if (!isOccupied(currentY, currentX-1)){
			b = false;
			cout << " (" << currentX - 1 << "," << currentY << ")";
		}
		if (b)
			cout << noPaths << endl;
	}else if (isBottomBorder(currentY-1, currentX-1)){ // West, North, East
		if (!isOccupied(currentY - 1, currentX)){
			b = false;
			cout << " (" << currentX << "," << currentY - 1<< ")";
		}
		if (b)
			cout << noPaths << endl;
	}else if (isLeftBorder(currentY-1, currentX-1)){ // North, East, South
		if (!isOccupied(currentY, currentX+1)){
			b = false;
			cout << " (" << currentX + 1 << "," << currentY << ")";
		}
		if (b)
			cout << noPaths << endl;
	}else {     // North
		if (!isOccupied(currentY-1, currentX) && !isBorder(currentY-2, currentX-1) && !isTouchingPath(currentY-1, currentX, current)){
			a = false;
			cout << " (" << currentX << "," << currentY - 1 << ")";
		}       // East
		if (!isOccupied(currentY, currentX+1) && !isBorder(currentY-1, currentX) && !isTouchingPath(currentY, currentX+1, current)){
			b = false;
			cout << " (" << currentX + 1 << "," << currentY << ")";
		}      // South
		if (!isOccupied(currentY+1, currentX) && !isBorder(currentY, currentX-1) && !isTouchingPath(currentY+1, currentX, current)){
			c = false;
			cout << " (" << currentX << "," << currentY + 1 << ")";
		}      // West
		if (!isOccupied(currentY, currentX - 1) && !isBorder(currentY-1, currentX-2)  && !isTouchingPath(currentY, currentX - 1, current)){
			d = false;
			cout << " (" << currentX - 1 << "," << currentY << ")";
		}
		if (a && b && c && d)
			cout << noPaths << endl;
	}
	cout << endl;
}

// Checks if the Current cell has any empty cells or the end cell 
// adjacent to it in order to determine if it's a dead end
bool Grid::isDeadEnd(Path* current){
	// Get current x and y (add 1 to turn array indices into grid locations)
	int aX = current->getX();
	int aY = current->getY();
	int currentX = aX + 1;
	int currentY = aY + 1;
	 
	bool a = false;
	bool b = false;
	bool c = false;
	bool d = false;
	
	string end = "End";

			// North
	if (isBorder(aY-1, aX))
		a = true;
	else if ((isOccupied(currentY-1, currentX) && arr[aY-1][aX]->getType() != end) || (!isOccupied(currentY-1, currentX) && isTouchingPath(currentY-1, currentX, current))){
		a = true;
	}		// East
	if (isBorder(aY, aX+1))
		b = true;
	else if ((isOccupied(currentY, currentX+1) && arr[aY][aX+1]->getType() != end) || (!isOccupied(currentY, currentX+1) && isTouchingPath(currentY, currentX+1, current))){
		b = true;
	}		// South
	if (isBorder(aY+1, aX))
		c = true;
	else if ((isOccupied(currentY+1, currentX) && arr[aY+1][aX]->getType() != end) || (!isOccupied(currentY+1, currentX) && isTouchingPath(currentY+1, currentX, current))){
		c = true;
	}		// West
	if (isBorder(aY, aX-1))
		d = true;
	else if ((isOccupied(currentY, currentX - 1) && arr[aY][aX-1]->getType() != end) || (!isOccupied(currentY, currentX-1) && isTouchingPath(currentY, currentX-1, current))){
		d = true;
	}
	return (a && b && c && d);
	
}

void Grid::editLoadedMap(){
	cout << "\n**********************" << endl;
	cout << "Starting Map Editor..." << endl;
	cout << "**********************" << endl;

	notify();

	int choice = 0;
	do{
		cout << "\nWhat would you like to edit? (1 - Start, 2 - End, 3 - Path Cell, 4 - Scenery Cell, 5 - Finish): ";
		Utility::getInt(choice);
		while (choice < 1 || choice > 6){
			cout << "\nPlease enter a valid choice!: ";
			Utility::getInt(choice);
		}
		if (choice == 1){
			start();
		}
		else if (choice == 2){
			end();
		}
		else if (choice == 3){
			path();
		}
		else if (choice == 4){
			scenery();
		}
		

	} while (choice != 5);
	
	notify();

}

// The Map Editor (start, end, and path creation) 
// Repeats path creation if user inputs to a dead end
void Grid::editMap(){
	cout << "**********************" << endl;
	cout << "Starting Map Editor..." << endl;
	cout << "**********************" << endl;

	///////// START PATH  ///////////
	cout << "\nPlease input Path's starting (x,y) coordinates anywhere along the borders of the grid (excluding corners): " << endl;
	int x; //col
	int y; //row
	int count = 0;

	do{
		do {
			if (count > 0)
				cout << "Please enter valid (x,y) coordinates!" << endl;
			cout << "x: ";
			Utility::getInt(x);
			cout << "y: ";
			Utility::getInt(y);
			++count;
		} while (!isValid(y, x));
	} while (!isBorder(y - 1, x - 1));

	// CHANGING OF CELL TYPE;
	setStart(y, x);
	Path* start = static_cast<Start*>(arr[y - 1][x - 1]);
	start->setPrev(nullptr);
	Path* current = start;

	/////////// END PATH /////////////
	cout << "Please input Path's ending (x,y) coordinates anywhere along the borders of the grid (excluding corners): " << endl;
	// Reset x,y and count to 0
	x, y = 0;
	 count = 0;

	do{
		do {
			if (count > 0)
				cout << "Please enter valid (x,y) coordinates!" << endl;
			cout << "x: ";
			Utility::getInt(x);
			cout << "y: ";
			Utility::getInt(y);
			++count;
			if (isValid(y, x) && isOccupied(y, x)){
				cout << "The coordinates you entered is already occupied." << endl;
				x = y = -1;
			}
		} while (!isValid(y, x));
	} while (!isBorder(y - 1, x - 1));

	// CHANGING OF CELL TYPE
	setEnd(y, x);
	Path* end = static_cast<End*>(arr[y - 1][x - 1]);
	end->setNext(nullptr);

	///////////// SET PATH FROM START TO END /////////////////
	do { 
		do {
			do {
				cout << "Please input next Path's (x,y) coordinates:" << endl;
				printValidPaths(current);
			
				// Reset x, y and count to 0
				x = y = 0;
				count = 0;
					do {
					if (count > 0)
						cout << "Please enter valid (x,y) coordinates!" << endl;
					cout << "x: ";
					Utility::getInt(x);
					if (x == -1){
						current = start;
						resetPath();

						cout << "***************" << endl;
						cout << "Path reset..." << endl;
						cout << "***************" << endl;
						
						notify();

						cout << "Please input next Path's (x,y) coordinates:" << endl;
						printValidPaths(current);
						cout << "x: ";
						Utility::getInt(x);
					}
					cout << "y: ";
					Utility::getInt(y);
					++count;
					}while (!isValid(y,x));

			} while (!isNextValid(y-1, x-1, current));

		if (isOccupied(y,x))
			cout << "The coordinates you entered is already occupied." << endl;

		} while (isOccupied(y,x));

		// CHANGING OF CELL TYPE
		setPath(y, x);
		current->setNext(static_cast<Path*>(arr[y-1][x-1]));
		static_cast<Path*>(arr[y-1][x-1])->setPrev(current);
		current = static_cast<Path*>(arr[y-1][x-1]);

		// CHECK DEAD END
		if (isDeadEnd(current) && !isNextEnd(current)){
			current = start;
			resetPath();

			cout << "****************************************************************" << endl;
			cout << "You have reached a dead end, restarting path creation process..." << endl;
			cout << "****************************************************************" << endl;
			notify();
		}

	}while (!isNextEnd(current));  // End of the big do-while loop (stops when current is adjacent to end)

	// Setting relation between the current and end paths
	current->setNext(end);
	end->setPrev(current);
	
	cout << "****************************************************************" << endl;
	cout << "Path completed! Converting empty tiles into scenery tiles..." << endl;
	cout << "****************************************************************" << endl;

	//// AUTOMATICALLY SWITCH "NULL" TILES TO "SCENERY" //////
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			if (arr[i][j] == nullptr)
				arr[i][j] = new Scenery(i,j);

	notify();
}

void Grid::start(){
	///////// START CELL  ///////////
	cout << "\nPlease input Path's starting (x,y) coordinates anywhere along the borders of the grid (excluding corners): " << endl;
	int x; //col
	int y; //row
	int count = 0;

	do{
		do {
			if (count > 0)
				cout << "Please enter valid (x,y) coordinates!" << endl;
			cout << "x: ";
			Utility::getInt(x);
			cout << "y: ";
			Utility::getInt(y);
			++count;
		} while (!isValid(y, x));
	} while (!isBorder(y - 1, x - 1));

	// CHANGING OF CELL TYPE;
	arr[startingCell->getY()][startingCell->getX()] = new Scenery(startingCell->getY(), startingCell->getX());
	setStart(y, x);

}

void Grid::end(){
	/////////// END CELL /////////////
	cout << "\nPlease input Path's ending (x,y) coordinates anywhere along the borders of the grid (excluding corners): " << endl;
	// Reset x,y and count to 0
	int x = 0, y = 0;
	int count = 0;

	do{
		do {
			if (count > 0)
				cout << "Please enter valid (x,y) coordinates!" << endl;
			cout << "x: ";
			Utility::getInt(x);
			cout << "y: ";
			Utility::getInt(y);
			++count;
		} while (!isValid(y, x));
	} while (!isBorder(y - 1, x - 1));

	// CHANGING OF CELL TYPE
	arr[endingCell->getY()][endingCell->getX()] = new Scenery(endingCell->getY(), endingCell->getX());
	setEnd(y, x);
	Path* end = static_cast<End*>(arr[y - 1][x - 1]);
	end->setNext(nullptr);
}

void Grid::path(){
	/////////// PATH CELL /////////////
	cout << "\nPlease input a Path cell (x,y) coordinate anywhere (excluding borders & corners): " << endl;
	// Reset x,y and count to 0
	int x = 0, y = 0;
	int count = 0;

	do{
		do {
			if (count > 0)
				cout << "Please enter valid (x,y) coordinates!" << endl;
			cout << "x: ";
			Utility::getInt(x);
			cout << "y: ";
			Utility::getInt(y);
			++count;
		} while (!isValid(y, x));
	} while (isBorder(y - 1, x - 1) || isCorner(y-1, x-1));

	// CHANGING OF CELL TYPE
	setPath(y, x);
}

void Grid::scenery(){
	/////////// SCENERY CELL /////////////
	cout << "\nPlease input a Scenery cell (x,y) coordinate anywhere: " << endl;
	// Reset x,y and count to 0
	int x = 0, y = 0;
	int count = 0;
		do {
			if (count > 0)
				cout << "Please enter valid (x,y) coordinates!" << endl;
			cout << "x: ";
			Utility::getInt(x);
			cout << "y: ";
			Utility::getInt(y);
			++count;
		} while (!isValid(y, x));

	// CHANGING OF CELL TYPE
	setScenery(y, x);
}

void Grid::resetPath(){
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j){
			if (arr[i][j] != nullptr)
				if (arr[i][j]->getType() == "Path"){
					delete arr[i][j];
					arr[i][j] = nullptr;
				}
		}
}

// Prints grid 
ostream& operator<<(ostream& os, Grid& grid)
{
	using std::setw;
	os << endl;
	os << setw(4) << " ";
	for (int i = 1; i <= grid.col; ++i)
		os << setw(3) << i;
	os << " (x)" << endl;
	os << setw(4) << " ";
	for (int i = 1; i <= grid.col*3+1; ++i)
		os << "_";
	os << endl;
	for (int row = 0; row < grid.row; ++row){
		os << setw(2) << row+1 << " |";
		for (int col = 0; col < grid.col; ++col){
		  os << setw(3) << ((grid.arr[row][col] == nullptr)? "0" : grid.arr[row][col]->print());
		}
		os << " |" << endl;
	}
	os << setw(3) << "(y) ";
	for (int i = 1; i <= grid.col*3+1; ++i)
		os << "_";
	os << "\n" << endl;
    return os;
}

void Grid::printLegend() const {
	cout << "\n\t-== LEGEND ==-\n"
		<< "\tS - Start\n" 
		<< "\tE - Exit\n"
		<< "\t' ' - Path\n"
		<< "\tT - Tower\n"
		<< "\tC - Critter\n"
		<< "\t# - Scenery\n"
		<< "\t0 - Blank" << endl;
}

void Grid::saveMap(string file){
	ofstream out(file);
	out << this->row << endl;  // height
	out << this->col << endl;  // width

	for (int row = 0; row < this->row; ++row){
		for (int col = 0; col < this->col; ++col){
			if (arr[row][col]->getType() == "Start") 
				out.put('S');
			else if (arr[row][col]->getType() == "End")
				out.put('E');
			else if (arr[row][col]->getType() == "Path")
				out.put('P');
			else if (arr[row][col]->getType() == "Scenery")
				out.put('#');
		}
		out << endl;
	}
	out.close();
}

void Grid::linkMap(string file){
	int height;
	int width;
	char ch;
	string line;
	
	ifstream input;
	input.open(file);

	getline(input, line);
	height = atoi(line.c_str());
	getline(input, line);
	width = atoi(line.c_str());

	this->setRow(height);
	this->setCol(width);

	arr = new MapObject**[row];
	for (int i = 0; i < row; i++)
    arr[i] = new MapObject*[col];

	for (int i = 1; i <= row; ++i){
		for (int j = 1; j <= col; j++){
			ch = input.get();
			if (ch == 'S') 
				setStart(i, j);
			else if (ch == 'E')
				setEnd(i, j);
			else if (ch == 'P')
				setPath(i, j);
			else if (ch == '#')
				setScenery(i, j);
		}
		 getline(input,line);
	}
	input.close();


	// Fix Links (Prev, Next)
	// startingCell , endingCell , current, previous
	startingCell->setPrev(nullptr);
	endingCell->setNext(nullptr);
	Path* current = startingCell;

	// Create the first link from startingCell (restricted based on border)
	if (isTopBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY() + 1][getStartX()]));
		static_cast<Path*>(arr[getStartY() + 1][getStartX()])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY() + 1][getStartX()]);
	}
	else if (isRightBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY()][getStartX() - 1]));
		static_cast<Path*>(arr[getStartY()][getStartX() - 1])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY()][getStartX() - 1]);
	}
	else if (isBottomBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY() - 1][getStartX()]));
		static_cast<Path*>(arr[getStartY() - 1][getStartX()])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY() - 1][getStartX()]);
	}
	else if (isLeftBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY()][getStartX() + 1]));
		static_cast<Path*>(arr[getStartY()][getStartX() + 1])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY()][getStartX() + 1]);
	}
	
	Path* previous = startingCell;
		
	// Create the rest of links until endingCell
	while (!isNextEnd(current)){
		// Current Array (x,y)
		int cArrayX = current->getX();
		int cArrayY = current->getY();
		// Current (x,y) + 1 for Grid
		int currentX = cArrayX + 1; 
		int currentY = cArrayY + 1;
		
		//if path north of current link north
		if (isPath(currentY - 1, currentX) && arr[cArrayY - 1][cArrayX] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY - 1][cArrayX]));
			static_cast<Path*>(arr[cArrayY - 1][cArrayX])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY - 1][cArrayX]);
		}
		//if path east of current link east
		else if (isPath(currentY, currentX + 1) && arr[cArrayY][cArrayX + 1] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY][cArrayX + 1]));
			static_cast<Path*>(arr[cArrayY][cArrayX + 1])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY][cArrayX + 1]);
		}
		//if path south of current link south
		else if (isPath(currentY + 1, currentX) && arr[cArrayY + 1][cArrayX] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY + 1][cArrayX]));
			static_cast<Path*>(arr[cArrayY + 1][cArrayX])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY + 1][cArrayX]);
		}
		//if path west of current link west
		else if (isPath(currentY, currentX - 1) && arr[cArrayY][cArrayX - 1] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY][cArrayX - 1]));
			static_cast<Path*>(arr[cArrayY][cArrayX - 1])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY][cArrayX - 1]);
		}
	}
	current->setNext(endingCell);
	endingCell->setPrev(current);
}

void Grid::linkMap(){
	// Fix Links (Prev, Next)
	// startingCell , endingCell , current, previous
	startingCell->setPrev(nullptr);
	endingCell->setNext(nullptr);
	Path* current = startingCell;

	// Create the first link from startingCell (restricted based on border)
	if (isTopBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY() + 1][getStartX()]));
		static_cast<Path*>(arr[getStartY() + 1][getStartX()])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY() + 1][getStartX()]);
	}
	else if (isRightBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY()][getStartX() - 1]));
		static_cast<Path*>(arr[getStartY()][getStartX() - 1])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY()][getStartX() - 1]);
	}
	else if (isBottomBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY() - 1][getStartX()]));
		static_cast<Path*>(arr[getStartY() - 1][getStartX()])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY() - 1][getStartX()]);
	}
	else if (isLeftBorder(getStartY(), getStartX())){
		current->setNext(static_cast<Path*>(arr[getStartY()][getStartX() + 1]));
		static_cast<Path*>(arr[getStartY()][getStartX() + 1])->setPrev(current);
		current = static_cast<Path*>(arr[getStartY()][getStartX() + 1]);
	}

	Path* previous = startingCell;

	// Create the rest of links until endingCell
	while (!isNextEnd(current)){
		// Current Array (x,y)
		int cArrayX = current->getX();
		int cArrayY = current->getY();
		// Current (x,y) + 1 for Grid
		int currentX = cArrayX + 1;
		int currentY = cArrayY + 1;

		//if path north of current link north
		if (isPath(currentY - 1, currentX) && arr[cArrayY - 1][cArrayX] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY - 1][cArrayX]));
			static_cast<Path*>(arr[cArrayY - 1][cArrayX])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY - 1][cArrayX]);
		}
		//if path east of current link east
		else if (isPath(currentY, currentX + 1) && arr[cArrayY][cArrayX + 1] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY][cArrayX + 1]));
			static_cast<Path*>(arr[cArrayY][cArrayX + 1])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY][cArrayX + 1]);
		}
		//if path south of current link south
		else if (isPath(currentY + 1, currentX) && arr[cArrayY + 1][cArrayX] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY + 1][cArrayX]));
			static_cast<Path*>(arr[cArrayY + 1][cArrayX])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY + 1][cArrayX]);
		}
		//if path west of current link west
		else if (isPath(currentY, currentX - 1) && arr[cArrayY][cArrayX - 1] != previous){
			current->setNext(static_cast<Path*>(arr[cArrayY][cArrayX - 1]));
			static_cast<Path*>(arr[cArrayY][cArrayX - 1])->setPrev(current);
			previous = current;
			current = static_cast<Path*>(arr[cArrayY][cArrayX - 1]);
		}
	}
	current->setNext(endingCell);
	endingCell->setPrev(current);
}

bool Grid::setTower(int y, int x, Tower* t){
	
	if (x >= 0 && x <= col && y >= 0 && y <= row){
		Scenery* sc = dynamic_cast<Scenery*>(arr[y - 1][x - 1]);
		if (sc == nullptr){
			return false;
		}
		else{
			if (sc->getTower() == nullptr || t == nullptr){
				sc->setTower(t);
				return true;
			}
			else{
				return false;
			}
		}
	}
	else {
		return false;
	}
	
}

int Grid::verifyMap(){
	int error = 0;
	int pathError = 0;
	int bExists = 0;
	int eExists = 0;
	int pathExists = 0;
	for (int y = 0; y < getRow(); y++)
		for (int x = 0; x < getCol(); x++){
			int side = 0;
			if (y != getRow() - 1 && arr[y + 1][x]->getType() != "Scenery")
				side++;
			if (y != 0 && arr[y - 1][x]->getType() != "Scenery")
				side++;
			if (x != getCol() - 1 && arr[y][x + 1]->getType() != "Scenery")
				side++;
			if (x != 0 && arr[y][x - 1]->getType() != "Scenery")
				side++;
			
			if (arr[y][x]->getType() == "Path"){
				pathExists++;
				if (side != 2){
					if (pathError == 0){
						cout << "\nWARNING: Verify path blocks are all touching and have a Start and End Path attached";
						error++;
						pathError++;
					}
				}
			}
			else if (arr[y][x]->getType() == "Start"){
				bExists++;
				if ((y != 0 && x != 0) && (y != getRow() - 1 && x != getCol() - 1)){		//checking if Start is touching edge
					cout << "\nWARNING: Start is not touching outer edge";
					error++;
				}
				if (side != 1){
					cout << "\nWARNING: Start is not attached to a path block";
					error++;
				}
			}
			else if (arr[y][x]->getType() == "End"){
				eExists++;
				if ((y != 0 && x != 0) && (y != getRow() - 1 && x != getCol() - 1)){		//checking if beginning is touching edge
					cout << "\nWARNING: End is not touching outer edge";
					error++;
				}
				if (side != 1){
					cout << "\nWARNING: End is not attached to a path block";
					error++;
				}
			}
		}
	if (pathExists == 0){
		cout << "\nWARNING: No path created";
		error++;
	}
	if (eExists == 0){
		cout << "\nWARNING: No end created";
		error++;
	}
	if (bExists == 0){
		cout << "\nWARNING: No start created";
		error++;
	}
	if (error > 0)
		cout << "\n\n***   ERROR(S) DETECTED   ***\n\n";
	else
		cout << "\n\n***  NO ERRORS DETECTED   ***\n\n";
	return error;
};
