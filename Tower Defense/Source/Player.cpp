#include "Player.h"

Player::Player(){}

Player::Player(int initialCur, int lives) : currency(initialCur), lives(lives)
{
}


Player::~Player()
{
}

void Player::addCurrency(int amount){
	this->currency += amount;
}

void Player::removeCurrency(int amount){
	this->currency -= amount;
	if (this->currency < 0)
		this->currency = 0;
}

int Player::getLives() const {
	return lives;
}

void Player::setLives(int lives){
	this->lives = lives;
}

void Player::decrementLives(){
	if (lives > 0)
		--lives;
}

void Player::setCurrency(int currency){
	this->currency = currency;
}