#include <stddef.h>
#include<iostream>
#include "BasicTower.h"
#include "Critter.h"
#include "MapEntity.h"

BasicTower::BasicTower() {
}

BasicTower::BasicTower(int cost, int range, int power, int initialLevelUpCost, int fireRate, char dispChar, std::string name, Strategy* strategy)  {

	this->setDisplayChar(dispChar);
	this->initialDisplayChar = dispChar;
	this->name = name;

	if (cost < 0)
		this->cost = 0;
	else
		this->cost = cost;

	if (range < 0)
		this->range = 0;
	else
		this->range = range;

	if (power < 0)
		this->power = 0;
	else
		this->power = power;

	if (fireRate < 0)
		this->fireRate = 0;
	else
		this->fireRate = fireRate;

	if (initialLevelUpCost < 0)
		this->currentLevelUpCost = 0;
	else
		this->currentLevelUpCost = initialLevelUpCost;

	this->strategy = strategy;
	this->hitChanceCounter = 0;
	this->level = 1;
	this->currentCritter = NULL;
	this->currentRefundCost = static_cast<int> (cost * Tower::REFUND_RATIO);

}

BasicTower::BasicTower(const BasicTower& orig) {

	this->name = orig.name;
	this->cost = orig.cost;
	this->range = orig.range;
	this->power = orig.power;
	this->fireRate = orig.fireRate;
	this->currentLevelUpCost = orig.currentLevelUpCost;
	this->hitChanceCounter = 0;
	this->level = orig.level;
	this->currentCritter = NULL;
	this->currentRefundCost = orig.currentRefundCost;
	this->setDisplayChar(orig.getDisplayChar());
	this->initialDisplayChar = orig.initialDisplayChar;
	this->strategy = orig.strategy;
}

Critter* BasicTower::GetCurrentCritter() const {
	return currentCritter;
}

//This is public and only implemented for the sake of this exercise. 
//It is obviously a security issue, because the effects could be modified.

void BasicTower::SetHitChanceCounter(int newHitChanceCounter){
	this->hitChanceCounter = newHitChanceCounter;
}

int BasicTower::GetHitChanceCounter() const {
	return hitChanceCounter;
}

void BasicTower::SetCurrentRefundCost(int currentRefundCost) {
	this->currentRefundCost = currentRefundCost;
}

int BasicTower::GetCurrentRefundCost() const {
	return currentRefundCost;
}

int BasicTower::GetCurrentLevelUpCost() const {
	return currentLevelUpCost;
}

int BasicTower::GetLevel() const {
	return level;
}

int BasicTower::GetPower() const {
	return power;
}

int BasicTower::GetRange() const {
	return range;
}

int BasicTower::GetCost() const {
	return cost;
}

void BasicTower::SetInitialDisplayChar(char c){
	this->initialDisplayChar = c;
}

BasicTower::~BasicTower() {
	delete this->strategy;
}

//Basically modulos a counter to determine if the tower can attack (it simulates a firerate)
bool BasicTower::CanTowerHit(int updatedFireRate) {
	return !(this->hitChanceCounter++ % updatedFireRate);
}

void BasicTower::ApplyEffectsAndDamage(Critter& crit, CritterManager& cm, int updatedPower) {
	crit.ApplyDamage(updatedPower);
}


bool BasicTower::CanBuy(int amount) {
	return (amount >= this->cost);
}


void BasicTower::SetCurrentCritter(Critter* c){
	this->currentCritter = c;
}

int BasicTower::getX() const {
	return MapEntity::getX();
}

int BasicTower::getY() const {
	return MapEntity::getY();
}

bool BasicTower::HasSplash() const {
	return false;
}

void BasicTower::Attach(IObserver* o){
	Tower::Attach(o);
}

void BasicTower::Detach(IObserver* o){
	Tower::Detach(o);
}

void BasicTower::Notify(){
	Tower::Notify();
}

void BasicTower::setStrategy(Strategy* newStrategy){
	this->strategy = newStrategy;
}

void BasicTower::executeStrategy(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange){
	t->getStrategy()->findTarget(t, cm, myGrid, updatedRange);
}

Strategy* BasicTower::getStrategy() const{
	return this->strategy;
}

int BasicTower::GetFireRate() const {
	return fireRate;
}

bool BasicTower::AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange) {
	if (this->CanTowerHit(updatedFireRate)) {
		this->executeStrategy(this, cm, myGrid, updatedRange); // Sets currentCritter depending on strategy (or nullptr if none in range)
		if (this->GetCurrentCritter() != nullptr){
			this->ApplyEffectsAndDamage(*currentCritter, *cm, updatedPower);
			if (currentCritter->GetState() == CritterState::Dead){
				cm->setCritterAliveCount(cm->getCritterAliveCount() - 1);
				p->addCurrency(currentCritter->getReward());
				this->currentCritter = NULL;
			}
			return true;
		}
		else
		{
			cout << "No critters in range" << endl;
			return false;
		}
	}
	cout << "Cannot attack yet" << endl;
	return false;
}

void BasicTower::SetPosition(int x, int y){
	MapEntity::SetPosition(x, y);
}
char BasicTower::getDisplayChar() const{
	return MapEntity::getDisplayChar();
}

std::string BasicTower::GetEffects(){
	return "";
}