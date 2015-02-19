/*	COMP 345 - Final Deliverable
	Team #3
	Sebouh Bardakjian		- 9640185
	Samuel-Beland Leblanc   - 7185642
	Zachary Bergeron        - 6593925
	Mark Ngo Minh Tai Le    - 6991203
   
	--- Tower Defence Game ---
	The program starts with the option to either load a map or enter the map editor. 
	You can load a sample map or a custom map (saved from editor)
	Or you can edit a new map or a loaded map, and then save it.
	Once the map is selected, the game starts, and the user can buy/sell/upgrade towers
	Once completed, the wave starts and critters move along the path 
	The two steps above are repeated until the game ends
	The game ends when either the player runs out of lives, or the max level is passed
	The player can choose to play again (Main menu) or quit
*/

#include "Game.h"

int main(){
	Game TD = Game();
	TD.play();
	return 0;
}
