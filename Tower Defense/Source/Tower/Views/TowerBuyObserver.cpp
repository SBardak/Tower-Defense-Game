#include "TowerBuyObserver.h"
#include "Utility.h"
#include "Tower.h"
#include "TowerManager.h"

TowerBuyObserver::TowerBuyObserver(TowerManager* tm) : TowerManagementObserver(tm)
{
}


TowerBuyObserver::~TowerBuyObserver()
{
}

void TowerBuyObserver::Update(){
	this->display();
}

TowerTypes TowerBuyObserver::displayTypeMenu(){
	bool confirmed = false;
	do{
		cout << "Which tower type would you like to buy? 1 - Basic	(Cost - $"<< this->getTowerManager()->GetBasicTower()->GetCost() <<")"
			"\n                                        2 - Freezing	(Cost - $" << this->getTowerManager()->GetFrezingTower()->GetCost() << ")"
			"\n                                        3 - Splash	(Cost - $" << this->getTowerManager()->GetSplashTower()->GetCost() << ")"
			"\n                                        4 - Back" << endl << endl << "Input: ";
		int input;
		Utility::getInt(input);
		while (input < 1 || input > 4){
			cout << "Invalid choice, try again..." << endl;
			Utility::getInt(input);
		}
		if (input < 4){
			(*this->getTowerManager()->getTowerObservers())[input - 1]->Update();
			cout << "Confirm purchase? (y/n): ";
			char cinput = ' ';
			cin >> cinput;

			while (cinput != 'y' && cinput != 'Y' && cinput != 'n' && cinput != 'N'){
				cout << "Invalid input, please re-enter: ";
				cin >> cinput;
			}

			if (cinput == 'y' || cinput == 'Y'){
				return static_cast<TowerTypes>(input - 1);
			}
			else if (cinput == 'n' || cinput == 'N')
				confirmed = false;
		}
		else {
			return TowerTypes::None;
		}
	} while (!confirmed);

	return TowerTypes::None; //To remove warnings
}

void TowerBuyObserver::initController(Grid* grid){

	TowerTypes tt = TowerTypes::None;
	do{
		tt = displayTypeMenu();
		if (tt != TowerTypes::None){

			// Check if has enough money to buy
			if (this->getTowerManager()->CanBuyTower(tt)){
				int x = 0;
				int y = 0;
				cout << endl << "Enter coordinates to buy tower: " << endl;
				cout << "x: ";
				Utility::getInt(x);
				cout << "y: ";
				Utility::getInt(y);
				int errorCode = this->getTowerManager()->BuyTower(tt, grid, x, y);
				if (errorCode == 0) {
					cout << "\nCannot place tower there: out of bounds\n" << endl;
				}
				else if (errorCode == 1) {
					cout << "\nCannot place tower there: path\n" << endl;
				}
			}
			else { // Not enough money
				cout << "\nNot enough money to buy tower!\n" << endl;
			}
		}
	} while (tt != TowerTypes::None);
}
