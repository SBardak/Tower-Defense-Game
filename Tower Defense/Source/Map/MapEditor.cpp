#include "Grid.h"
#include "Tower.h"
#include "Critter.h"
#include "GridDisplay.h"
#include <fstream>
#include <iostream>
#include "MapEditor.h"
#include "Utility.h"

bool MapEditor::file_exists (const string& fileName) {
	FILE *file;
	errno_t err;
    if (err = fopen_s(&file, fileName.c_str(), "r") == 0) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

// Checks if height and width are between 5 and 40, returns false otherwise
bool MapEditor::isValidMapSize(int x, int y){
	if (x < 5 || y < 5)
		return false;
	else if (x > 40 || y > 40)
		return false;
	else
		return true;
}

bool MapEditor::isValidMapName(string mapName){
	if (mapName == "sample1" || mapName == "sample2" || mapName == "sample3")
		return false;
	
	if (mapName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos)
		return false;
	
	 return true;
}

Grid* MapEditor::editAndSaveMap(){
	Grid* myGrid = loadMap();
	if (myGrid == nullptr){ // If user chooses to go back
		return myGrid;
	}
	else { // User loaded a map
		do{
			myGrid->editLoadedMap();
		} while (myGrid->verifyMap() != 0); // Edit loaded map until valid
		myGrid->linkMap();
		return saveMap(myGrid); // Save the map and return it
	}
}
	

Grid* MapEditor::createAndSaveMap(){
	int count = 0;
	int height = 0;
	int width = 0;

	// Prompt for height and width of map and loop to check validity
	do{
		if (count > 0)
			cout << "You have entered invalid height and/or width." << endl;
		cout << "\nPlease, specify the height and width of the map! (Between 5 - 40)" << endl;
		cout << "Height: ";
		Utility::getInt(height);
		cout << "Width: ";
		Utility::getInt(width);
		++count;
	}while (!isValidMapSize(height, width)); 


	cout << "\nA blank map of Height (" << height << ") and Width (" << width << ") will be created!" << endl;

	// Create grid
	Grid* myGrid = new Grid(height, width);

	// Create Observer
	GridDisplay* display = new GridDisplay(myGrid);

	// Add observer to grid
	myGrid->addObserver(display);

	// Print legend
	myGrid->printLegend();

	// Print blank grid
	cout << *myGrid << endl;

	// Now that we have blank grid, prompt for path/scenery cells
	myGrid->editMap();

	//myGrid->verifyMap();   No need to verify new
	return saveMap(myGrid);
}

Grid* MapEditor::saveMap(Grid* myGrid){
	// Prompt to save
	cout << "\nWarning: If you do not save this map, it/changes will be discarded\nWould you like to save this map? (y/n): ";
	char c_userInput;
	cin >> c_userInput;
	while (c_userInput != 'y' && c_userInput != 'Y' && c_userInput != 'n' && c_userInput != 'N'){
		cout << "Invalid input, please try again: ";
		cin >> c_userInput;
	}
	if (c_userInput == 'y' || c_userInput == 'Y'){
		// Save Map
		cout << "\nWhat would you like to name this map? ";
		string mapName;
		cin >> mapName;
		while (!isValidMapName(mapName)){
			cout << "Invalid Map Name, can only contain [a-z][A-Z][0-9][_], please try again: ";
			cin >> mapName;
		}
		cout << "Custom map saved as: " + mapName + "\n" << endl;
		mapName = mapName + ".txt";
		myGrid->saveMap(mapName);

		cout << "Would you like to play this map or return to menu? (1 - Play, 2 - Menu): ";
		int i_userInput = 0;
		Utility::getInt(i_userInput);
		while (i_userInput != 1 && i_userInput != 2){
			cout << "Invalid input, please try again: ";
			Utility::getInt(i_userInput);
		}

		if (i_userInput == 1){
			return myGrid;
		}
		else if (i_userInput == 2){
			myGrid = nullptr;
			return myGrid;
		}
	}
	else if (c_userInput == 'n' || c_userInput == 'N'){
		cout << endl;
		cout << "Would you like to play this map or return to menu? (1 - Play, 2 - Menu): ";
		int i_userInput = 0;
		Utility::getInt(i_userInput);
		while (i_userInput != 1 && i_userInput != 2){
			cout << "Invalid input, please try again: ";
			Utility::getInt(i_userInput);
		}

		if (i_userInput == 1){
			return myGrid;
		}
		else if (i_userInput == 2){
			myGrid = nullptr;
			return myGrid;
		}
	}
	return nullptr; // To remove warnings
}


Grid* MapEditor::loadMap() {
	bool confirmed = false;

	// Create grid
	Grid* myGrid = nullptr;

	while (!confirmed){
		cout << "\nWhich map would you like to load? (1 - Map1, 2 - Map2, 3 - Map3, 4 - custom, 5 - back): ";
		string mapName = "";
		int mapNumber = 0;
		Utility::getInt(mapNumber);
		while (mapNumber < 1 || mapNumber > 5){
			cout << "Invalid selection, please try again: ";
			Utility::getInt(mapNumber);
		}
		if (mapNumber == 1){
			myGrid = new Grid("sample1.txt");
			cout << "\n---=== LOADING SAMPLE MAP 1 ===---" << endl;
		}
		else if (mapNumber == 2){
			myGrid = new Grid("sample2.txt");
			cout << "\n---=== LOADING SAMPLE MAP 2 ===---" << endl;
		}
		else if (mapNumber == 3){
			myGrid = new Grid("sample3.txt");
			cout << "\n---=== LOADING SAMPLE MAP 3 ===---" << endl;
		}
		else if (mapNumber == 4){
			cout << "\nWhat's the map name? ";
			cin >> mapName;
			while (!file_exists(mapName + ".txt")){
				cout << "This map does not exist, please try another: ";
				cin >> mapName;
			}
			cout << "\n---=== LOADING CUSTOM MAP: " + mapName + " ===---" << endl;
			myGrid = new Grid(mapName + ".txt");
		}
		else if (mapNumber == 5){
			myGrid = nullptr;
			return myGrid;
		}

		myGrid->printLegend();
		cout << *myGrid << endl;

		// Confirm Map after displaying it
		cout << "Confirm Map selection (y/n): ";
		char c_userInput;
		cin >> c_userInput;
		while (c_userInput != 'y' && c_userInput != 'Y' && c_userInput != 'n' && c_userInput != 'N'){
			cout << "Invalid input, please try again: ";
			cin >> c_userInput;
		}
		if (c_userInput == 'y' || c_userInput == 'Y'){
			// Create Observer
			GridDisplay* display = new GridDisplay(myGrid);

			// Add observer to grid
			myGrid->addObserver(display);

			confirmed = true;
		}
		else if (c_userInput == 'n' || c_userInput == 'N'){
			confirmed = false;
		}
	} // End of loop (confirmed)
	return myGrid;
}