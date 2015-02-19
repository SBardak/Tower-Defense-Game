#include "Game.h"
#include "Utility.h"
#include "TowerManager.h"
#include "TowerSellingObserver.h"
#include "TowerLevelUpObserver.h"
#include "TowerBuyObserver.h"



const int Game::STARTINGCURRENCY = 1500;
const int Game::STARTINGLIVES = 15;

Game::Game(){
	currentLevel = 0;
	maxNumLevels = 3;
	myGrid = nullptr;
	editor = MapEditor();
	p = Player(Game::STARTINGCURRENCY, Game::STARTINGLIVES);
}

Game::~Game(){
}

void Game::play(){


	// Welcome message 
	cout << "   <><><><><><><><><><><><><><><><><><><><><>" << endl;
	cout << "<><><><><><>    Tower Defence v1.0    <><><><><>" << endl;
	cout << "   <><><><><><><><><><><><><><><><><><><><><>" << endl;

	// GAME LOOP
	do {
		// First Menu
		do{
			// Check if playing sample map or map editor
			cout << "\nWould you like to load a map, run the map editor, or quit? (1 - Load Map, 2 - Map Editor, 3 - Quit): ";
			int userInput = 0;
			Utility::getInt(userInput); // Make sure input is an Int
			while (userInput < 1 || userInput > 3){
				cout << "Invalid input, please try again: ";
				Utility::getInt(userInput);
			}
			// LOAD MAP
			if (userInput == 1){
				myGrid = editor.loadMap();
			} // EDITOR
			else if (userInput == 2) {
				bool confirmed = false;
				while (!confirmed){
					cout << "\nWould you like to edit a saved map or create a new one? (1- Edit, 2 - New, 3 - Back): ";
					int userInput = 0;
					Utility::getInt(userInput); // Make sure input is an Int
					while (userInput < 1 || userInput > 3){
						cout << "Invalid input, please try again: ";
						Utility::getInt(userInput);
					}
					if (userInput == 1){
						myGrid = editor.editAndSaveMap();
						if (myGrid == nullptr){
							confirmed = false;
						}
						else {
							confirmed = true;
						}
					} // EDITOR
					else if (userInput == 2) {
						myGrid = editor.createAndSaveMap();
						confirmed = true;
					}
					else if (userInput == 3){
						confirmed = true;
						myGrid = nullptr;
					}
				}
			}
			else if (userInput == 3) { // EXIT
				cout << "\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
				cout << " Thank you for playing Tower Defence v1.0! Hope you enjoyed it!" << endl;
				cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n" << endl;
				system("pause");
				exit(0);
			}

		} while (myGrid == nullptr); // Return to top menu 

		cm = new CritterManager(myGrid->getStartY(), myGrid->getStartX(), &p);

		CritterFactory* cFactory = new CritterFactory(cm, myGrid);

		tm = new TowerManager(myGrid, &p, cm);

		cout << endl << "------=== STARTING GAME ===-------" << endl;
		myGrid->printLegend();
		cout << *myGrid;


		// START OF GAME
		do {
			while (!isDonePlacingTowers()){
				buy_sell_upgrade_menu(myGrid);
			}
			// Generates a number of critters equal to three times the current level
			cm->initializeWave(3 * (currentLevel + 1));

			// Indicates the number of spaces between each critter
			int spawnInterval = 1;
			startLevel(cm, cFactory, spawnInterval, tm);

		} while (!GameOver() && !GameWin());

		if (GameOver()){
			cout << "\n********************************"
				"\n*          YOU LOSE!           *"
				"\n*   Better luck next time...   *"
				"\n********************************" << endl;
		}
		else{
			cout << "\n************************************************************"
				"\n*                       YOU WIN!                           *"
				"\n* You have successfully defended against the Critter Army! *"
				"\n************************************************************" << endl;
		}

		delete cFactory;
		delete myGrid;
		delete cm;
		delete tm;

	} while (playAgain());

	cout << "\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
	cout << " Thank you for playing Tower Defence v1.0! Hope you enjoyed it!" << endl;
	cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n" << endl;
	system("pause");

}

bool Game::playAgain(){
	char cPlayAgain = ' ';

	cout << "\nWould you like to play again? (y/n) ";
	cin >> cPlayAgain;

	while (cPlayAgain != 'y' && cPlayAgain != 'Y' && cPlayAgain != 'n' && cPlayAgain != 'N'){
		cout << "Invalid input, please re-enter: ";
		cin >> cPlayAgain;
	}

	if (cPlayAgain == 'y' || cPlayAgain == 'Y'){
		// DELETE AND RESET 
		p.setLives(Game::STARTINGLIVES);
		p.setCurrency(Game::STARTINGCURRENCY);
		currentLevel = 0;
		return true;
	}
	else if (cPlayAgain == 'n' || cPlayAgain == 'N')
		return false;

	return false; // Only to remove warnings
}

void Game::startLevel(CritterManager* cm, CritterFactory* cf, int spawnInterval, TowerManager* tm){
	++currentLevel;
	stringstream ss;
	ss << currentLevel;
	string s_currentLevel = ss.str();
	cout << endl << "-----=== STARTING LEVEL " + s_currentLevel + " ===-----" << endl;
	int spawnCounter = 0;
	// SPAWN AND MOVE CRITTERS
	while (cm->getCritterAliveCount() > 0 || cm->getCritterSpawnCount() > 0){
		// 1st critter spawn
		if (cm->getCritterSpawnCount() == cm->getCritterTotalCount() && spawnCounter == 0){
			spawnCounter = spawnInterval;
			cf->createCritter(currentLevel);
			cout << *myGrid << endl;
			cout << "Currency: " << p.getCurrency() << endl;
			cout << "Critters remaining: " << cm->getCritterAliveCount() << endl;
			cout << "Lives: " << p.getLives() << endl << endl;
			system("PAUSE");
		}
		else if (spawnCounter != 0)
			--spawnCounter;

		// MOVE CRITTERS BY 1
		cm->moveCritters(myGrid);
		if (cm->getCritterSpawnCount() <= 0 || spawnCounter != 0){
			cout << *myGrid << endl;
		}

		// Spawn remaining critters
		if (cm->getCritterSpawnCount() > 0 && spawnCounter == 0){
			spawnCounter = spawnInterval + 1;
			cm->spawnCritter(myGrid, currentLevel);
			cout << *myGrid << endl;
		}

		// STOP IF PLAYER LIVES <= 0
		if (p.getLives() <= 0)
			break;

		// ALL TOWERS ATTACK
		for (int i = 0; i < tm->getNumOfTowers(); ++i){
			int updatedFireRate = tm->getTowers()[i]->GetFireRate();
			int updatedPower = tm->getTowers()[i]->GetPower();
			int updatedRange = tm->getTowers()[i]->GetRange();
			cout << "Tower " << i + 1 << ":" << endl;
			tm->getTowers()[i]->AttackCritter(cm, &p, myGrid, updatedFireRate, updatedPower, updatedRange);
		}

		// PRINT INFO
		cout << "\nCurrency: " << p.getCurrency() << endl;
		cout << "Critters remaining: " << cm->getCritterAliveCount() << endl;
		cout << "Lives: " << p.getLives() << endl << endl;
		system("PAUSE");
	}
	endLevel();
}

void Game::endLevel(){
	cm->resetCritterID();
	for (int i = 0; i < tm->getNumOfTowers(); ++i){
		tm->getTowers()[i]->SetHitChanceCounter(0);
	}
}

bool Game::GameOver(){
	return (p.getLives() <= 0);
}

bool Game::GameWin(){
	return (currentLevel == maxNumLevels);
}

bool Game::isDonePlacingTowers(){
	char input = ' ';
	cout << "\nWould you like to buy, sell, upgrade, or inspect a tower? (y/n): ";

	cin >> input;

	while (input != 'y' && input != 'Y' && input != 'n' && input != 'N'){
		cout << "Invalid input, please re-enter: ";
		cin >> input;
	}

	if (input == 'y' || input == 'Y')
		return false;
	else if (input == 'n' || input == 'N')
		return true;

	return false; //To remove warnings
}

void Game::buy_sell_upgrade_menu(Grid* grid){
	bool completed = false;
	do{
		cout << endl << "Options: 1 - Buy Tower"
			"\n         2 - Sell Tower"
			"\n         3 - Upgrade Tower"
			"\n         4 - Inspect Tower"
			"\n         5 - Back" << endl << endl << "Input: ";
		int input = 0;
		Utility::getInt(input);
		while (input < 1 || input > 5){
			cout << "Invalid choice, try again..." << endl;
			Utility::getInt(input);
		}
		// BUY TOWER
		if (input == 1){
			buy_menu(grid);
		} // SELL TOWER
		else if (input == 2){
			sell_menu();
		} // UPGRADE TOWER
		else if (input == 3){
			upgrade_menu();
		} // BACK
		else if (input == 4){
			inspect_menu();
		}
		else if (input == 5){
			completed = true;

		}
	} while (!completed);
}

void Game::buy_menu(Grid* grid){
	TowerBuyObserver* tbo = new TowerBuyObserver(this->tm);
	tbo->display();
	tbo->initController(grid);
	delete tbo;
}

void Game::sell_menu(){
	TowerSellingObserver* tso = new TowerSellingObserver(this->tm);
	tso->Update();
	tso->initController();
	delete tso;
}

void Game::upgrade_menu(){
	TowerLevelUpObserver* tluo = new TowerLevelUpObserver(this->tm);
	tluo->Update();
	tluo->initController();
	delete tluo;
}

void Game::inspect_menu(){
	TowerManagementObserver* tmo = new TowerManagementObserver(this->tm);
	tmo->Update();
	tmo->initController();
	delete tmo;
}