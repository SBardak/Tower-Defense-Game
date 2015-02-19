#pragma once
class Player
{
public:
	Player();
	Player(int initialCur, int lives);
	virtual ~Player();
	int getCurrency() const { return currency; }
	void addCurrency(int amount);
	void removeCurrency(int amount);
	void setCurrency(int currency);
	int getLives() const;
	void setLives(int lives);
	void decrementLives();
private:
	int currency;
	int lives;
};

