/*
 * File:   TowerManager.cpp
 * Author: Samuel
 *
 * Created on October 19, 2014, 3:42 PM
 */

#include <stddef.h>

#include "TowerManager.h"
#include "Tower.h"
#include "BaseTowerObserver.h"
#include "StrategyNearest.h"
#include "StrategyNearestExit.h"
#include "StrategyStrongest.h"
#include "StrategyWeakest.h"
#include "BasicTower.h"
#include "EffectUpgrade.h"
#include "SplashUpgrade.h"
#include "LevelUpgrade.h"


TowerManager::TowerManager(Grid* const grd, Player* const p, CritterManager* cm) : map(grd), player(p), cm(cm) {

	//Basic towers so that we can inpect them when buying
	this->basicTower = createBasicTower();
	this->slowTower = createSlowTower();
	this->splashTower = createSplashTower();

	this->towers = new std::vector<Tower*>();
	this->observers = new std::vector<TowerObserver*>();

	this->observers->push_back(new BaseTowerObserver(this->basicTower));
	this->observers->push_back(new BaseTowerObserver(this->slowTower));
	this->observers->push_back(new BaseTowerObserver(this->splashTower));
	
	numOfTowers = 0;
}

TowerManager::TowerManager(const TowerManager& orig) : map(orig.map), player(orig.player) {
}

TowerManager::~TowerManager() {
	delete this->basicTower;
	delete this->slowTower;
	delete this->splashTower;


	if (!this->observers->empty()){
		this->observers->clear();
	}


	delete this->towers;
	delete this->observers;
}

bool TowerManager::CanBuyTower(TowerTypes type){
	Tower* temp = NULL;

	switch (type) {
	case TowerTypes::Basic:
		//temp = new Tower(*this->basicTower);
		temp = createBasicTower();
		break;
	case TowerTypes::Slowing:
		//temp = new Tower(*this->slowTower);
		temp = createSlowTower();
		break;
	case TowerTypes::Splash:
		//temp = new SplashTower(*dynamic_cast<SplashTower*>(this->splashTower));
		temp = createSplashTower();
		break;
	}

	return (temp->CanBuy(player->getCurrency()));
	
	
}

int TowerManager::BuyTower(TowerTypes type, Grid* grid, int x, int y) {

	Tower* temp = NULL;

	switch (type) {
	case TowerTypes::Basic:
		//temp = new Tower(*this->basicTower);
		temp = createBasicTower();
		break;
	case TowerTypes::Slowing:
		//temp = new Tower(*this->slowTower);
		temp = createSlowTower();
		break;
	case TowerTypes::Splash:
		//temp = new SplashTower(*dynamic_cast<SplashTower*>(this->splashTower));
		temp = createSplashTower();
		break;
	}

	if (!grid->isValid(y, x)) {
		// Out of bounds
		return 0;
	}
	else if (grid->isPath(y, x)) {
		// On path
		return 1;
	}
	else if (this->map->setTower(y, x, temp)){
		this->towers->push_back(temp);
		this->observers->push_back(new TowerObserver(temp));
		this->player->removeCurrency(temp->GetCost());
		temp->SetPosition(x, y);
		++numOfTowers;

		Notify();
		return -1;
	}
	return -1; //To remove warnings
}

bool TowerManager::SellTower(Tower* t){
	int index = this->Contains(t);
	if (index >= 0){
		this->player->addCurrency(t->GetCurrentRefundCost());
		int x = t->getX();
		int y = t->getY();
		this->map->setTower(y, x, static_cast<Tower*>(nullptr));
		this->towers->erase(this->towers->begin() + index);
		this->observers->erase(this->observers->begin() + index);
		--numOfTowers;
		Notify();
		return true;
	}
	else{
		return false;
	}
}

bool TowerManager::LevelUpTower(int index){

	int tempAmount = (*(this->towers))[index]->GetCurrentLevelUpCost();
	bool res = LevelUpgrade::TryToLevelUp((*(this->towers))[index], this->player->getCurrency());
	(*(this->observers))[index + 3]->UpdateDecoratedTower((*(this->towers))[index]);
	if (res){
		this->player->removeCurrency(tempAmount);
		Notify();
	}

	return res;
}

int TowerManager::Contains(Tower* t) {

	int ind = 0;
	for (std::vector<Tower*>::iterator i = this->towers->begin(); i != this->towers->end(); ++i, ++ind){
		if (t == *i){
			return ind;
		}
	}
	return -1;
}

void TowerManager::Inspect(int index){

	(*(this->observers))[index+3]->Update();
	system("pause");
}



int TowerManager::getNumOfTowers() const {
	return numOfTowers;
}

Tower* TowerManager::createBasicTower(){

	Tower* temp = new BasicTower(250, 3, 2, 50, 4, 'B', "Basic Tower", new StrategyNearest());
	return temp;

}

Tower* TowerManager::createSlowTower(){
	Tower* temp = new BasicTower(250, 3, 2, 100, 4, 'F', "Freezing Tower", new StrategyNearestExit());
	temp = new EffectUpgrade(temp, new Effect(1, 0, 0, CritterType::None, EffectType::Slow, "Slow"));
	return temp;
}

Tower* TowerManager::createSplashTower(){
	Tower* temp = new BasicTower(250, 3, 2, 80, 4, 'S', "Splash Tower", new StrategyWeakest());
	SplashUpgrade::TryToApplySplash(temp, 3 /* Splash range of 3 */);
	return temp;
}