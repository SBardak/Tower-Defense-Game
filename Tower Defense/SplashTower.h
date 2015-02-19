#ifndef SPLASHTOWER_H
#define	SPLASHTOWER_H

#include "CritterGroup.h"
#include "Critter.h"
#include "Tower.h"
#include <string>


class SplashTower /*: public Tower*/ {
public:
    SplashTower();
	//SplashTower(int cost, int range, int power, int initialLevelUpCost, int fireRate, int maxNumOfEffects, int splashRange, char dispChar, std::string name);
    //SplashTower(const SplashTower& orig);
    virtual ~SplashTower();
    
    virtual bool TryToAttackCritter(CritterGroup&);
    
private:

    int splashRange;
    
    virtual bool AttackCritter(Critter&, CritterGroup&);
    
};

#endif	/* SPLASHTOWER_H */

