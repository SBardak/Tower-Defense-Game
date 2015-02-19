#include "Upgrade.h"
#include "TowerObserver.h"


Upgrade::Upgrade(Tower* t)
{
	
	for (std::list<IObserver*>::iterator i = t->GetObservers()->begin(); i != t->GetObservers()->end(); ++i){
		Tower::Attach(*i);
		
	}
	for (std::list<IObserver*>::iterator i = this->GetObservers()->begin(); i != this->GetObservers()->end(); ++i){
		t->Detach(*i);

	}

	for (std::list<IObserver*>::iterator i = this->GetObservers()->begin(); i != this->GetObservers()->end(); ++i){
		TowerObserver* to = dynamic_cast<TowerObserver*>(*i);
		if (to != 0) {
			to->UpdateDecoratedTower(this);
		}
	}
	
	this->upgradedTower = t;
}


Upgrade::~Upgrade()
{
	delete upgradedTower;
}

int Upgrade::GetRange() const {
	return upgradedTower->GetRange();
}

int Upgrade::GetPower() const {
	return upgradedTower->GetPower();
}

int Upgrade::GetLevel() const {
	return upgradedTower->GetLevel();
}

int Upgrade::GetCurrentLevelUpCost() const {
	return upgradedTower->GetCurrentLevelUpCost();
}

int Upgrade::GetFireRate() const {
	return upgradedTower->GetFireRate();
}

int Upgrade::GetCost() const {
	return upgradedTower->GetCost();
}

int Upgrade::getX() const {
	return this->upgradedTower->getX();
}

int Upgrade::getY() const {
	return this->upgradedTower->getY();
}

void Upgrade::ApplyEffectsAndDamage(Critter& c, CritterManager& cm, int updatedPower){
	this->upgradedTower->ApplyEffectsAndDamage(c, cm, updatedPower);
}

std::string Upgrade::GetName() const {
	return this->upgradedTower->GetName();
}

int Upgrade::GetCurrentRefundCost() const {
	return this->upgradedTower->GetCurrentRefundCost();
}

Critter* Upgrade::GetCurrentCritter() const{
	return this->upgradedTower->GetCurrentCritter();
}

bool Upgrade::HasSplash() const{
	return this->upgradedTower->HasSplash();
}

void Upgrade::Attach(IObserver* o){
	Tower::Attach(o);
}

void Upgrade::Detach(IObserver* o){
	Tower::Detach(o);
}

void Upgrade::Notify(){
	Tower::Notify();
}

void Upgrade::SetPosition(int x, int y){
	this->upgradedTower->SetPosition(x, y);
}

char Upgrade::getDisplayChar() const{
	return this->upgradedTower->getDisplayChar();
}

Strategy* Upgrade::getStrategy() const {
	return this->upgradedTower->getStrategy();
}

bool Upgrade::CanBuy(int amount){
	if (GetCost() <= amount)
		return true;
	return false;
}

void Upgrade::SetCurrentCritter(Critter* c){
	this->upgradedTower->SetCurrentCritter(c);
}

bool Upgrade::AttackCritter(CritterManager* cm, Player* p, Grid* myGrid, int updatedFireRate, int updatedPower, int updatedRange){
	return this->upgradedTower->AttackCritter(cm, p, myGrid, updatedFireRate, updatedPower, updatedRange);
}

bool Upgrade::CanTowerHit(int updatedFireRate) {
	return this->upgradedTower->CanTowerHit(updatedFireRate);
}

void Upgrade::SetHitChanceCounter(int newHitChanceCounter){
	this->upgradedTower->SetHitChanceCounter(newHitChanceCounter);
}

void Upgrade::executeStrategy(Tower* t, CritterManager* cm, Grid* myGrid, int updatedRange){
	return this->upgradedTower->executeStrategy(t,cm,myGrid, updatedRange);
}

std::string Upgrade::GetEffects(){
	return this->upgradedTower->GetEffects();
}