#include "GridDisplay.h"
#include <iostream>
#include <iomanip>
#include <string>

GridDisplay::GridDisplay(Grid* grid) {
	this->grid = grid;
}

GridDisplay::~GridDisplay() {}

void GridDisplay::update() {
	using std::setw;
	cout << endl;
	cout << setw(4) << " ";
	for (int i = 1; i <= grid->getCol(); ++i)
		cout << setw(3) << i;
	cout << " (x)" << endl;
	cout << setw(4) << " ";
	for (int i = 1; i <= grid->getCol()*3+1; ++i)
		cout << "_";
	cout << endl;
	for (int row = 0; row < grid->getRow(); ++row){
		cout << setw(2) << row+1 << " |";
		for (int col = 0; col < grid->getCol(); ++col){
			cout << setw(3) << ((grid->getArr(row,col) == nullptr)? "0" : grid->getArr(row,col)->print());
		}
		cout << " |" << endl;
	}
	cout << setw(3) << "(y) ";
	for (int i = 1; i <= grid->getCol()*3+1; ++i)
		cout << "_";
	cout << "\n" << endl;
}